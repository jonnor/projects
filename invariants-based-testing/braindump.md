
By stating some 'invariants' or 'properties' that should hold over a range of inputs,
we can more exaustively test a system compared to example-based (unit-testing etc).

# Property-based testing

* [Theft](https://github.com/silentbicycle/theft), property-based-testing for C
* [Property-based testing in ScalaTest](http://www.scalatest.org/user_guide/property_based_testing)
* [JsVerify](http://jsverify.github.io/)
* [Property-based testing without framework in CoffeeScript](https://graeme-lockley.github.io/posts/20160201-coffeescript_string_calculator_with_predicate_tests/)
* [quick_check.js](https://github.com/gampleman/quick_check.js/), includes lots of combinators

> Many partial and fragmentary open-source tools claim to be "quickcheck clones" but they lack two really important parts: search-space optimization and failure minimization
http://thinkrelevance.com/blog/2013/11/26/better-than-unit-tests

# propgen-ideas

Classifier: Given a value, return true if value belongs in a class, else false
Use a set of such classifiers to determine class(es) of value
alternative, given a value, return names of classes the value belongs to

Generator: For a given class, generate values that belong in this class
Should have ways of guiding order of generation? Resume from particular point, do each side of

Each Generator should have a corresponding Classifier. 

Property
domain

Do we need/want to parametrize generators?
Does that imply some new subclass(es) are created?

Output (equivalence) paritions.
Two output values can be considered part of the same equivalence partition if
they have the same classes (as returned by classifiers) 


Exhaustiveness:
(of testcases). Output from each partition has been produced.
(of declared partitions). No output produced did not fall into a declared class

Attempt to select inputs such that each partition is covered with something,
then afterwards expand coverage inside each partition.
If possible, distribute values inside widely spread inside declared classification.
Sub-classifications may assist this?
Both for inputs, and for outputs?

Can create a Generator using a set of sub-class generators, and picking between them?
First one-of-each, then random selection 

Errors as a class? Like everything else can be subclassified


Internal system properties

Generator-Classifier correspondence.
Each value produced by a Generator for class `C` shall be classified as `C` by the classifier 

Classification subsets. 
If "mysub" is a subset of "my"
each value generated of class "mysub" is classified as "my"
some but not all, values generated in class "my" is classified as "mysub"

Example: "positive integer" is a subset of "integer", is a subset of (real) "number"


Examples

Multiplication. Inputs: A, B. Outputs: M

A * 0       =0
A * 1       =A
A * A       =A**2
A * -A      =-(A**2)

A * >1      >A
A * <1      <A
A * <-1     <-A

... and the same holds for B


