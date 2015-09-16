
# Mtr convenience
class Stepper
  constructor: () ->
    @_self = Module['_mtr_stepper_new']()

  free: () ->
    Module['_mtr_stepper_free'] @_self


# DOM helpers
id = (name) ->
  document.getElementById name

# Main
main = () ->
  console.log 'main'

  stepper = new Stepper()
  stepper.free()

  Module['_mtr_run_smokecheck']()

  #id('runButton').onclick = runTests

  console.log 'main done'

main()





###
TODO: automate creation of wrapper objects
createApiWrapper = (prefix, methodnames, module) ->
  module = Module if not module
  
  klass = {}
  for name in methodnames
    emName = "#{prefix}_#{name}"
    emFunc = module[emName]
    if name == 'new'
      klass[name] = () ->
        # get the C instance, keep it in object
        emInstance = emFunc.call this, arguments
        instance =
          _self: eminstance
        return instance
    else
      klass[name] = () ->
        # inject the C instance as first argument
        args = [@._self]
        for i in arguments.length
          args.push arguments[i]
        emFunc.call this, 

autoApiWrapper = (prefix, module) ->
  module = Module if not module
  obj = {}

  for name, func of module
    if name.indexOf(prefix) == 0 

Stepper = createApiWrapper '_mtr_stepper', ['new', 'free']
StepperEmulator = createApiWrapper '_mtr_emu', ['new', 'free']
###
