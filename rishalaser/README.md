
November 2014 I started building a [Risha](http://rishalaser.org) open source laser cutter,
for use at [Bitraf](http://bitraf.no) hackerspace in Oslo, Norway.


Customizations
============
Changes made to original build.
In general to minimize custom made parts, to better accomodate cutting usecase
and because portability is not that important.

* 2 watt 445nm diode instead of 750mW 405nm
* Somewhat larger work area: A3 (297 × 420mm)
* Stock CPU cooling fan + stock laser diode host bracket instead of custom mill
* Stock RAMPs motor driver board instead of custom electronics
* Custom laser diode driver (details TBD)
* Using M5 threaded-rod instead of 5mm slick rod for slave axel

TODO
=====

* Print rest of parts
* Complete mechanical assembly
* Test drive without laser
* Test using A9288 stepper driver as current source
* (possibly) Adapt laser mount to fit customization
* Test drive with laser
* Implement laser heatsink
* Adapt eletronics enclosure to fit customizations
* Write docs/procedures for safe use
* Run BSU workshop

Worklog
========

December 1. 2 hour
Documentation of ideas

November 29+30. 8 hours
Fixed and tuned the two Ultimaker 3d-printers at Bitraf.
Printed around half of the parts.
Used "line" type support in Cura, worked very nicely. 33% infill.
The parts are in general very printable.

November 25. 6 hours
Researched the various options for laser diodes.
Ordered all electronics and hardware parts that cannot be sourced locally.
Estimated delivery for all parts between 10-20 December.
Most mechanical parts should however be in place first week of December.
Sourced from Amazon, Makeblock, E3D, DealExtreme EU.
Local sourcing planned from Clas Ohlson.

October
Talked to Moushira about project at Open Hardware Summit Rome.

Ideas
======

Reduce height
-------------
Reduce the height of the traversal and carriage.
Right now X-motor is mounted very high, causing
the entire machine to be about twice as tall as needed.
It complicates adding an enclosure on top,
is more fragile due to sticking out of structure.
The laser diode mount and Z adjustment also needs to
be extra tall as a consequence.

Note: It does however very easily allow to engrave/cut onto
work objects which are fairly tall. Up to 40mm or so.

It also seems that the motor mount is such that it limits
the Y axis because it hits the corner. Could be that this
is just same distance needed for the laser diode head though?

Could also be that if turning the laser diode assembly around,
one could add ~40 mm working space along Y by having a cutout
in the eletronics compartment. Would complicate the design of
the corners somewhat to fit the threaded rod though?

Main challenges are:

* Allowing to still engrave onto tall objects
* Finding space for Y belt+rods that does not conflict with X belt+rods
* Finding good mounting for the X motor

Current idea.

* Move Y belts up to same level as Y rods
* Put the X belt and rods underneath Y belt, close to surface



Diode driver
------------
A9288 stepper driver could perhaps be used as constant current source.
Potential problems:

* Does not operate cleanly when continiously driven against current limiter
Action: TEST on dummy load.
* If current source is misadjusted or pot wiper becomes dirty, risk of overcurrent
Action: ? implement an extra protection mechanism

If A9288 driver does not work, fairly easy to create a
linear driver using 5V power supply, 0.1 ohm series resistor to measure current,
opamp to convert to voltage and regulate, and a NPN/N-channel to drive load.


Galvo-drive
------

When engraving or cutting thin material,
cutting from an angle is not that much of a problem.
So one could maybe use galvonometer mirrors to move the laser around.
This is sometimes used in textile industry.

This minimizes the amount/scale of movable parts. On the other hand,
higher precision parts are needed, and control+calibration is trickier.

Commercially available galvos and drivers might make it too expensive,
and printed galvos might not be good enough.

Main problem is the open beam, securing the workarea.
Calibration would be an issue also after moving it,
so practical portability might not be so much higher.

Hack using loudspeakers as galvos
http://www.instructables.com/id/Arduino-Laser-Show-with-Full-XY-Control/


Add+substrative electronics production
-----------------------------

Printed, laser-tuned resistors

In SMD production of resitors (and capacitors) a precise
value is often obtained by measuring and trimming the
deposited material using a laser. If one can print
resistors using FDM.
Main challenge here is the measurement, which requires
probing automatically and precisely. On the other hand,
such probes would be needed for automatic functional
verification as well.

