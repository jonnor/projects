
The [RepRap](http://reprap.org/) project aims to build open-source self-replicating machines.
FDM 3d-printing is one of their main pillars, but the ideas are applicable to any type of fabrication technique. 

# State of FDM 3d-printer reproducability

As of mid 2016, reproducability in terms of number of parts is typically around 50-60%.

The [Reprap Snappy](https://www.youtube.com/watch?v=3b7BE8HRyWw) is at the forefront, with 73% reproduability.
It is a notable improvement by having basically no screws (using snap/click-fit pieces instead),
having the linear motion be printed slides with rack+pinion drive.

But still has one 686 mm bearing (for extruder idler) and uses 2x threaded rods (for the Z axis).

## Reproducable, commonly done

* Structural connectors
* Extruder mechanics

## Reproducable, but not typically done

* Drivechain. Timing belts or rack+pinion
* Machine structure. Usually wood/acrylic or aluminium profiles.
* Linear motion guides. Usually LMx linear bearings on steel rods.

## Not reproducable, specialized

* Hotend. Consists of several pieces, usually machined of metal on a lathe.
[Ubis/PrintrBot hotend CNCed](https://www.youtube.com/watch?v=U-m8Jrj5zDA)
* Extruder drive gear
* Motor controller electronics

## Not reproducable, generic

* Drive motors (stepper/servo). Found in old computer equipment
* Cooling fans. Found in old computer equipment
* Power supply.
Being able to 3d-print a generator, powered by natural resources or human power would be great.
* Limit switches. Should be able to use any kind of switch really, including two wires touching.
But not seen any 3d-printed designs.


# TapeXY

Moved to [TapeCore project](https://github.com/jonnor/tapecore/blob/master/README.md#tapexy)

## Beam structures

Couple of designs for lasercut beams, mostly untested.

* I-beam. [FreeCAD source](./ibeam-20.fcstd)
* II-beam. [FreeCAD source](./ibeam-30.fcstd)

TODO

* Check squareness and flatness of a fabricated beam
* Calculate stiffness, and do experimental test

Tools for calculating stiffness of beams

* http://www.had2know.com/technology/I-beam-calculator-moments-engineering.html
* http://www.engineersedge.com/section_properties_menu.shtml
* http://www.amesweb.info/SectionalPropertiesTabs/SectionalPropertiesIbeam.aspx
* https://en.m.wikipedia.org/wiki/Deflection_(engineering)
* https://en.m.wikipedia.org/wiki/List_of_second_moments_of_area

## TapeZ

Moved to [TapeCore project](https://github.com/jonnor/tapecore/blob/master/README.md#tapez)

## TapeCrane

Moved to [TapeCore project](https://github.com/jonnor/tapecore/blob/master/README.md#tapecrane)

## Experiments

### Kapton 608 bearing

Moved to [TapeCore project](https://github.com/jonnor/tapecore/blob/master/README.md#kapton-608-bearing)

## Extruders

In the typical design (as of 2016), filament is driven with hobbed bolt/extruder gear, pressed against an idler.
Because of the small contact area, the press is very high.
Therefore a metal bolt is needed, and an bearing as/for the idler.
It also relies on the pre-existing bearing(s) in the extruder stepper-motor.

It should be possible to incrementally improve this to remove the bearing
(while still using a special hobbed bolt), with something (more) printable.

An alternative design would be to distribute the force along a larger area.
There are some example of this idea on Thingiverse:

* [Filament pusher](http://www.thingiverse.com/thing:1664969), using rollers wheels and groved disc

## Endstops

For XY the precision or repeatability is not so important, around 1 mm would be fine.
However for Z it is desirable to have repeatability on order of 0.1mm.
Ability to put the endstop on the head and use it as a probe is also highly desriable.

Various options for detection principle is possible.

* Conductivity (mechanical contact)
* Optical (ambient light or active light)
* Magnetic (hall effect)
* Inductive (magnetic field)

A mechanical contact using two wires, and printed spring should be possible.
Challenge is noise from bounce, and repeatability - as well as ensuring it can withstand the wear.
Using some lever or other mechanical advantage principle
to connect to the moving part may give flexibility to more easily design good spring/contact mechanism.

An optical also possible. However adding an LED and LDR/phototransistor does not lower the part-count.
Non-contact means durability should not be issue. 
May be easily extendable to more general purpose, linear- or rotary encoders.

Inductive switches need a metal target. The pre-built ones are already popular used as Z-level probe.
They consist of an oscillator, an inductive coil, measuring the voltage/current going through and acting on that.
Here is a [Teensy-based DIY example](https://sehrainder.wordpress.com/2013/12/11/a-diy-crude-inductive-proximity-switch/).
If the microcontroller is fast enough (and frequency low enough), it maybe possible to remove the peak-detector in software.

May be able to use wire as the inductive sensor. Or use a coil wound from same wire as for 3d-printed stepper motor.
One can [compensate for a small inductance in the sensor element](https://e2e.ti.com/blogs_/b/analogwire/archive/2014/06/10/inductive-sensing-how-to-use-a-tiny-2mm-pcb-inductor-as-a-sensor)
using a series inductor.

Maximum reduction in partcount and assembly of using printable endstops, would also mean eliminating their wiring.
This could maybe be done if the motors of each axis had smart driver-electronics with neccesary endstop logic built in.

### Work by others

* [3d-printable endstop](http://www.thingiverse.com/thing:389006), using copper wire and a spring.
* [3d-printable endstop housing](http://www.thingiverse.com/thing:756126), using a standard microswitch

## Power

A typical reprap, without a heated bed, requires around 100 watts peak. Average will maybe be 30-50 watts.
This should be doable by human power, or pretty small wind/solar installation on a good day.
Solar is not so interesting for reprap-purposes, as the solar-cells require special manufacturing -
through arguably the techniques are same as for the semi-conductors of the controller electronics.

A wind-generator which could be hand/foot cranked as a backup would maybe be the ideal.
This is essentially just a motor in reverse, so can hopefully be done without adding materials/part types,
compared to when also having 3d-printed motors.

`TOOD: test the PrintBot average and peak current draw`.


## Ideas

* Use a lightweight CNC milling head with thin tool to precicely score/drill acrylic.
So that one can just snap along these edges, and widen hole with hand-drill. To make more reprappable.
Challenge: limits design to straight external edges?

### Cheap closed-loop solutions

Have camera on head. Optical recognition.
For laser cutter. First move slowly, 

### Ninjaflex belted gearbox

Most 3d-printed gearboxes use meshing gears of PLA/ABS/Nylon.
Using a flexible timing belt to connect them instead has advantages:
* Less wear, since belts distribute force over a larger area.
Most wear should be on belt, allowing independent replacement. Also more wear tolerant.
* More silent, since belts are of softer material
* More tolerant for bad bearings (excentric or axial motion)

If well designed, could also be more overload tolerant as well
- belt should slip before damaging pulleys.

The belt could be printed out of NinjaFlex ([work by others](http://www.thingiverse.com/search/page:1?q=ninjaflex+belt&sa=)).
With some clever work on axel, bearings and belt-tensioner, it may be possible to make it zero-vitamins.

One application for such a gearbox, would be for a belted Z-axis of a printer using a standard NEMA17 stepper.

## Printed belt tensioner

The standard solution for tightening belts is to have the bearing/pulley axel in a slot,
and then a bolt which the axel rests against, on the side the belt pulls.
Tightening the bolt, pushes the axel further up in the slot, and tightens the belt.
This works well, but requires a couple of vitamins (bolt, nut)

An excentric wheel, where radius increases when turning, could replace the bolt.
To keep it from just rotating, a ratcheting mechanism on a spring would lock it.
To loosen belt one would push out the ratchet.

## References

Work by others

* [3d-printed bushing](http://www.thingiverse.com/thing:1196801), replaces speciality linear bearings
* [3d-printed beam surface](http://www.thingiverse.com/thing:9080/#comments)

# Interesting designs

* [Delta-T, rail-free, wire-based delta](http://forums.reprap.org/read.php?1,525804)
* [SkyDelta, rail-free, wire-based delta](https://groups.google.com/forum/#!topic/deltabot/Jj6vyPf7jJ8)
* [Cantilevered CoreXY printer](https://www.youtube.com/watch?v=6EtJfaiQ9H0)

# Electronic discharge machining

Looks promising as a non-contact method of machining metals.
Particularly for small/fine things, like PCB isolation engraving or.

Can be used with a wide array of tool-heads, to make custom shapes.

Disadvantages are heavy tool erosion. But maybe can use 0.5 mm grafite leads from pencils??

Needs some regulation circutry which constantly keeps the head at appropriate level from workpiece.
Bonus sideeffect : built-in Z-height autolevel.

References

* [YouTube: Principle test from Fablab India](https://www.youtube.com/watch?v=Zf7_GY7GMV40), part of Fabacademy 2016.
* [YouTube: Principle test from 2012](https://www.youtube.com/watch?v=GVSST58x_FE). Looks to be working quite well.
* [RepRap forums: DIY EDM](http://forums.reprap.org/read.php?1,262452)
* [Hackaday.io: Not Your Father's EDM](https://hackaday.io/project/3232-not-your-fathers-edm). Last update in Feb 2015.
