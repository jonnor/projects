
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

