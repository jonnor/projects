

Additive digital manufacturing technicues (3d-printing) brings
many new possibilities and challenges to electronics.

As of early 2015, there are several developments happening
that enable afforable additive manufacturing of conductive material
(and thus basic electronics):

* Specialized printers for electronics. Ex: Voxel 8
* Electronically conductive filament for normal FDM/FFF printers. Ex: ProtoPasta, Leapfrog Exotic

It may also be possible to print channels in non-conductive
material and then fill these with low viscocity conductive material (ex: Bare Conductive).



Experiments
===========

High-power active switch
--------------------------

![First working power switch](./doc/powerswitch-first.jpg)

[FreeCAD](./power-switch.fcstd)

The high-current paths of circuit are connected directly to/from the IC
instead of going through deposited traces, side-stepping issues of poor conductivity.
Power handling mostly limited by not having a heat-sink.
Traces currently done using channels in the PLA filled with Bare Conductive ink.
Dedicated resistors uneccesary as trace-lengths are adapted to make suitable resistivity.

Vitamins required:

* 1x TO220 N-channel MOSFET with pinout Gate,Drain,Source (ex: IRF244N, BUZ10/11/12)
* 3x M3 screws

TODO:

* Attach top part to bottom part. Press/click-fit?
* Close wire holes on backside
* Design way to attach Gate-leg as spring in Vin+ hole
* Find way to document which port is what. Embed +, -, O (out) into frontwall?
* Tweak button surface, better indicate where to press, rigidity
* Add external input for gate signal!
* Fix traces to be producable by printed mask w/Bare Conductive
* Run high-current test
* **Publish on Thingiverse**
* Ensure printable with ProtoPasta (pending delivery...)
* Test more advanced control configs, captouch,toggle/RF/timer etc

Similar technique could for instance be used to create:

* Audio power amplifiers, using LM3886 or similar
* Stepper-motor drivers, using microcontroller + H-bridges [avrstmd](http://www.avrstmd.com)



Braindump
=========



Key process parameters
--------------------

* Conductivity of material
* Capacitance and inductance
* Strength and flexibility of material
* Bonding to other conductive materials: component, PCBs etc
* Bonding to non-conductive material


Thoughs on designing for print
---------------

**Resistance**

In the forseeable future (2015) of additive manufacturing,
the conductive materials are pretty poor compared to in conventional 
electronics manufacturing, having a factor 100-1000 higher resistivity.
The significant resistance of available conductors will mean that many
conventional designs will work poorely when produced in this new way.
It might be required to re-think not just the manufacturing, but also
(parts of) the design of electronics to be able to make working systems.
The significant resistance can however be used to reduce or eliminate
actual resistors, at least in applications where high tolerance is not needed.

**Hybrid**

It is tempting to try to make systems where everything is 3d-printed.
In the forseeable future however, we need to reuse existing technology where
makes sense, and 3d-printing where that makes sense.
The obvious place for additive manufacturing, is the assembly of components into a (sub)system
(traditionally: PCB board manufacturing).

However, more importantly one can potentially now produce sensors, actuators and enclosures
*in the same process* as the functional system, which in conventional
thinking are only somewhat-overlapping problems. This opens up new possibilities in
integrated systems design, if one re-thinks the exising boundaries.

**3D**

Conventional electronics is nearly almost only oriented around 2d. The added dimension
should enable more compact designs, as well as more flexibility in integrating/interfacing
with other 3 dimensional objects.

**Scale**

Electronics is traditionally very oriented around standardized, reusable components.
Each component is cheap because it is produced in the millions and can
be used for many purposes. However there is a significant cost in producing
the custom parts, both for connects the re-usable components and providing
chassis/enclosure and interfacing. Sourcing and stocking all the different
components also incurrs significant costs.
The current processes there also scale well with high quantity
(or conversely, scales poorely with low quantity). This naturally
opens up for alternative technologies for low-quantity manufacturing,
or where. 

Some factors that could possibly exploit to also scale up to medium-size quantities:

* Just-in-time manufacturing, saving storage costs
* Distributed manufacturing, saving shipping costs
* Universality, every system made up of connected digital controllers + custom 3d-printed parts.

**QA**

Traditional manufacturing methods also have very well established quality assurance systems.
Successful commercial use of additive manufacturing will likely require the same.
Some additional challenges are introduced because of the currently still unmature/developing
nature of the materials and processes. Designing ways to do effective & efficient QA on
a low-quantity scale is seemingly an unsolved problem.

**Recycling**

If all the components (potentially reusable, or individually recycable)
are baked into the object being produced, with no way of dissassembling,
this requires new solutions for recyling.
The conductive material itself also needs a way to be recycled.

Software (EDA/CAD/CAM)
-----------------

Traditional EDA tools very limited 3d-capabilities.
Traditional CAD/CAM very little knowledge about electronics.

Want to at least be able to import netlists from schematic capture,
and have a way to establish connections with traces. Each unfulfilled
connection should be shown as warning/error.

One could try to do layout primarily in multi-layer 2d EDA,
and then let adapt this to 3d-printing by doing vertical paths
instead of vias.
Problem is that few (if any?) tools will allow placing components in
more than two layers (front+back). It is also assumed that these two
planes are parallel, severely limiting component placement.
Orientation of components is limited to rotation around Z-axis,
again limiting layout (and thus complicates routing).

Since traces have non-neglible resistance, having automatic calculation
of trace resistance for a given 3d-path is critical. A warning when
trace resistance is too high for design requirements massively beneficial.
Ideally the auto-router would know about resistance, and be able to lay out traces
to create a given resistance.

Since it will be possible to print whole components in some cases, like
connectors, a way of representing and manipulating such components would be needed.
Having a resuable (ideally shareable) library should significantly speed up development process.

Tools
------
* Finite Domain Solver (fd.js) for calculating lengths/crossection/resistance
* [KiCAD](http://www.kicad-pcb.org/): EDA tool, including schematic capture, and many component 3d-models
* DigiKey, has huge [repository of 3d-models](http://www.digikey.com/en/resources/3d-models)

Calculating connections
-----------------------

Assuming cross-section same along whole path

    R = ρL/A

    R: fixed by requirements in circuit design.
       Ratios to others might be more important than exact value
    ρ: fixed by material property. Likely need calibration
    L: variable, highly influenced by component positions 
    A: variable, constrained downwards by minimum nozzle/lines,
       constrained upwards by size limits of single conductor
       0.4*0.4mm <-> 4*4mm, factor 10*10 = 100

Challenge: resistance of paths different between layers than within a layer.
Try to keep them the same for all paths?

Possible strategy:

1) Attempt to solve for A, keeping L constant
2) Modify path to be longer by not following path directly

Step 2 can potentially be done in discrete steps:


Direct line along path

    *-----------------------*

Multiple lines parallel to direction of path. N lines, X % of path

      -------------------
      |                 |
    *-|  ---------------    *
         |                  |
         ---------------------

Multiple lines perpendicular to direction of path. N lines, Y millimeter extension

      --- ---
      | | | |
    *-| | | | |-*
        | | | |
        --- ---

All these are periodic patterns, which allows to calculate effective resistance per period
then multiplying up to get total for path.
Could also do more complex paths in 3D.


Coping with variance in conductivity
--------------------

Run various testcases on conductivity.
Establish relationships between

* Resistance versus number of lines
* Resistance versus number of layers
* Resistance versus length
* Resistance variability/repeatabilit
* Resistance versus temperature, w/without curing
* Resistance over time

Trimmable.
Circular/linear track with viper (potmeter)
Cutting off pieces of pattern, or joining together



Possible testcases
-------------

Sensors

* Touch (capacitive?)
* Proximity (inductive?)
* Vibration, low-frequency
* Vibration, audio

Control systems

* Momentary switch (non/inverted)
* Latched switch. SR-latch
* Toggled switch. T flip-flop
* Timers (astable, monostable)
* RF controlled switch (433Mhz/BT/WiFi)

Power connectors

* Mains/Wall socket plug. 110/230V
* USB male&female. 5V

It would be beneficial to establish best-practices for
various classes of electronics (sub) circuits:

* Discrete digital signal processing.
* Analog signal processing.
* Embedded microcontrollers.
* Power electronics


