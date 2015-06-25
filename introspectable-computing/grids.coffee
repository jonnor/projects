# ./node_modules/.bin/mocha --compilers=coffee:coffee-script/register grids.coffee

# A Grid is akin to a spreadsheet
# - contains of a set of cells containing data
# - cells data have a particular type
# - cell value can be calculated as an expression of other cells
# - when a cell changes
# 
# Unlike conventional spreadsheet implementations
# - cells can have any name
# - there is no particular order/arrangement of cells
# - the cells are arranged sparsely
# - The metadata, including type info, value constraints are stored separately from the data
# - cell changes are grouped into transactions. TODO: or make resolution fully lazy?
#
# Goals: introspectable handling of equations in 'real application'
# - can be visualized and manipulated in UI, both statically and live
# - usable by non-tech audiences with live data coming from live production systems
#
# TODO: add richer metadata to cells
# TODO: add support for units
# TODO; add metadata to functions
# TODO: add some sort of selectors, including multi-value/ranges
# TODO: use in http://github.com/the-grid/guv ?
# TODO: add NoFlo integration
# TODO: add a simple DSL, and extensible function library
# TODO: add some UI prototypes
# XXX: optional integration with WebWorker?
debug = () ->
debug = console.log

addChainedAttributeAccessor = (obj, propertyAttr, attr) ->
    obj[attr] = (newValues...) ->
        if newValues.length == 0
            obj[propertyAttr][attr]
        else
            obj[propertyAttr][attr] = newValues[0]
            obj

# Holds information about a variable. Not the data itself!
class Variable
  constructor: (@ctx, @id) ->
    @properties =
      type: 'number'
      label: @id
      unit: ''
      description: ''

    for attr of @properties
      addChainedAttributeAccessor(this, 'properties', attr)

  # Chain up to parent
  set: (value) ->
    @ctx.set @id, value
    return this

  # Context modifiers
  parent: () ->
    return @ctx
  var: (name) ->
    return @ctx.var name
  function: (inputs, func) ->
    return @ctx.function @id, inputs, func

class Function
  constructor: (@func, @ctx) ->
    @properties =
      label: ''
      description: @func.toString()

    for attr of @properties
      addChainedAttributeAccessor this, 'properties', attr

  # Context modifiers
  parent: () ->
    return @ctx
  var: (name) ->
    return @ctx.var name
  function: (inputs, func) ->
    return @ctx.function @id, inputs, func

# A context which computations can be done in
# Holds multiple Variable and Function
class Computation
  constructor: (@id) ->
  
    # metadata
    @id = '' if not @id
    @properties =
      description: ''

    for attr of @properties
      addChainedAttributeAccessor this, 'properties', attr

    # variables
    @variables = {} # varname -> Variable
    # expressions
    @dependencies = {} # 
    @functions = {} # targetvarname -> Function
    # transaction state
    @data = {}
    @dirty = [] # { var: , value:  }
    @_currentTransaction = null

  # transactions
  open: (name) ->
    debug 'Computation.open', name
    throw new Error "open(): Already open transaction: #{name}" if @_currentTransaction
    name = 'anonymous' if not name
    @_currentTransaction = name
    return this

  close: (name) ->
    debug 'Computation.close', name
    throw new Error "close(): No open transaction" if not @_currentTransaction
    @_resolve()
    @_currentTransaction = null
    return this

  transaction: (name, func) ->
    if not name
      func = name

    @open name
    func.apply this, []
    @close name
    return this

  _implicitTransaction: (name, func) ->
    if not @_currentTransaction
      @transaction name, func
    else
      func.apply this

  # variables
  var: (name) ->
    @variables[name] = new Variable this, name if not @variables[name]
    return @variables[name]
  
  set: (name, value) ->
    @_implicitTransaction "#{name}=#{value}", () =>
      @dirty.push
        var: name
        value: value
    return this

  # functions
  function: (target, inputs, func) ->
    func = new Function func, this if typeof func == 'function'
    func.ctx = this
    func.inputs = inputs # hack
    @_implicitTransaction "#{target}=f(#{inputs.join(',')})", () =>
      for input in inputs
        @dependencies[input] = [] if not @dependencies[input]
        @dependencies[input].push target
        @dirty.push
          var: input
      @functions[target] = func
    return func

  # computation
  _resolve: () ->
    # TODO: respect data restrictions on the cell. agree Contract?
    # XXX: allow iterative solving, with progress?

    debug 'starting with', @data
    changes = {}
    for c in @dirty
      changes[c.var] = c.value if @data[c.var] != c.value
      @data[c.var] = c.value if c.value?
    @dirty = []
    changes = Object.keys changes
    debug 'changes in transaction', changes

    # TODO: filter out duplicate dependency changes
    for v in changes
      dependants = @dependencies[v]
      continue if not dependants
      for d in dependants
        debug "calculating #{d}", dependants, Object.keys(@functions)
        f = @functions[d]
        args = f.inputs.map((i) => @data[i])
        args.unshift args.slice()
        debug "from #{f.inputs}", args
        res = f.func.apply this, args
        debug 'got result', res
        @data[d] = res
        @dirty.push
          var: d

    @_resolve() if @dirty.length

Computation.create = (id) ->
  return new Computation id

generateFunctions = () ->
  fs = require 'fs'
  path = require 'path'

  code = ""
  for op in ['+', '-', '*', '/']
    f = "exports['#{op}'] = function(v, a, b) { return a#{op}b; };\n"
    code += f

  filepath = path.join __dirname, 'generated.js'
  fs.writeFileSync filepath, code, 'utf-8'

  p = path.join __dirname, 'generated.js'
  functions = {}
  exported = require p
  for op, f of exported
    func = new Function f
    func.label "a#{op}b"
    functions[op] = func
  return functions

tests = () ->
  chai = require 'chai'

  describe 'c=a+b,a=1,b=2', ->
    da = null
    it 'c should be 3', ->
      da = Computation.create('simple')
          .description 'Make things as simple as they can be, but no simpler'
          .var('a').set 1
          .var('b').set 2
          .var('c').function ['a', 'b'], (v, a, b) -> return a + b
          .parent()
      chai.expect(da.data['c']).to.eql 3

    it 'a=2 should make c=4', ->
      da.transaction 'initial', () ->
        @set 'a', 2
      chai.expect(da.data['c']).to.eql 4

  describe 'guv proportional scaling', ->
    it '', ->
      f = generateFunctions()
      c = Computation.create('proportional')
        .var('N').label('jobs in queue')
        .var('p').label('processing time')
        .var('ta').label('target time')
        .var('T_w').label('waiting time').function(['N', 'p'], f['*'])
        .var('T_a').label('available time').function(['ta', 'p'], f['-'])
        .var('W').label('required workers').function(['T_w', 'T_a'], f['/'])
        .parent()
      c.open().set('N', 100).set('p', 10).set('ta', 52).close()
      chai.expect(Math.ceil(c.data['W'])).to.equal 24
###
min = (a, b) -> if a < b then a else b
max = (a, b) -> if a > b then a else b
bound = (v, lower, upper) -> return min(max(v, lower), upper)

scale = (config, queueLength) ->
  estimate = proportional config, queueLength
  debug 'estimate for', queueLength, estimate
  workers = Math.ceil(estimate)
  # TODO: estimate higher than max should be a warning
  # TODO: add code for estimating how long it will take to catch up (given feed rate estimates)
  workers = bound workers, config.minimum, config.maximum
  debug 'bounded', workers
  return workers
###

tests()
