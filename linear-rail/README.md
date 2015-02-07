
Linear-drive stage
==============
Experiment in increasing reproducability of CNC machines.
Target machines include (in order) lasercutter, 3d-printer, mill.
Attempting to reduce needed vitamins: stepper-motor, belts/screw

Three major sub-systems

* Linear electromotor
* Closed-loop feedback system
* Rail mechanics

Key ideas
-----------

* Using microstepping to avoid requiring too many poles
* Using closed loop feedback to get precision
* Stage split into sections
* Each section self-contained: mechanics, motor, electronics
* 8-20 poles per section
* An end-section contains microcontroller, power regulation
* Using standard magnet/iron + wound coil design initially
* Primarily fabricatable using CNC mill, secondarily 3d-printer. Incl PCB.


Electromotor section
------------

* PCB mounted on back of rail
* Wires from magnets coming directly through PCB
* Serial data bus + power connectors between section PCBs
* Optional direct power connection
* Addressable latch, parallel-out with IC buffers/driver, or
* stepper motor drivers, or switched-reluctance driver
* Efficiency a secondary concern, power losses accepted for now
* Levitation effect not initially targetted

Rail mechanics
---------------

* Use a simple roller-bearing + guide initially
* Rotation around drive axis not priority to lock
* Some friction and variability acceptable due to closed-loop

Feedback system
----------------

* Optical linear encoder
* Probably relative
* Use stock component first, aim to develop self-reproducable one

Prototyping
------------

Testing closed-loop first system using a traditional linear stage,
then the linear drive without closed-loop before combining the two.

Aiming for

* 1 mm accuracy/repeatability
* ~120 mm stage length
* 10 mm/second speed, slow acceleration

Using

* ~ 4 mm between poles, 1/4 microstepping
* ~ 40 mm per section

Initial testing done with laser pointer?

TODO
-----

* CAD out conceptual design of carriage
* Tool for winding coils

References
-----------

* [Hackaday: Linear tubular motor](http://hackaday.com/2013/02/04/building-a-linear-motor)
* [Reprap: Wire wound] (http://forums.reprap.org/read.php?88,12556)
* [Reprap: Printable linear drives](http://forums.reprap.org/read.php?1,5898) (pictures of working commercial design)
* [Texas Instuments: Switched Reluctance Motor Control](http://www.ti.com/lit/an/spra420a/spra420a.pdf)
* [Good diagrams of stator/rotor teeth](http://www.alciro.org/alciro/Plotter-Router-Fresadora-CNC_1/Motores-reluctancia-variable_42_en.htm)
