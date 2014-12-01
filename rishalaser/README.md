
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
* Run workshop

Worklog
========

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
Right now X-motor is mounted very high.

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

