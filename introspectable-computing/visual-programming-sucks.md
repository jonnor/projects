
# Things that suck about visual programming

Programming is primarily a text-based and text-oriented venture, today in 2016 as in 1960 when we only had a teletype.
This is not an attempt to explain why this is the case.
But I will list some things which I consider limit adoption among currently available tools.
Initially this was prompted by a discussion on Facebook on whether one should teach kids visual programming,
or go straight for conventional text-based programming languages/tools.

'visual programming' is a broad category, and I will primarily focus on dataflow and flow-based programming,
where the program is represented as a `graph`, with `nodes` being (possibly stateful) components which *act
on data* coming in on `inports` and *sending data out* on `outports`. Edges in the graph connect nodes together.

Examples of this paradigm include

* Pure Data / Max MSP
* LabView
* NoFlo / MicroFlo

Less about imperative ones, like MIT Scratch.
Unfamiliar with them, though I expect that many things may apply also there.

# The shitlist

## 1. Not embeddable.
Integrate into own programs
## 2. Cannot run standalone, without GUI.
Problematic on devices where one does not have or want a GUI system.
Or where just want to expose a custom GUI on top of a program built with the IDE
## 3. No seamless transiton between assembling visual components and working with code
All the systems have a way of defining a component/block.
Usually also a way to install more, via plugins/modules etc.
But often one cannot see the code of a component, or create a new one from the IDE
Should be able to pick and chose what to use.
## 4. Not version controllable, or diff-able
Makes it hard to collaborate in a team. Code reviews etc
## 5. No keyboard-friendly workflows. Even the most common operations can often only be done with mouse/touch.
Insert/delete node. Move into node / back out. Search to find node/component. Disconnecting/connecting
## 6. Lack of testing tools/workflows.
Automated testing, static and dynamic analysis are critical for software verification.
## 7. Second-rate debugging tools/techniques.
One programs in terms of data and nodes, but usually there is no equivalents of the
debugger, breakpoints or stacktraces that one has in imperative programming.
Sometimes one even has to resort to debugging on obscure generated code...
## 8. Lack of how-to and best-practices documentation
For imperative and object-oriented programming you'll find lots of
books, tutorials, videocasts, conference presentations, blogposts and Q+A about almost any aspect of
programming, from getting unstuck to how to approach certain types of problems.


# Hope?

In 2013, we started working on Flowhub (then called NoFlo UI).
How do we fare with respect to these matters?
`0% = worst`, `100% = really good`.

Focus on the more general purpose runtimes, NoFlo/MicroFlo.
Not so much the specialised ones, like imgflo and MsgFlo.

## 1. Embeddable. `90%`
NoFlo is just a JavaScript library. The provided 'runner' programs/entrypoints like
noflo-nodejs, grunt-noflo-browser and noflo-runtime-msgflo are wrapper tools around this.
MicroFlo can be used as a header-only C++ library.

## 2. Run standalone `90+%`
There is a strict separation for NoFlo, MicroFlo between the runtime (which executes) the program,
and the IDE (Flowhub). The IDE is optional, and communication happens over a the FBP runtime protocol.

## 3. Visuals+text integration `50%`
Flowhub will, with some exceptions, show the source code of components if runtime supports it.
And is basic support for adding/changing components.
However, NoFlo sends compiled JS for CoffeeScript components and you cannot use/add external dependencies.
MicroFlo does not support showing nor editing components from Flowhub.

Both NoFlo and MicroFlo can be programmed purely with textual tools, including a textual DSL for graphs.

## 4. Version control `20%`.
Flowhub has some notion of versioning built-in. But it is not persisted and only offers linear undo/redo, and one cannot review changes.
Flowhub can also make git commits, but only allows adding changes on per-file level. And again, no way to review the changes.
Because Flowhub cannot easily [save graph/component changes](https://github.com/noflo/noflo-ui/issues/64) back to disk (via runtime) but only has current state inside the browser,
it is hard also to use existing tools.

Graphs are stored as pretty-printed JSON, but it takes quite some effort to grok a diff.
Tools for preparing this is only in idea stage, [fbp-diff](https://github.com/jonnor/fbp-diff/blob/master/README.md)

## 5. Keyboard friendlyness `10%`.
Basically nothing in Flowhub usage can be comfortably done from keyboard.

## 6. Automated testing `50%`.
NoFlo is very testable using conventional JS tools like Chai/Mocha, thanks mostly to its embedding API.
However such tests don't show up in Flowhub, can't be written nor ran from Flowhub.

[fbp-spec](https://github.com/flowbased/fbp-spec) allows defining tests as data, and running against any compliant FBP runtime.
There is experimental integration in Flowhub, however it has not been released and running is [currently broken]().
Via a compatibility wrapper, it should eventually also allow running existing Mocha tests.

## 7. Debugging `10%`
Flowhub supports showing data on individual connections, as text, as it comes through (and a little bit of history).
The way data on connections is presented (no way to see relationships) makes it very hard to find/understand any non-trivial issue.
There is no built-in support for retroactive debugging, configuring something like a breakpoint, or searching/matching in data.

[flowtrace](https://github.com/flowbased/flowtrace) has a dataformat and tools for retroactive debugging, with basic support
in NoFlo for capturing , and playing back to Flowhub. [Lack of subgraph support](https://github.com/noflo/noflo-runtime-base/issues/32)
makes it not-that-useful at the moment for non-trivial programs.

## 8. How-to/bestpractice docs `0%`
There is essentially nothing? Maybe 10 answers on StackOverflow 'noflo' cover how-to-program,
and couple of notes in [Thinking Flowbased](https://github.com/flowbased/thinking-flowbased).
No tutorials, demo/walkthroughs, blogposts etc...


