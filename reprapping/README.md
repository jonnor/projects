
# TapeXY

Experiment in super low-cost XY stage, for uses in digital fabrication techniques
which have minimal weight and forces on head (laser engraving, 3d-printing).
Inspired by the [RishaLaser](http://rishalaser.org) project.

[Youtube VIDEO](https://www.youtube.com/watch?v=5F9-HIbBYwc)

![TapeXY first prototype](./doc/tapexy-first.jpg)

Key features:

* Using Kapton tape as basis for gliding surfaces,
inspired by [a design](http://www.thingiverse.com/thing:3554) by Peter Jansen
* Using braided Nylon/Polyamid wire ("Spectra line") instead of timing belts.
Like on Tantillus and some Delta printers.
* Reproduction with primarily lasercutter (or CNC mill), in wood/acrylics.
* [CoreXY](http://corexy.com) kinematics

Parts:

* Base [FreeCAD](./tapexy.fcstd)
* Gantry [FreeCAD](./tapexy-gantry.fcstd)
* Pulleys. NinjaFlex/SemiFlex for friction. [FreeCAD](./pulley-ninjaflex.fcstd)
* Idlers. 8 pieces, consisting of 1x 608 bearing, 1x M8-40mm bolt and 2x [sideguides](http://www.thingiverse.com/thing:31216)

Done

* First working prototype of XY stage, driven by RAMPS/Cura
* Laser diode driver. DIY, linear constant-current source based on op-amp+NPN for 5volt supply

TODO:

* Make second iteration (with belts/pulleys in single plane)
* Design a proper belt/line attachment and tensioning system
* Design and make mount laser diode
* Add mounting holes for endstops
* Run tests with laser
* Design some self-adjusting system for friction parts

Later:

* Test cutting Kapton tape with laser. Both CO2 and with the 445nm diode
* Test removing idler bearings, and just let Nylon wire slide on Kapton?
* Reduce number of screws used, by having lasercut pins instead
* Prototype a matching Z-bed/table design
* Test FDM printing
* Test some lightweight CNC milling, like wax, PCB traces or engraving.
* Test a full-size laser envelope

Research

* Coefficient of friction.
[Table](http://www.goodfellow.com/catalogue/GFCat2C.php?ewd_token=Q4ZIFOAVRhE2dSOYkbUxPMdSBZyxXk&n=Ab6sV0qHM8iAeitFJGlgDA1qjQCrhQ&ewd_urlNo=GFCat26&type=30&prop=3)
Kapton/Polyimide: 0.45, Teflon/PTFE: 0.05-0.2, UHMW PE: 0.1-0.2.

## Related projects...

Of mine

* [Clothing](../clothing)
* [Rishalaser](../rishalaser)

Of others

* [MPlus One](http://www.thingiverse.com/thing:1104249) Cantilevered, moving bed like PrinterBot Simple and Smartrap, with lasered/milled structure.
Maybe has potential in combination with tape principle, possibly making even cheaper than a CoreXY?

## TapeZ

Moving-bed Z-axis stage for laserengraver/3d-printer to go with TapeXY.
Also uses Kapton tape and braided Nylon wire.

Existing wire/belt Z-axis:

* [SmartRapCore alternative Z](http://www.thingiverse.com/thing:896556)
* [Sli3dr](http://richrap.blogspot.co.uk/2014/07/3d-printers-big-printers-small-printers.html)
* [Igentis](https://www.youmagine.com/designs/ingentis-a-tantillus-variant)
* [Printxel](http://printxel.blogspot.ca/2012/12/printxel-community.html)
* http://forums.reprap.org/read.php?177,310249
* http://forums.reprap.org/read.php?160,170024
* http://forums.reprap.org/read.php?177,192178
* http://forums.reprap.org/read.php?14,319321
* http://forums.reprap.org/read.php?279,188149

A challenge is that Z-resolution/precision might be a bit low without gearing.
The hold-torque of a NEMA17 stepper might also not be enough to keep bed up.
Reduction gearing of between 1/4 and 1/9 is desirable.

## TapeCrane

My dad wants to build a cheap, large-scale 3d-printer (workspace with sides of 50-100cm)
which could be stowed away when not in used. For this he had two ideas for the kinematics.
One being a robot arm with two joints (elbow and wrist), working in the XY plane. Like SCARA.
The arm up/down or the bed would move to form Z axis.
The effector is cantilevered, making it tricky to keep rigid, and there are multiple
solutions for the inverse kinematics and singularity points.

The other idea was more like a crane, a [cylindrical robot](https://www.google.no/search?q=cylindrical+robot&tbm=isch).
It has the advantages of much simpler inverse kinematics (because no articulated joints),
and that the structure can be made more rigid in various ways:
Using tensioned wires (like a guy-wire), by supporting the far end, and/or using a (moving) counterbalance.

The most common configuration, has a rotating base. Alternatively, one can rotate just the (elevated) arm.
Either the whole arm can move back & forth to move end-effector, or the effector can travel along a static arm.

Unlike a cartesian or delta robot, several cylindrial robots could work into the same workarea.
They could potentially collaborate on a single (large) part, either for speed or multi-filament.
Or indepentently making different parts, or multiple instances of the same part.

Challenges:

* Mimizing weight of rotating joint, keeping it close to center of axis. For maximum speed
* Implementing the IK for cylindrical in firmware
* Cylindrical sectioned build area
* Decreasing precision at long-reach

TODO:

* Sketch a rough concept
* Test an arm beam, with tensioned wires on top+bottom for ridigity

## Experiments

### Kapton 608 bearing

.. Wednesday 14 Oct 2015, Oslo ..

Attempted to create a 608-sized bearing/bushing. 3d-printed, using Kapton tape added afterwards.
Using a V-profile to make the bearing support some axial load.
Initially 120 deg, but had to increase to 135-degrees to make it possible to insert inner part into outer ring.
Tolerances when 3d-printed (on a Ultimaker Original) seemed generally OK.

However, major issues were found when trying to assemble.
The Kapton tape was not particularly sticky to the print,
and would not easily fold around the V-profiles, especially the outer ring (with inward V profile).
When pressing the inner part of the bearing in, would easily
move the carefully aligned tape... Avoiding folds/creases was quite tricky.

I was able to succesfully assemble one bearing, with tape only on the inner part.
This rotated quite nicely, with not too much play
(considering the application of belt pulley, where some excentricity is quite OK).
Indicates that if one can figure out a practical assembly, the idea has some merit.

It could be that in larger scale, and with a more adhesive tape and, or with simpler geometry,
that the idea would have some merit. But with v-style 608 the process was too fiddly to be practical.

For TapeXY it could be possible to design an alternative idler/pulley solution.
For instance one could integrate the belt bottom/top guides, and use top/bottom of
rotating part for supporting the (tiny) axial load.

It is however desirable to be compatible with a standard solution,
or at least also allow a standard solution - since a hacked thing will (probably?)
never be as good as a proper bearing.

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

One application for such a gearbox, would be for a belted Z-axis of a printer using NEMA17 stepper.

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
