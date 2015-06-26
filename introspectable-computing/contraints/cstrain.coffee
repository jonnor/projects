
# Utils
addChainedAttributeAccessor = (obj, propertyAttr, attr) ->
    obj[attr] = (newValues...) ->
        if newValues.length == 0
            obj[propertyAttr][attr]
        else
            obj[propertyAttr][attr] = newValues[0]
            obj

# Common declaration
primitives =
  'eq': '='
  'neq': '!='
  'lt': '<'
  'gt': '>'
  'lte': '<='
  'gte': '>='

generateC = () ->
  declarec = require 'declarec'
  fs = require 'fs'

  enums =
    'INVALID': 0
  count = 0
  for p, v of primitives
    int = count += 1
    enums[p.toUpperCase()] = int

  ccode = declarec.generateEnum 'CsConstraint', 'CS_', enums
  console.log 'loc', ccode
  fs.writeFileSync 'cstrain_declarations.h', ccode, 'utf-8'

# Setting up
class Cstrain
  constructor: (@id) ->
    @constraints = []

    # Add the API for primitive constraints
    addPrimitiveChained = (op) ->    
      return (varA, varB) =>
        @constraints.push [  ]
        return this
    for name, v of primitives
      this.[name] = addPrimitiveChained name

Cstrain.create (id) -> return new Cstrain id

tests = () ->
  chai = require 'chai'

  describe 'hello world', ->
    it 'should solve', ->
      Cstrain.create('trivial')
        .

generateC()
tests()
