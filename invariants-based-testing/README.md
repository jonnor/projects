
By stating some 'invariants' or 'properties' that should hold over a range of inputs,
we can more exaustively test a system compared to example-based (unit-testing etc).

# Property-based testing

Modern implementations

* [Theft](https://github.com/silentbicycle/theft), property-based-testing for C
* [quickcheck in Racket](https://docs.racket-lang.org/quickcheck/index.html)
* [quickcheck for Rust](https://github.com/BurntSushi/quickcheck)
* [Property-based testing in ScalaTest](http://www.scalatest.org/user_guide/property_based_testing)
* [JsVerify](http://jsverify.github.io/)
* [Property-based testing without framework in CoffeeScript](https://graeme-lockley.github.io/posts/20160201-coffeescript_string_calculator_with_predicate_tests/)
* [quick_check.js](https://github.com/gampleman/quick_check.js/), includes lots of combinators

> Many partial and fragmentary open-source tools claim to be "quickcheck clones" but they lack two really important parts: search-space optimization and failure minimization
http://thinkrelevance.com/blog/2013/11/26/better-than-unit-tests

Generators

* [popcorn](https://github.com/asmyczek/popcorn), a JSON generator/fuzzer
* [json-schema-faker](https://github.com/json-schema-faker/json-schema-faker), generate JSON from a JSON Schema.
Also has some inference for the schemas itself (like type).
* [generate-schema](https://github.com/nijikokun/generate-schema) can infer a schema from example data.

Additional ideas

* [gencheck](https://hackage.haskell.org/package/gencheck) (Haskell), allows selection strategies and composing generators.
* JSCheck uses "claim" instead of "property", to avoid the existing definition of "property" in languages like JavaScript.

## References

### QuickCheck

[QuickCheck](http://www.cse.chalmers.se/~rjmh/QuickCheck/). The original project, in and for Haskell.
[paper](http://www.cs.tufts.edu/~nr/cs257/archive/john-hughes/quick.pdf).
Suports conditional laws/properties, using a predicate function. On the Lava embedded DSL for hardware circuits,
was able to check more things than with a formal theorem prover (because they only supported first-order logic). 

> In 1984, Duran and Ntafos compared the fault detection probability
> of random testing with partition testing, and discovered that
> the differences in effectiveness were small[9].
> Hamlet and Taylor repeated their study more extensively, and corrobo-
> rated the original results [12]. Although partition testing is
> slightly more effective at exposing faults, to quote Hamlet's
> excellent survey [11], \By taking 20% more points in a random test,
> any advantage a partition test might have had is wiped out.

> ..in general, a test adequacy criterion is defined, and
> testing proceeds by generating test cases which meet the
> adequacy criterion.
> For example, a simple criterion is that every reachable statement
> should be executed in at least one test, a more complex one that every feasible control path
> (with exceptions for loops) be followed in at least one test.
> A wide variety of adequacy critera have been proposed; a recent survey is [19].
> We have chosen not to base QuickCheck on such an adequacy criterion..

### Test Adequacy

> [19]: http://www.cs.toronto.edu/~chechik/courses07/csc410/p366-zhu.pdf
> Line, Statement, Branch, Path, Mutation (score)

These are based on an analysis of the code.
Can one instead have a test adequancy criterion defined over input and output values?
Requires some notion of the shape, size and partitions of the value domains?

> The idea is to construct an order # between mutants
> such that mutant b is stronger than a (written a # b) if for any test
> case t, t kills b implies that t necessarily kills a.
> Therefore, mutant b should be executed on test cases before the
> execution of a, and a is executed only when the test data failed to kill b.
> A similar ordering can also be defined on test data. Given a mutant q of program
> p, q should be executed on test data t before the execution on test data s if t is
> more likely to kill q than s is.

> 4.2 Program-Based Input-Space Partitioning
> The software input space can also be partitioned according to the program.
> In this case, two input data belong to the same subdomain if they cause the same
> “computation” of the program.
> Usually, the same execution path of a program is considered as the same computation.
> Therefore, the subdomains correspond to the paths in the program.

In FBP, the connections activated by executing a graph with particular inputs can classify.
However not so easy to find via analysis. Would need to use symbolic execution in the components used

> https://www.st.cs.uni-saarland.de/edu/automatedtestingverification12/slides/02-AdequacyCategoryPartition.pdf
> Why not Random [input selection]?
> Non-uniform fault distribution
> Failing values are sparse in the input space — needles in a very big haystack.
> -> We need to use everything we know 
> Partition principle
> Exploit some knowledge to choose samples that are more likely to include "special" or trouble prone areas of input space

> Functional testing
> Uses the specification to partition input space
> Test each category, and boundaries between categories

> Combinatorial testing:
> Identify distinct attributes that can be varied
> Systematically generate combinations to be tested
> 
> Category-partition testing
> Separate (manual) identification of values that characterize the input space 
> from (automatic) generation of combinations for test cases
> 
> Pairwise testing 
> systematically test interactions among attributes of the program input space 
> with a relatively small number of test cases
> 
> Catalog-based testing
> aggregate and synthesize the experience of test designers in a particular 
> organization or application domain, to aid in identifying attribute values
Can use constraints between values to reduce combinatorial possibilities
Simple example: Erronous value needs only be excercised in one case? (assumes independence...)
> [single] indicates a value class that test designers choose to test only once to reduce 
> the number of test cases


## Question

If we have specifications which associate classified/partitioned input with partitioned/classified outputs,
this is an implicit definition about the (inherent) structure of the program?


## Implementaition ideas

```
Classifier
  Given a value, return true if value belongs in a class, else false
  Use a set of such classifiers to determine class(es) of value
  alternative, given a value, return names of classes the value belongs to

Generator
  For a given class, generate values that belong in this class
  Should have ways of guiding order of generation? Resume from particular point, do each side of

Each Generator should have a corresponding Classifier. 

PropertyChecker
  Can execute unit-under-test and verify a certain Property
  It is given the input values, and the output values.

Property
  Each property has PropertyChecker and associated input domain.
  The input domain is expressed as a class name, and the associated Generator used to create input values
  The output domain is declared as a class name, and output values are checked using the associated Classifier 
```

Output (equivalence) paritions.
Two output values can be considered part of the same equivalence partition if
they have the same classes (as returned by classifiers) 

Test adequacy:
(of testcases). Output from each partition has been produced.
(of declared output partitions). No output produced fell outside of a declared class
(of declared inputs). ??? No input exists outside declared domains, which does not produce an error.

Attempt to select inputs such that each partition is covered with something,
then afterwards expand coverage inside each partition.
If possible, distribute values inside widely spread inside declared classification.
Sub-classifications may assist this?
Both for inputs, and for outputs?

Can create a Generator using a set of sub-class generators, and picking between them?
First one-of-each, then random selection inside each afterwards.

Errors as a class? Like everything else can be subclassified

Do we need/want to parametrize generators?
Does that imply some new subclass(es) are created?

## Internal system properties

### Generator-Classifier correspondence.
Each value produced by a Generator for class `C` shall be classified as `C` by the classifier 

### Classification subsets. 
If "mysub" is a subset of "my"
each value generated of class "mysub" is classified as "my"
some but not all, values generated in class "my" is classified as "mysub"

Example: "positive integer" is a subset of "integer", is a subset of (real) "number"

## Examples

Multiplication. Inputs: A, B. Outputs: M

A * 0       =0
A * 1       =A
A * A       =A**2
A * -A      =-(A**2)

A * >1      >A
A * <1      <A
A * <-1     <-A

... and the same holds for B


