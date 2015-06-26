
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
  'eq': '=='
  'neq': '!='
  'lt': '<'
  'gt': '>'
  'lte': '<='
  'gte': '>='
  'num': '='

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

# TODO: compile tertiary constraints to binary (sum etc)

# Setting up
class Domain
  constructor: (@id) ->
    @constraints = []

    self = this
    # Add the API for primitive constraints
    addPrimitiveChained = (op) =>
      return (varA, varB) =>
        @constraints.push [ op, varA, varB ]
        return self

    for name, v of primitives
      this[name] = addPrimitiveChained name

Domain.create = (id) ->
  return new Domain id

# Map variable names to integers (and vica versa)
buildVariableMapping = (constraints) ->
  int = 0
  mapping = {}
  reverse = {}

  for cont in constraints
    cont.forEach (arg, idx) ->
      # first is opcode
      if idx > 0 and typeof arg == 'string' and not mapping[arg]?
        int += 1
        mapping[arg] = int
        reverse[int] = arg

  return { forward: mapping, reverse: reverse }

buildOpMapping = (ops) ->
  int = 0
  mapping = {}
  reverse = {}
  for p, ignored of primitives
    int += 1
    mapping[p] = int
    reverse[int] = p
  return { forward: mapping, reverse: reverse }

operations = buildOpMapping()
console.log 'op mapping', operations

serialize = (constraints, mapping) ->
  bytesPerCommand = 4*4
  buf = new Buffer bytesPerCommand*constraints.length
  maybeMap = (val) ->
    return if typeof val == 'number' then val else mapping.forward[val]
  constraints.forEach (args, idx) ->
    throw new Error 'Contraint op must be 3 long' if not args.length == 3
    [op, a, b] = args
    op = operations.forward[op]
    a = maybeMap a
    b = maybeMap b
    pos = (idx*bytesPerCommand)
    console.log idx, args, pos, op, a, b
    buf.writeInt32LE op, pos+(0*4)
    buf.writeInt32LE a, pos+(1*4)
    buf.writeInt32LE b, pos+(2*4)
    buf.writeInt32LE 0, pos+(3*4)

  return buf

deserialize = (stream, mapping) ->
  bytesPerCommand = 4*4
  numCommands = stream.length/bytesPerCommand
  ops = []
  for idx in [0...numCommands]
    pos = (idx*bytesPerCommand)
    op = stream.readInt32LE pos+(0*4)
    console.log idx, pos, op
    op = operations.reverse[op.toString()]
    a = stream.readInt32LE pos+(1*4)
    a = mapping.reverse[a.toString()]
    b = stream.readInt32LE pos+(2*4)
    if not op == 'num'
      b = mapping.reverse[b.toString()]
    padding = stream.readInt32LE pos+(3*4)
    ops.push [op, a, b]

  return ops

solveOne = (dom, callback) ->
  mapping = buildVariableMapping dom.constraints
  console.log 'mappings', mapping

  stream = serialize dom.constraints, mapping
  console.log 'serialized', stream

  ops = deserialize stream, mapping
  console.log 'deserialized', ops

tests = () ->
  chai = require 'chai'

  describe 'hello world', ->
    it 'should solve', (done) ->
      d = Domain.create('trivial')
        .eq 'a', 'b'
        .num 'a', 5

      console.log 'constraints',   d.constraints
      solveOne d, (solution) ->
        chai.expect(solution['b'] == 5)
        done()

generateC()
tests()
