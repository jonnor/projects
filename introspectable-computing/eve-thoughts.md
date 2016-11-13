
# Thoughts on Eve

http://witheve.com

## Good

Super-strong focus on the data, delightfully small amounts of "programming" standing inbetween.
Express data-transformations by focusing on data,
express algorithms using multiple data-transformations together.

Suprisingly strong composability.
Practical to use multiple code blocks, each with one responsibility, working together through the data they read/commit/bind.
Code blocks and their records as reusable "modules". Ref "View" and "bar-graph" etc

Enabling/disabling blocks works nicely, trying alternate approaches etc.
Creating a new block or two for testing something is practical.
Often keep it around as reference.

Browser runtime/server works seamlessly.
Can use browser for debug/vizualization/UI also when targetting server.

## Interesting

Strong pattern-matching is really what makes the declarative logic style possible,
and the universiality of the `record` (of records) as data representation.

Set-oriented, as opposed to individual values, means dealing with many of a thing is not special.
Using aggregates in order to extract individual (or just fewer)


## Things I miss

* Searchable examples & API reference from the IDE
* Docs/tools for understanding where functions can be used and not
* Server connection state indication. https://github.com/witheve/Eve/issues/546
* Block not-active indication https://github.com/witheve/Eve/issues/547


## Challenges

### Encapsulation

Any block can create, change, or delete  any data.
Big danger of widespread "action from afar".
Especially once programs start spreading over more than one page.
Need tools, best-practices which helps ensure that one does not need to worry about every block
for every change made.

Search matching rules decides which records can be affected.
Could be able to declare some constraints on a codeblock.
For instance that nothing is deleted, limitations on databases affected.

### Deploying
As a standard, whole .JS app not tricky, just bundle all the deps, provide entrypoint, and go.
https://github.com/witheve/Eve/issues/544

Keeping the IDE-included, open extensibility.
Access to private data. Ability to disrupt system (also for other users).
Authentication, scoping

Partial/gradual usage is more interesting in most real-world scenarios:

Embedding Eve in JavaScript app (Node.js/browser). No APIs for this at this time?
Using Eve as backend for existing system. Could be doable with the @server database (HTTP server).
Using Eve as frontend for existing system. Seems doable with @http database (HTTP client).


### Verifying correctness

There seems to be some ideas around using blocks to declare invariants, by searching
for things which, and then committing to an `@error` database if it happens.
Mentioned on the frontpage http://witheve.com/ but not shown in any examples, or mentioned in docs.


Functional testing. Can be applied 'outside of' Eve.
For instance testing browser state, injecting events and verifying correctness in DOM.
Servers can be tested on protocol level, via MQTT/HTTP.

Unit testing
If an embedding API exists, can use traditional JavaScript tooling for testing.
Like Mocha, Chai, etc.

Open question how automated testing integrates with the IDE.
Non-Eve aware tooling can probably only be represented in a very low-fidelity manner.

Given the declarative nature of Eve, perhaps there is some possibilities of static analysis,
including proving certain properties of a program?


## Relationship to FSM

The creator of Eve, Chris Granger, said that finite state machines are a foundation.
And that for some problems it may be desirable to have an explicit/high-level representation of them.
https://groups.google.com/forum/#!topic/eve-talk/xCONYXnztyE

## Relationship to FBP/dataflow

The entire flowtrace produced by an FBP program, could maybe be seen as an implicit set of records.
Records are tagged by the edge which the data was processed.
Can be used for visualization of system state.
If richely enough annotated it could maybe be a basis for global constraints.
Some of the search/matching methods may be good inspiration for finding things in traces.


# Related

* [Datalog](https://en.wikipedia.org/wiki/Datalog)
* [Dedalus: Datalog in Time and Space](https://www2.eecs.berkeley.edu/Pubs/TechRpts/2009/EECS-2009-173.html)
* [Bloom](http://bloom-lang.net/faq/), distributed programming language, based on Dedalus. Last release in 2013.
* [CALM: consistency as logical monotonicity](http://bloom-lang.net/calm/)
* [The Declarative Imperative: Experiences and Conjectures in Distributed Logic](http://db.cs.berkeley.edu/papers/sigrec10-declimperative.pdf)

Not so related

* [Lineage-driven Fault Injection](https://people.eecs.berkeley.edu/~palvaro/molly.pdf). Promises much faster detection of faults compared to random fault injection.

