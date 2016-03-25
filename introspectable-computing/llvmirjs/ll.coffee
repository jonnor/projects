
## LLVM IR generation

# LLVM IR reference, http://llvm.org/docs/LangRef.html
# http://llvm.lyngvig.org/Articles/Mapping-High-Level-Constructs-to-LLVM-IR

# http://www.ibm.com/developerworks/library/os-createcompilerllvm1/#resources

# IDEA: allow to pass function, which gets # ref https://msdn.microsoft.com/en-us/magazine/ee291514.aspx

# TODO: support raw() for raw LLVMIR strings

# DSL references
# Internal JS DSL for HTML https://github.com/caolan/pithy
# http://www.slideshare.net/adorepump/dsls-in-javascript
# http://www.infoq.com/articles/internal-dsls-java
# List of DSL patterns, http://martinfowler.com/dslCatalog/
# http://www.vittoriozaccaria.net/diy/

# XXX: probably there should be a more generic expression/statement type class,
# which can be used for functions and other things?
class FunctionBuilder
  constructor: (@data, @parent) ->
    @body = []

  # return from a function
  ret: (type, value) ->    
    @body.push "ret #{type} #{value}"

  # generate LLVM IR
  generate: () ->
    f = @data
    args = "" # FIXME: serialize from f.args
    return """define #{f.returns} @#{f.id}(#{args}) { 
      #{@body}
    }"""

  up: () ->
    return @parent

class Builder
  constructor: (metadata, options) ->
    @options = options or {}
    @metadata = metadata or {}
    @functions = {}
    console.log 'constructor done'

  # define a function
  function: (name, returns=null, args={}) ->
    d =
      id: name
      returns: returns
      arguments: args
    @functions[name] = f = new FunctionBuilder d, this
    return f

  # generate the resulting code
  generate: () ->
    lines = []
    for n, f of @functions
      lines.push f.generate()
    return lines.join('\n')
    

exports.Builder = Builder

ll = exports

unsafeRandomString = () ->
  return (Math.random()+1).toString(36).substr(2, 5)

compileProgram = (code, progname, callback) ->
  { exec } = require 'child_process'
  fs = require 'fs'
  path = require 'path'

  tmpDir = 'build'
  fs.mkdirSync tmpDir if not fs.existsSync tmpDir

  tmpName = progname + '-' + unsafeRandomString()
  tmpPath = path.join tmpDir, "#{tmpName}.ll"
  compiledPath = path.join tmpDir, "#{tmpName}.o"
  llc = 'llc'
  fs.writeFile tmpPath, code, (err) ->
    return callback err if err

    compileCmd = "#{llc} -filetype=obj #{tmpPath}"
    exec compileCmd, (err, stdout, stderr) ->
      return callback err if err

      progPath = path.join tmpDir, "#{tmpName}"
      linkCmd = "gcc -o #{progPath} #{compiledPath}"
      exec linkCmd, (err, stdout, stderr) ->
        return callback err, progPath

tests = () ->
  chai = require 'chai'

  describe 'program exiting with 0', ->
    code = null
    program = null
    it 'should generate code', ->
      b = new ll.Builder
      b.function 'main', 'i32', {}
       .ret 'i32', 0
      code = b.generate()
      chai.expect(code).to.contain 'i32 @main()'

    it 'should compile', (done) ->
      compileProgram code, 'true', (err, program) ->
        console.log 'prog', program
        return done err
    it 'should give exit code 0'


tests()
