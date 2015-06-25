
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

class Grid
  constructor: (@name) ->
    # variables
    @data = {}
    @meta = {}

    # expressions
    @dependencies = {}
    @functions = {}

    # transaction state
    @dirty = [] # { var: , value:  }
    @_currentTransaction = null

  # transactions
  open: (name) ->
    debug 'open', name
    throw new Error "open(): Already open transaction: #{name}" if @_currentTransaction
    name = 'anonymous' if not name
    @_currentTransaction = name
    return this

  close: (name) ->
    debug 'close', name
    tr = @transaction
    throw new Error "close(): No open transaction" if not @_currentTransaction
    @_resolve()
    @transaction = null
    return this

  transaction: (name, func) ->
    if not name
      func = name

    @open name
    func.apply this, []
    @close name
    return this

  _implicitTransaction: (func) ->
    if not @transaction
      @transaction func
    else
      func.apply this

  # variables
  define: (name, type, initial) ->
    @meta[name] = type
    @set name, initial if initial?
  
  set: (name, value) ->
    @_implicitTransaction () ->
      @dirty.push
        var: name
        value: value
    return this

  calc: (target, inputs, func) ->
    for input in inputs
      @dependencies[input] = target
    @functions[target] =
      func: func
      inputs: inputs
    return this

  # computation
  _resolve: () ->
    # TODO: respect data restrictions on the cell. agree Contract?
    # XXX: allow iterative solving, with progress?

    debug 'starting with', @data
    changes = []
    for c in @dirty
      changes.push c.var if @data[c.var] != c.value
      @data[c.var] = c.value
    debug 'changes in transaction', changes

    # TODO: filter out duplicate dependency changes
    for v in changes
      dependants = @dependencies[v]
      continue if not dependants
      for d in dependants
        f = @functions[d]
        args = f.inputs.map((i) => @data[i])
        debug "calculating #{d} from #{f.inputs}", args
        res = f.func.apply this, [args]
        debug 'got', res
        @data[d] = res
      

Grid.create = (name) ->
  return new Grid name

tests = () ->
  chai = require 'chai'

  describe '1+2', ->
    it 'should be 3', ->
      da = Grid.create('simple')
        .transaction 'initial', (c) ->
          @define('a', 'number', 1)
          @define('b', 'number', 2)
          @define('c', 'number')
          @calc('c', ['a', 'b'], (args) -> return args[0] + args[1] )
      chai.expect(da.data['c']).to.eql 3


tests()
