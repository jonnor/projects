# Introspectable programming

Researching making programs and systems that are *introspectable*.
That is, *programs that know what they are* and *how they work*,
and provide facilities for *viewing*, *extracting* and *querying* this
information.

And with these capabilities in place, what

Note that this is a broader use of the word 'introspection' compared to
typically in programming, which usually is limited to very primitive information, like types.

# Motivations

There are 3 primary motivations for this work. From most concrete to most speculative:

1) Increasing the ability of experienced programmers to reason about
non-trivial systems, and write more advanced and robust software.
2) Helping blur the lines between 'programmers' and 'non-programmers' (domain experts, interested users),
by making the system more inviting and self-describing.
3) Open up the possibility for self-governing systems and intelligent agents.
Where the entity using the introspection information


# Areas of research

Some of the areas I have done work in, or think could be fruitful to research.
Most are prototyped in CoffeeScript and can be run in webbrowser + Node.js,
but often having a component of C/C++ and low-level/hardware/electronics component too it.

In rough order of time spent / maturity.

- Dataflow/flow-based -programming [Flowhub](http;//flowhub.io) + [MicroFlo](http://microflo.org)
- Finite State Automata/Machines: [Finito](https://github.com/jonnor/finito)
- [Design by Contract](https://en.wikipedia.org/wiki/Design_by_contract)
/ Contracts Programming: [Agree](https://github.com/jonnor/agree)
- Equations & "spreadsheets": [1](./grids.coffee)
- Constraint Satisfaction: [1](./cstrain.coffee)
- Promises incl chains/composition
- Functional programming/composition
- [Behavioral trees](https://en.wikipedia.org/wiki/Behavior_Trees_%28artificial_intelligence,_robotics_and_control%29)

Combinations would make sense.

# Interconnected ideas

Opinions that I bring to the table in relation to this work.

- Live programming
- Polyglot programming
- Static or quasi-static verification
- Model-based programming
- Behavior testing over unit-testing
- Data-driven and generative tests
- Integrated testing

# References

Established

- [Python docstrings](https://en.wikipedia.org/wiki/Docstring), `doc()` and `help()` functions

