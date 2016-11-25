flowtrace = window.flowtrace
flowtrace = require 'flowtrace/src/index' if not flowtrace

React = window.React

getEvents = (trace, predicate) ->
  trace.events.filter predicate


# DOM helpers
id = (name) ->
  document.getElementById name

clearChildren = (node) ->
  while node.firstChild
    node.removeChild node.firstChild
  return true

# Main
main = () ->
  console.log 'main'

  updateApp = (app) ->
    console.log 'render'

  changeTrace = (err, trace) ->
    console.log 'load', err, Object.keys(trace)
    dataEvents = getEvents(trace, (e) -> e.command == 'data')
    console.log 'data', dataEvents
    app =
      trace: trace
      selection: dataEvents[dataEvents.length-1]
    updateApp app

  id('loadfileinput').addEventListener 'change', (event) ->
    file = event.target.files[0]
    console.log 'loadfile', file.name
    reader = new FileReader
    reader.onload = (e) ->
      contents = reader.result
      trace = flowtrace.trace.loadString contents
      changeTrace null, trace
    reader.readAsText(file)

  loadDefault = () ->
    defaultTrace = '/trace.json' # FIXME: allow specify in URL
    flowtrace.trace.loadHttp defaultTrace, changeTrace
  setTimeout loadDefault, 100
  console.log 'main done'

main()
