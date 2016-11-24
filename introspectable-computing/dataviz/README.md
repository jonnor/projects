
Programming should be more visual, and interactive - engaging our spatial-visual cognitive abilities more,
as well as our tendency to explore and develop intuitive understandings of complex systems.

There are several aspects of this

1. Structure of programs. What pieces they consist of and how these pieces connected and interact.
2. The data processed by our, including the possible ranges of data, and how data changes during execution.
3. Models of the domain that the program operates on/within. How program behavior influence, and is influenced by this.

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

Data in the FBP protocol is primarily represented as JSON.
Tools for operating with/on JSON, or JSON-like data.
Json Schema, JsonPath. `jq`


TODO: include notes from paper, 2015-2016.

Existing:

* Workbooks with built in plotting, like Matlab/Octave, iPython/Jupyter
* Spreadsheets, with built-in graphing tools. Like Execl/Google Docs.
* Data-visualization frameworks, like D3
* Scripting debugger, like Python scripts in gdb generate graphs. TODO: link blogpost, from HackerNews

Wanted

* Reverse-engineering of dataformats

## Models

Most evident when working with programs that interact with the "real-world",
for instance robotics, 3d-modelling, transportation.

Other programs which operate on/within an "environment".
This can be software-defined networking, cloud computing orchestration, user behavior analysis (for sales or UX).

With virtual reality and augmented reality, need and drive for more of these.


Support development of mental models, both initial creation and refinement.
Right now these only exist within heads of people, or in best case in an outdated documentation artifact.



"simulation-driven development".
Built an interactive model, which is used for simulations of scenarios.
Possible to drive programatically and with user-interface.

Similar to "model-based", but not attempting to be a mathematically rigorous system.
Model to the extent that is practical. Start rough, refine as needed and as understanding improves.

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

Related

* Brett Victor "Seeing Spaces"
