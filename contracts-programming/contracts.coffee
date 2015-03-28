# Just some rough sketching around how contracts-based programming or
# programming-by-contracts, design-by-contract could look like in
# CoffeeScript/JavaScript
# 
# References
# - http://en.wikipedia.org/wiki/Design_by_contract
# - http://c2.com/cgi/wiki?DesignByContract
# - http://disnetdev.com/contracts.coffee/ custom syntax+compiler based on coffee-script
#
# TODO:
# - Prototype a way to declare and verify symmetrical functions, ie ones which cancel eachother out
# - Sketch out a way to provide default for pre/post/invar, as an executable coding-style
# - Add possibily for human-readable doc/description on predicates,
# attach the info to exceptions
# - Investigate how to generate useful documentation, both
# and REPL-like runtime introspection
# - Investigate how unit tests can be generated from introspected
# invariants, or how checks can replace unit tests for simple cases
# - Investigate to which extent invariants can be statically checked,
# prototype reasoning about some simple cases.
# http://coffeescript.org/documentation/docs/nodes.html
# http://www.coffeelint.org/
# https://github.com/jashkenas/coffeescript/issues/1466
#
# - Add some type checking predicates
# - Allow a single pre/post/class-invar func in addition to array
# - Allow to not specify pre/post at all
# - Consider moving to a fluent interface ala https://www.npmjs.com/package/blueprint
# - Consider adding first-class support for Promises instead of functions
#
# Random:
# - Should contracts and their use be registered globally, for dependency tracking?
# Could allow tracking whether they are all set up statically or not
# Also how many of them are excersised by tests. Also a registration target for a test?
# - 


# Framework
class ContractFailed extends Error

class PreconditionFailed extends ContractFailed
    constructor: () ->

class PostconditionFailed extends ContractFailed
    constructor: () ->

class ClassInvariantViolated extends ContractFailed
    constructor: () ->

# should not be possible to disable except for in extreme cases for performance
# at that point should probably avoid the function hops too
checkPrecond = true
# should be disabled in non-debug mode
checkClassInvariants = true
checkPostcond = true

# Factory function for contracts-based methods
method = (preconditions, postconditions, body) ->
    return () ->
        instance = this
        if checkClassInvariants
            for invariant in instance.invariants
                throw new ClassInvariantViolated if not invariant.apply instance
        if checkPrecond
            for cond in preconditions
                throw new PreconditionFailed if not cond.apply instance, arguments

        ret = body.apply(instance, arguments)

        if checkPostcond
            for cond in postconditions
                throw new PostconditionFailed if not cond.apply instance, arguments
        if checkClassInvariants
            for invariant in instance.invariants
                throw new ClassInvariantViolated if not invariant.apply instance

        return ret

# Predicates, can be used as class invariants, pre- or post-conditions
# Some of these can be generic and provided by framework, parametriced to 
# tailor to particular program need
noUndefined = () ->
    for a in arguments
        return false if not a?
    return true

neverNull = (attribute) ->
    return () ->
        return this[attribute]?

attributeEquals = (attribute, value) ->
    return () ->
        return this[attribute] == value


# Example
class Foo
    invariants: [neverNull 'prop1']

    constructor: () ->
        @prop1 = "foo"

    doBar: method [noUndefined], [], (arg1, arg2) ->
        return arg1+arg2

    doBaz: method [noUndefined], [], (arg1, arg2) ->
        @prop1 = null

    doCacaWrong: method [noUndefined], [attributeEquals 'prop1', 'bar'], () ->
        @prop1 = "bar2"

    doCacaRight: method [noUndefined], [attributeEquals 'prop1', 'bar'], () ->
        @prop1 = "bar"

main = () ->

    chai = require 'chai'

    describe 'Contracts', ->
        f = null
        beforeEach ->
            f = new Foo
        it 'method with valid arguments should succeed', ->
            chai.expect(f.doBar(1, 2)).to.equal 3
        it 'method with failing precondition should throw', ->
            chai.expect(() -> f.doBar undefined, 0).to.throw PreconditionFailed
        it 'method violating class invariant should throw', ->
            chai.expect(() -> f.doBaz 2, 3).to.throw ClassInvariantViolated
        it 'method violating postcondition should throw', ->
            chai.expect(() -> f.doCacaWrong 1).to.throw PostconditionFailed
        it 'method not violating postcondition should succeed', ->
            chai.expect(f.doCacaRight()).to.equal "bar"

main()
    

