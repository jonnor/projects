
# Utils
addChainedAttributeAccessor = (obj, propertyAttr, attr) ->
    obj[attr] = (newValues...) ->
        if newValues.length == 0
            obj[propertyAttr][attr]
        else
            obj[propertyAttr][attr] = newValues[0]
            obj

# Common declaration
binaries =
  'eq': '=='
  'neq': '!='
  'lt': '<'
  'gt': '>'
  'lte': '<='
  'gte': '>='
commands = [
  'invalid'
  'header'
  'declare'
  'domain'
]
commands = commands.concat Object.keys(binaries)

generateC = () ->
  declarec = require 'declarec'
  fs = require 'fs'

  ccode = ""

  enums = {}
  count = 0
  for p in commands
    enums[p.toUpperCase()] = count
    count++
  ccode += declarec.generateEnum 'Command', 'CMD_', enums

  enums = {}
  count = 0
  for p, v of binaries
    enums[p.toUpperCase()] = count
    count++
  ccode += declarec.generateEnum 'ConstraintType', 'CS_', enums

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
        @constraints.push [ op, varA, varB, null ]
        return self

    for name, v of binaries
      this[name] = addPrimitiveChained name

  decl: (name, lower, upper) ->
    @constraints.push ['declare', name, null, null]
    @constraints.push ['domain', name, lower, upper]
    return this
  konst: (name, value) ->
    @decl name, value, value
    return this

Domain.create = (id) ->
  return new Domain id

# Map variable names to integers (and vica versa)
buildVariableMapping = (constraints) ->
  int = 0
  mapping = {}
  reverse = {}

  for cont in constraints
    [op, varname] = cont
    if op == 'declare'
      throw new Error "variable declared twice #{varname}" if mapping[varname]?
      int += 1
      mapping[varname] = int
      reverse[int] = varname

  return { forward: mapping, reverse: reverse }

buildOpMapping = () ->
  int = 0
  mapping = {}
  reverse = {}

  for p in commands
    int += 1
    mapping[p] = int
    reverse[int] = p
  return { forward: mapping, reverse: reverse }

operations = buildOpMapping()
console.log 'op mapping', operations

serialize = (constraints, mapping) ->
  commands = constraints.slice()
  rels = constraints.filter((c) -> ( c[0] != 'declare' and c[0] != 'domain') )
  commands.unshift [ 'header', Object.keys(mapping.forward).length, rels.length, null ]

  bytesPerCommand = 4*4
  buf = new Buffer bytesPerCommand*commands.length
  maybeMap = (val) ->
    return if typeof val == 'number' then val else mapping.forward[val]
  commands.forEach (args, idx) ->
    throw new Error 'Contraint op must be 4 long' if not args.length == 4
    [op, a, b, c] = args
    op = operations.forward[op]
    a = maybeMap a
    b = maybeMap b
    pos = (idx*bytesPerCommand)
    console.log idx, args, pos, op, a, b
    buf.writeInt32LE op, pos+(0*4)
    buf.writeInt32LE a, pos+(1*4)
    buf.writeInt32LE b, pos+(2*4)
    buf.writeInt32LE c, pos+(3*4)

  return buf

deserialize = (stream, mapping) ->
  bytesPerCommand = 4*4
  numCommands = stream.length/bytesPerCommand
  ops = []
  for idx in [0...numCommands]
    pos = (idx*bytesPerCommand)
    op = stream.readInt32LE pos+(0*4)
    a = stream.readInt32LE pos+(1*4)
    b = stream.readInt32LE pos+(2*4)
    c = stream.readInt32LE pos+(3*4)

    op = operations.reverse[op.toString()]
    if not op == 'header'
      a = mapping.reverse[a.toString()]
    if not op == 'domain'
      b = mapping.reverse[b.toString()]
      c = mapping.reverse[c.toString()]
    ops.push [op, a, b, c]

  return ops

solveOne = (dom, callback) ->
  mapping = buildVariableMapping dom.constraints
  console.log 'mappings', mapping

  stream = serialize dom.constraints, mapping
  console.log 'serialized', stream

  ops = deserialize stream, mapping
  console.log 'deserialized', ops

  { exec } = require 'child_process'
  filename = 'out.csp.bin'
  # HACK: should be passed over stdin
  require('fs').writeFileSync filename, stream
  exec "./cstrain_kernel #{filename}", (err, stdout, stderr) ->
    console.log 'out', err, stdout, stderr
    return callback err if err


tests = () ->
  chai = require 'chai'

  describe 'hello world', ->
    it 'should solve', (done) ->
      d = Domain.create('trivial')
        .eq 'a', 'b'
        .konst 'a', 5

      console.log 'constraints',   d.constraints
      solveOne d, (err, solution) ->
        chai.expect(err).to.not.exist
        chai.expect(solution['b'] == 5)
        done()

generateC()
tests()
