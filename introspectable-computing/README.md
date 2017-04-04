# Introspectable programming

Researching making programs and systems that are *introspectable*.
That is, *programs that know what they are* and *how they work*,
and provide facilities for *viewing*, *extracting* and *querying* this
information.

And with these capabilities in place, how can we represent problems & solutions
in a better way. Can we make programs more *understandable*, faster to get to a useful level, and more robust?
Can we use these properties to make programming more widely applicable and accessible,
also as a tool outside software development?

Note that this is a broader use of the word 'introspection' compared to
typically in programming, which usually is limited to very primitive information, like types.

# Motivations

There are 3 primary motivations for this work. From most concrete to most speculative:

1. Increasing the ability of experienced programmers to reason about
non-trivial systems, and write more advanced and robust software.
2. Helping blur the lines between 'programmers' and 'non-programmers' (domain experts, interested users),
by making the system more inviting and self-describing.
3. Open up the possibility for self-governing systems and intelligent agents.
Where the entity using the introspection information is another program, instead of a human.


# Areas of research

Some of the areas I have done work in, or think could be fruitful to research.
Most are prototyped in JavaScript/CoffeeScript and can be run in webbrowser + Node.js,
but often having a component of C/C++ and low-level/hardware/electronics component too it.

In rough order of time spent / maturity.

- Dataflow/flow-based-programming [Flowhub](http://flowhub.io) + [MicroFlo](http://microflo.org)
- [Design by Contract](https://en.wikipedia.org/wiki/Design_by_contract)
/ Contracts Programming: [Agree](https://github.com/jonnor/agree)
- Finite State Automata/Machines: [Finito](https://github.com/jonnor/finito)
- Equations & "spreadsheets": [Formulate](https://github.com/jonnor/formulate)
- Constraint Satisfaction: [1](./cstrain.coffee)
- Promises incl chains/composition
- Functional programming/composition
- [Behavioral trees](https://en.wikipedia.org/wiki/Behavior_Trees_%28artificial_intelligence,_robotics_and_control%29)
- [Decision trees](https://en.wikipedia.org/wiki/Decision_tree)

Combinations would make sense.

# Applications / experiments

- [dhang](https://github.com/jonnor/hangdrum).
MIDI controller / input device. Using recorded sensor data and simulation to determine triggering logic,
make software and hardware improvements.
- [rebirth](https://github.com/jonnor/rebirth).
Visual interactive sculpture. Using simulation of time-series to see animations of LED color.
- [syncrony](https://github.com/jonnor/synchrony).
How simulation and visual programming can help experiment in order to create interesting interactive art quicker.
- [microfridge](https://github.com/jonnor/microfridge).
Home electronics, control systems. Multi-level access, ending with full reprogrammability.
- [guv](https://github.com/flowhub/guv)
Automatic scaling of servers in cloud-environment.
Focus on tools for understanding config of a dynamic system reflecting changing world conditions.

# Interconnected ideas

Opinions that I bring to the table in relation to this work.

- Live programming
- Polyglot programming
- Static or quasi-static verification
- Model-based programming
- Self-documenting
- Behavior testing over unit-testing
- Data-driven and generative tests
- Integrated testing

# References

Logic programming

- [miniKamren](http://minikanren.org/) is a embedded logic programming DSL, that for instance powers Clojure `core.logic`.
[veneer](https://github.com/tca/veneer) looks to be the only maintained JavaScript/browser version,
but [microScopeKamren](https://github.com/asolove/microScopeKanren) has the explicit focus "inspecting logic programs as they run".

Pattern-matching programming

- [Senenca.js](http://senecajs.org/getting-started/), async-first pattern-matching library for Node.js microservices
- [Eve](http://witheve.com/), pattern-matching on records as a general purpose computational model.

Research

- [metamodels for structured interaction with machine intelligence](http://ppig.org/sites/default/files/2015-PPIG-26th-Sarkar-2.pdf).
Many good references to work on interactive machine learning, and end-user programming/debugging. No sure I buy premise of 'goal being ill-defined'.

Presentations

> ... The reason programming is so hard is because it is unobservable
[In Search of Tomorrow, by creator of LightTable](https://www.youtube.com/watch?v=VZQoAKJPbh8).

Books

* [Data oriented design](http://www.dataorienteddesign.com/dodmain/)

Established ideas

- [Python docstrings](https://en.wikipedia.org/wiki/Docstring), `doc()` and `help()` functions

Ideas applicable to standard programming

- Use a collection to define related functions, for instance implementation for each message type in a protocol. 
Can then introspect the collection to check completeness and common properties/invariants, or generate documentation.

Recent development

- [Node machines, spec for declaring meta info about JavaScript functions](http://node-machine.org/), and [Treeline](https://treeline.io/), a visual IDE built on top of it.

Model-based development

- [ImProve](https://github.com/tomahawkins/improve/wiki/ImProve), Haskell based DSL for high-assurance embedded applications, verified using SMT model checking.
Compiles to C/Ada/Modelica (and Simulink).

AST-based tools

- [OilShell: From AST to Lossless Syntax Tree](http://www.oilshell.org/blog/2017/02/11.html).
Offering two-way translation between source code, and parsed syntax tree.
[HN discussion](https://news.ycombinator.com/item?id=13628412)
