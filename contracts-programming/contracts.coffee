# Just some rough sketching around how contracts-based programming or
# programming-by-contracts, design-by-contract could look like in standard
# CoffeeScript/JavaScript
# 
# References
# - http://en.wikipedia.org/wiki/Design_by_contract
# - http://c2.com/cgi/wiki?DesignByContract
# - http://disnetdev.com/contracts.coffee/ custom syntax+compiler based on coffee-script
# - http://dlang.org/contracts.html built-in support for contracts in D
#
# Differences from existing implementions
# - contracts, and functions/classes built with contracts, can be introspected
# - preconditions can, and should be, used for input validation at runtime
#
# Goals
# - the fact that contracts are used is completely transparent to consuming code
# - JavaScript-friendly API (even if written with CoffeeScript)
#
# Usecases
# - NoFlo components: verifying data on inports, specifying component behavior
# - HTTP REST apis: specifying behavior, validating request
# - Abstractions: multiple implementations of same interface
#
# Unresolved questions:
# - should it be a goal to enable piece-wise/step-by-step integration into existing functions/classes?
# - should class invariants be explicit on class, or implicit derived from contract-based properties or both?
#
# Documentation
# - allow to generate API docs including pre,post,classinvariants
#
# Testing
# - allow to verify all pre,post,classinvariants have been triggered
# - predicates include positive/negative examples as basic doctests
#
#
# Debugging
# - ability to log failing predicates, including descritpion, location of fail, reason for fail
# - ability to cause failing predicate to cause breakpoint using `debugger` statement
#
# Performance
# - MAYBE: opt-out of postcondition and class invariant checking
#
# TODO:
# - Prototype a way to declare and verify symmetrical functions, ie ones which cancel eachother out
# - Prototype a way to declare an interface which can be implemented by multiple
# - Sketch out a way to provide default for pre/post/invar, as an executable/verifiable coding-style
# - Add possibily for human-readable doc/description on predicates,
# attach the info to exceptions
# - Investigate how to generate useful documentation, both
# and REPL-like runtime introspection
#  Use positive and negative example as docs/tests for predicate functions
# - Investigate how unit tests can be generated from introspected
# invariants, or how checks can replace unit tests for simple cases
# - Investigate to which extent invariants can be statically checked,
# prototype reasoning about some simple cases.
# http://coffeescript.org/documentation/docs/nodes.html
# http://www.coffeelint.org/
# https://github.com/jashkenas/coffeescript/issues/1466
#
# - Add some type checking predicates
# - Add way to wrap constructor also
# - Allow a single pre/post/class-invar func in addition to array
# - Allow to not specify pre/post at all
# - Consider moving to a fluent interface ala https://www.npmjs.com/package/blueprint
#   * invariants on properties whould then be done together with declaring them. Specify default, generate constructor?
# - Consider adding first-class support for Promises instead of functions
#
# Random:
# - Should contracts and their use be registered globally, for dependency tracking?
# Could allow tracking whether they are all set up statically or not
# Also how many of them are excersised by tests. Also a registration target for a test?
# - 

# FIXME: move everything into this namespace
agree = {}

# Framework
class ContractFailed extends Error

class PreconditionFailed extends ContractFailed
    constructor: (name, cond) ->
       @message = "#{name}: #{cond?.name}"

class PostconditionFailed extends ContractFailed
    constructor: (name, cond) ->
       @message = "#{name}: #{cond?.name}"

class ClassInvariantViolated extends ContractFailed
    constructor: (name, cond) ->
       @message = "#{name}: #{cond?.name}"

class NotImplemented extends Error
    constructor: () ->
        @message = 'Body function not implemented'


class FunctionContract
    constructor: (@name, @parent, @options) ->
        @postconditions = []
        @preconditions = []
        @func = () ->
            throw new NotImplemented
        defaultOptions =
            checkPrecond: true
            checkClassInvariants: true
            checkPostcond: true
        @options = defaultOptions # FIXME: don't override

    ## Fluent construction
    postcondition: (conditions) ->
        conditions = [conditions] if not conditions.length
        for c in conditions
            @postconditions.push c
        return this

    # TODO: also accept a fail value/callback
    precondition: (conditions) ->
        conditions = [conditions] if not conditions.length
        for c in conditions
            @preconditions.push c
        return this

    body: (f) ->
        @func = f
        return this

    # Register as ordinary function on
    add: (context, name) ->
        name = @name if not name?
        call = (instance, args) =>
            @call instance, args, name
        func = () ->
            call this, arguments
        func.contract = this # back-reference for introspection
        context[name] = func
        return this

    # Chain up to parent to continue fluent flow there
    method: () ->
        return @parent.method.apply @parent, arguments if @parent

    # Executing
    call: (instance, args, name) ->
        options = @options

        if options.checkClassInvariants and instance.contract?
            for invariant in instance.contract.invariants
                pass = invariant.apply instance
                throw new ClassInvariantViolated if not pass
        if options.checkPrecond
            for cond in @preconditions
                throw new PreconditionFailed @name, cond if not cond.apply instance, args

        ret = @func.apply instance, args

        if options.checkPostcond
            for cond in @postconditions
                throw new PostconditionFailed @name, cond if not cond.apply instance, args
        if options.checkClassInvariants and instance.contract?
            for invariant in instance.contract.invariants
                pass = invariant.apply instance
                throw new ClassInvariantViolated if not pass

        return ret

    pre: () -> @precondition.apply @, arguments
    post: () -> @postcondition.apply @, arguments

agree.function = (name, parent, options) ->
    return new FunctionContract name, parent, options

class ClassContract
    constructor: (@name, @options) ->
        @invariants = []
        @initializer = () ->
            console.log 'ClassContract default initializer'

        self = this
        construct = (instance, args) =>
            @construct instance, args
        @klass = () ->
            this.contract = self # back-reference for introspection
            construct this, arguments
        @klass.contract = this # back-reference for introspection

        defaultOptions =
            checkPrecond: true
            checkClassInvariants: true
            checkPostcond: true
        @options = defaultOptions # FIXME: don't override

    # add a method
    method: (name) ->
        f = agree.function "#{@name}.#{name}", this
        return f.add @klass.prototype, name

    # add constructor
    init: (f) ->
        @initializer = f
        return this

    # add class invariant
    invariant: (conditions) ->
        conditions = [conditions] if not conditions.length
        for cond in conditions
            @invariants.push cond
        return this

    # register ordinary constructor
    add: (context, name) ->
        name = @name if not name
        context[name] = @klass
        return this

    construct: (instance, args) ->
        @initializer.apply instance, args

        # Check class invariants
        if @options.checkClassInvariants
            for invariant in instance.contract?.invariants
                throw new ClassInvariantViolated if not invariant.apply instance
        return instance

agree.Class = (name) ->
    return new ClassContract name


# Predicates, can be used as class invariants, pre- or post-conditions
# Some of these can be generic and provided by framework, parametriced to 
# tailor to particular program need
#
# TODO: generalize the composition/parametrization of predicates?
# - look up an identifier (string, number) in some context (arguments, this)
# - take a value for the instance of a set (types, values) to check for 
noUndefined = () ->
    for a in arguments
        return false if not a?
    return true

# parametric functions, returns a predicate
neverNull = (attribute) ->
    return () ->
        return this[attribute]?

attributeEquals = (attribute, value) ->
    return () ->
        return this[attribute] == value

attributeTypeEquals = (attribute, type) ->
    return () ->
        return typeof this[attribute] == type


# Examples
examples = {}

agree.Class 'Foo'
.add examples
.init () ->
    @prop1 = "foo"
    @numberProp = 1
.invariant neverNull 'prop1'
.invariant attributeTypeEquals 'numberProp', 'number'

.method 'setNumberWrong'
.precondition noUndefined
.postcondition [attributeEquals 'prop1', 'bar']
.body (arg1, arg2) ->
    @prop1 = null

.method 'setPropNull'
.precondition noUndefined
.body (arg1, arg2) ->
    @prop1 = null

.method 'addNumbers'
.precondition noUndefined
.body (arg1, arg2) ->
    return arg1+arg2

# TODO: allow to reuse/name the contract, and use different body/name
agree.function 'setPropCorrect'
.add examples.Foo.prototype
.pre noUndefined
.post [attributeEquals 'prop1', 'bar']
.body () ->
    @prop1 = 'bar'

agree.function 'setPropWrong'
.add examples.Foo.prototype
.precondition noUndefined
.postcondition [attributeEquals 'prop1', 'bar']
.body () ->
    @prop1 = 'nobar'

# Invalid
agree.Class 'InvalidInit'
.invariant neverNull 'prop1'
.init () ->
    @prop1 = null
.add examples

main = () ->

    chai = require 'chai'

    describe 'FunctionContract', ->
        f = null
        beforeEach ->
            f = new examples.Foo

        it 'method with valid arguments should succeed', ->
            chai.expect(f.addNumbers(1, 2)).to.equal 3
        it 'method with failing precondition should throw', ->
            chai.expect(() -> f.addNumbers undefined, 0).to.throw PreconditionFailed

        it 'method violating postcondition should throw', ->
            chai.expect(() -> f.setPropWrong 1).to.throw PostconditionFailed
        it 'method not violating postcondition should succeed', ->
            chai.expect(f.setPropCorrect()).to.equal "bar"

    describe 'ClassContract', ->
        f = null
        beforeEach ->
            f = new examples.Foo

        it 'initializer shall be called', ->
            chai.expect(f.prop1).to.equal "foo"
        it 'initializer violating class invariant should throw', ->
            chai.expect(examples.InvalidInit).to.throw ClassInvariantViolated
        it 'method violating class invariant should throw', ->
            chai.expect(() -> f.setPropNull 2, 3).to.throw ClassInvariantViolated
    
    describe 'Predicates', ->
        f = null
        beforeEach ->
            f = new examples.Foo
        # TODO: should be autogen from example
        it 'method violating attributeTypeEqual', () ->
            chai.expect(() -> f.setNumberWrong()).to.throw ContractFailed

main()
    

