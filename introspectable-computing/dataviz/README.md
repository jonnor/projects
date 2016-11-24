
Software development should be more visual, and interactive - engaging our spatial-visual cognitive abilities more,
as well as our ability to explore and develop intuitive understandings of complex systems.

There are several aspects of this

1. Structure of programs. What pieces they consist of and how these pieces connected and interact.
2. The data processed by the program. Including the possible ranges of data, and how data changes during execution.
3. Models of the domain that the program operates on/within. How program behavior influence the environment, and is influenced by it.

Each of these aspects may be useful on its own, however the major benefits might not appear until
each of the apects are present *and* that they are interconnected, supporting eachother.

## Visual programming

* Node-based dataflow programming, as used in [Flowhub](http://flowhub.io).
* Imperative visual programs, like MIT scratch.
* Ladder-based programming, used for PLS
* Visual graph notation used in finite state machines.
* Callstack analysis/visualiztion of imperative/functional code.


## Datavisualizion

`{ x: 1.0, y: 3.0 }` (most likely) represents a point in 2d space.
It should be visualizable and manipulatable as such.

Idea: Use "structural typing" (ref TypeScript) to decide how data may be treated.
Benefit: Explicit type information, and agreement on type system not neeed

Data in the FBP protocol is primarily represented as JSON.
Tools for operating with/on JSON, or JSON-like data.
Json Schema, JsonPath. `jq`


TODO: include notes from paper, 2015-2016.

Existing:

* Workbooks with built in plotting, like Matlab/Octave, iPython/Jupyter
* Spreadsheets, with built-in graphing tools. Like Excel/Google Docs.
* Data-visualization frameworks, like D3
* Metrics platforms with support for graphs. Like New Relic Insights
* Debuggers with support for graphs. Like [ddd](https://www.gnu.org/software/ddd/)
* Scripting debugger, like Python scripts in gdb generate graphs. TODO: link blogpost, from HackerNews
* Visualizer nodes, or custom UI on nodes in node-based-programming. Like PureData

Wanted

* Reverse-engineering of dataformats and/or protocols, visually?

### Prerequisites

For datavisualization, there needs to be a way in the programming language/framework/toolchain
to find the places where there is data of interest, and to be able to observe the data there.
In order to allow visual manipulation of the data, must also be able to inject manipulated data at such points.

The exact mechanism is not important, however:
Since programs often run on devices, the data-observation should be network capable.
Since issues often happen in production, production systems should have the system enabled.
This implies that it cannot disturb normal production, including performance.

## Models

Most evident when working with programs that interact with the "real-world",
for instance robotics, 3d-modelling, transportation.

Other programs which operate on/within an "environment".
This can be software-defined networking, cloud computing orchestration, user behavior analysis (for sales or UX).

With virtual reality and augmented reality, need and drive for more of these.


Support development of mental models that are executable. Both the initial creation and refinement.
Right now these only exist within heads of people, or in best case in an outdated documentation artifact.

### Simulation-driven development
Start by building/using an interactive model, and specifying a few usage scenarios.
Run simulations, driven programatically and with user-interface.
Build up learning about the domain, exploring what is perceived as known (assumptions),
and mapping what is unknown "terra incognita" - use to decide areas of focused research/testing,
to (in)validate assumptions and make more things known.

Similar to "model-based" development, but not attempting to be a mathematically rigorous system.
Model to the extent that is practical. Start rough, refine as needed and as understanding improves.
Use the model as part of the implementation, as part of (automated) verification, as part of
debugging tools for live system.

Existing

* Physics-based component simulators in EDA (electronic design automation) tools, like SPICE.
* Physics engines, as found in games
* FEM/FEA (finite element analysis), used for structural engineering in CAD (computer aided design), like Calculix in FreeCAD
* Raytracing engines, simulating how light behaves. Cycles in Blender
* Sales funnel, like in Google Analytics

Wanted

* Computer networking, including latency, throughput, unreliability. Wireless
* Energy consumption of embedded device. Communication, computation. Storage
* Processor memory, including caches
* Distributed computing systems, both networks, computational resources, program behavior.
* Flying-robotics, like multicopters
* Wheel-based-robotics, like folkrace
* Energy production, via solar cells.
* Energy production, via windpower
* Digital fabrication machines, subtractive (CNC/laser) and additive (3dprinter)
* Sound propagation in space
* Propagation of information though a social network. Facebook social graph?

Related

* Brett Victor "Seeing Spaces"
* Idea of first building a toolkit for the problem domain, that allows to experiment in that domain. Alan Kay?

### Prerequisites

Need a way to observe a programs effects on its environment, and.
For simple programs/models this may be just input/outputs of the program.
For more complex, multi-faceted programs some environment interactions may be "internal",
important that these still can be found and observed.

For simulations, important that one can inject a model into a program.
Drive program, observe changes in model. Or drive model, observe changes in program.
For pure simulations, desirable to disable the real environment influence/manipulation.
Desirable to drive model and real behavior in the same system, in order to directly observe
discrepancies.

Since models represent a system behavior over a (wide) range, important that one can
collect data about the real system, to validate the model with.


## Unrelated

[Tools for Thought by Howard Rheingold](http://www.rheingold.com/texts/tft/1.html)
