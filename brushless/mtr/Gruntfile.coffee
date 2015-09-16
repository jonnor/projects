
exports = () ->
  list = []
  fs = require 'fs'
  contents = fs.readFileSync('./mtr.exports', 'utf-8')
  for line in contents.split '\n'
    list.push line
  return list

formatList = (list) ->
  quote = (str, quotechar) -> return quotechar+str+quotechar
  items = ( quote(i, '\\"') for i in list when i)
  items = items.join ','
  fmt = "\\'[#{items}]\\'"
  return fmt

emscriptenExports = formatList(exports())

module.exports = ->
  # Project configuration
  @initConfig
    pkg: @file.readJSON 'package.json'

    # Browser version building
    exec:
      emscripten: "make emscripten EMSCRIPTEN_EXPORTS=#{emscriptenExports}"
      host: 'make'

    # BDD tests on Node.js
    mochaTest:
      nodejs:
        src: ['test/*.coffee']
        options:
          reporter: 'spec'
          require: 'coffee-script/register'

    # Web server for the browser tests
    connect:
      server:
        options:
          port: 8000

  # Grunt plugins used for building
  @loadNpmTasks 'grunt-exec'

  # Grunt plugins used for testing
  @loadNpmTasks 'grunt-contrib-connect'


  # Our local tasks
  @registerTask 'build', 'Buld', (target = 'all') =>
    @task.run 'exec:host'
    @task.run 'exec:emscripten'

  @registerTask 'test', 'Build MicroFlo and run automated tests', (target = 'all') =>
    @task.run 'build'

  @registerTask 'default', ['test']

