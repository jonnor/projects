
## Boolean satisfiability (SAT)

About

* [SAT solvers](https://embedded.eecs.berkeley.edu/eecsx44/fall2011/lectures/SATSolving.pdf)

[List of solvers](https://github.com/jonnor/agree/blob/master/doc/braindump.md#relation-to-theorem-provers).

Other Tools

* [logic.py](http://aima.cs.berkeley.edu/python/logic.html)
* [CNF 3-SAT generator](http://code.activestate.com/recipes/82346-random-3-cnf-problem-generator/), in Python
* [cnfgen](https://github.com/MassimoLauria/cnfgen/blob/master/cnfformula/cnfgen.py), Python generator for CNF file format (common input to SAT solvers)

Example problems/solutions

* [4queens.cnf](http://homepage.cs.uiowa.edu/~hzhang/c145/code/queen4.cnf)
* [N-queens CNF generator](https://sites.google.com/site/haioushen/search-algorithm/solvean-queensproblemusingsatsolver) in C++
* [N-queens CNF generator](http://forrestbao.blogspot.de/2007/11/python-script-to-solve-n-queen-problem.html) in Python
* [pycosat](https://pypi.python.org/pypi/pycosat) Python frontend to picosat, with CNF representation

## Logic programming

* [HANSEI as a Declarative Logic Programming Language](http://okmij.org/ftp/kakuritu/logic-programming.html).
Library-only approach (for OCaml), with. As an alternative to using a specialized languages like Prolog, or a deeply embedded DSL like miniKanren.
The overall problem formulation is 'generate worlds and test', but thanks to lazy evaluation it doesn't have to realize or explore all worlds.
Support for non-determinism. Search strategies include iterative deepening. Can abort on depth limit, or when remainder probabiliy (that solution is in unexplored world) is below a certain level.

## Relations to human intelligence

* [Computational Logic and Human Thinking: How to be Artificially Intelligent](http://www.doc.ic.ac.uk/~rak/papers/newbook.pdf) by Robert Kowalski. Argues for using computational logic as an extension of human thinking, as well as explaining many core concepts of intelligent agents, and proposing some novel (combinations of) agent models.

'Production systems' combine a working memory of atomic facts
with condition-action rules of the form *if conditions then actions*.

> In Artificial Intelligence and Computing more generally, it is common for  an  intelligent  designer
> to  implement  an  artificial  agent  that  does  not contain an  explicit  representation  of  its higher-level  goals. 
> The designer is aware of the agent’s goals, but the agent itself is not.
> As far as the agent is concerned, its life  may seem to be entirely meaningless.

> we explore how meta-logic can be used to simulate the reasoning of other agents,
> and to solve problems that can not  be  solved  in  the  object  language  alone

