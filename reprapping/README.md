
The [RepRap](http://reprap.org/). 

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

`TODO: move to separate repo`

Experiment in super low-cost XY stage, for uses in digital fabrication techniques
which have minimal weight and forces on head (laser engraving, 3d-printing).
Inspired by the [RishaLaser](http://rishalaser.org) project.

[Youtube VIDEO](https://www.youtube.com/watch?v=5F9-HIbBYwc)

![TapeXY first prototype](./doc/tapexy-first.jpg)

Key features:

* Using low-friction tape as basis for gliding surfaces,
inspired by [a design](http://www.thingiverse.com/thing:3554) by Peter Jansen
* Using braided Nylon/Polyamid wire ("Spectra line") instead of timing belts.
Like on Tantillus and some Delta printers.
* Reproduction with primarily lasercutter (or CNC mill), in wood/acrylics.
* [CoreXY](http://corexy.com) kinematics

### Parts

Fabricated

* Frame [FreeCAD](./tapexy-frame.fcstd)
* Gantry [FreeCAD](./tapexy-gantry.fcstd)
* Head [FreeCAD](./tapexy-head.fcstd)
* Pulleys. NinjaFlex/SemiFlex for friction. [FreeCAD](./pulley-ninjaflex.fcstd)
* Idlers. 2x [sideguides](http://www.thingiverse.com/thing:31216) for 608 bearing

Assembly: [FreeCAD](./tapexy.fcstd)

Main vitamins

* MDF/Plywood/Acrylic 3-6 mm.
* 2x NEMA17 stepper motors.
* 1x Motion driver board. RAMPS or similar
* Cables for motors and endstops
* Low-friction tape, width at least 20mm. Recommened:
[UHMWPE 1in 3mil](https://www.amazon.com/JVCC-UHMW-PE-3-UHMW-Polyethylene-Film/dp/B00WUU61AQ) |
Alternative: Kapton tape, as used for Reprap 3d-printers.
* Strong line. Recommended: Braided fishing line (Spectra or similar).
Alternative: Nylon, Polyester or linen.
* 2x Endstops.

Misc vitamins

* 8x 608 bearings, for idlers.
* 8x M8x40 bolts, for idlers.
* 8x M3x10 bolts, for stepper.
* 4x M4x25 bolts, for head/gantry.

Effector

* 1x Laser diode module including driver.


## Done

* First working prototype of XY stage, driven by RAMPS/Cura
* [Laser diode driver](../currentsource). Linear constant-current source based on op-amp+MOSFET, for 5volt supply.

### TODO

v2 testing

* Add tape layers (2x) to gantry to avoid clamping head too hard
* Make the head geometry slightly smaller (too tight). Maybe remove
* Design a proper belt/line attachment and tensioning system
* Design and make mount for laser diode.
Alt: Make a vinyl/pen actuator
* Add mounting holes for endstops
* Run tests with laser
* Design some self-adjusting system for friction parts

Next:

* Reduce touchpoints/area for the gantry slides.
* Find a solution for managing the cables going to head/effector. 4mm ID bowden tube?
* Design in space for the RAMPS/controlboard
* Try to switch pulleys to the fixed-end type used in deltas.
* Test replacing the 608 bearings with printed+tape bearings
* Test cutting the low-friction tape with diode laser
* Reduce number of screws used, by having lasercut pins instead
* Test a build for full-size laser envelope

Maybe:

* Test some lightweight CNC milling, like wax, PCB traces or engraving.
* Test FDM printing
* Prototype a matching Z-bed/table design

Research

* Coefficient of friction.
[Table](http://www.goodfellow.com/catalogue/GFCat2C.php?ewd_token=Q4ZIFOAVRhE2dSOYkbUxPMdSBZyxXk&n=Ab6sV0qHM8iAeitFJGlgDA1qjQCrhQ&ewd_urlNo=GFCat26&type=30&prop=3)
Kapton/Polyimide: 0.45, Teflon/PTFE: 0.05-0.2, UHMW PE: 0.1-0.2. UHMW apparently has the best abrasion resistance, seems somewhat cheaper than PTFE.

Existing low-cost laser diode engravers

* [smartDIYs](http://www.thingiverse.com/thing:1026345) open source kit. Lasercut acrylic, steelrods+timingbelts, motor on gantry.
* [Mr. Beam](https://www.mr-beam.org/) open source kit. Kickstarter 2014. 3d-printed + wood-frame. [Octoprint-based](https://github.com/mrbeam/OctoPrint) software
* [Emblaser](https://darklylabs.com/emblaser-overview) [2](https://sites.google.com/site/3dprinterlist/lasercutters/darklylabs-a3-diode-laser)

## Reproducability

### Power needed to reproduce itself.

Mr.Beam II says that with 5W they can cut 4 mm plywood in two passes (no focus adjustment).
It seems to be a blue LED with no air assist. Adding air-assist might improve cutting efficiency a bit.

This probably sets 5W as the a lower limit. If one could cut 4 mm acrylic instead, or 5-6 mm plywood, that would make it simpler to make a more rigid machine.
This _might_ be doable with 8-10 watts IR diode. If more is needed, may need to assemble 15-20 watt using multiple diodes.

### Construction tricks

To make more reproducible

* Use I/H beam or similar structures to achieve stiffness
* Use 2x 2-3mm material instead of 1x 4-6mm, sandwiched using interlocking geometry.

General best practices

* Use same bearings and screws types everywhere

Self-reproducability.

* Need to create structure bigger than own working area.
Let I/II-beams consist of multiple sections, with staggered joints?
Do testing of a long beam (50 cm+). Flatness, stiffness, maximum load.
Keep compatible with alu profiles? T-slot/Makerbeam/Openbeam

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

## Laser diodes

* [Banggood](http://www.banggood.com/Wholesale-Laser-Equipment-c-3491.html), 1.6W - [5.5W](http://www.banggood.com/445nm-5_5W-5500mW-Blue-Laser-Module-With-Heatsink-For-DIY-Laser-Cutter-Engraver-p-999283.html)
* Osram PL TB450B [DigiKey](http://www.digikey.com/product-detail/en/osram-opto-semiconductors-inc/PL%20TB450B/PL%20TB450B-ND/5719266)
* [DTR's Laser Shop](https://sites.google.com/site/dtrlpf/home/diodes)
* [Laserdirect@Ebay](http://www.ebay.com/sch/laserdirect/m.html?_nkw&_armrs=1&_ipg&_from&rt=nc&_mPrRngCbx=1)

Fibre guided

* [Ebay: 8 watt NIR 980nm](http://www.ebay.com/itm/980nm-8W-Fiber-Coupled-Laser-Semiconductor-Fiber-Coupled-laser-8000mW-IR-Laser-/141524214275?hash=item20f3802203:g:jsMAAOSwMpZUolDB)
* Ebay: [3W](http://www.ebay.com/itm/Laser-Diode-3-1-Watt-923nm-Fiber-Coupled-100um-JDSU-6380-L2-3-1W-NEW-63-00123-/111598682682?hash=item19fbccc23a:g:mhMAAOSwPhdU3sXA)
and [5W](http://www.ebay.com/itm/Laser-Diode-5-Watt-915nm-Fiber-Coupled-100um-JDSU-6390-L3-5W-NEW-63-00192-/111598671030?hash=item19fbcc94b6:g:0M8AAOSwqu9U3r8Y)

Should be possible to [combine](https://www.rp-photonics.com/beam_combining.html) multiple such fibre laser diodes with one focusing lens (maybe with colliminator).
To achieve powers of N times the individual laser source. Though with simple combinators, the brightness will not increase so much, due to widening of beam size.
 Also the heatsink no longer needs to be on the head, reducing weight of moving parts.

## CO2 lasers

For cheap lasercutters, CO2 lasers are used.

There are several aspects which are challenging.

* Laser tube itself
* Cooling the gas
* The optics
* Power supply

Principle

Using gas mixture of helium, nitrogen, and carbon dioxide gas.
A common standard mixture is 4.5 percent CO2, 13.5 percent N2, and 82 percent He. Penn suggests using a mixture of 14:14:72 in narrow-bore CO2 laser.

Aactive cooling to keep the temperature of the discharge tube below around 30 degrees C or so.

Flowing-gas lasers

"the flowing-gas CO2 laser requires a vacuum pump to achieve the low pressures (10-30 torr or so)"

* [35 Watt Flowing Gas CO2 Laser Tube Kit](http://repairfaq.cis.upenn.edu/sam/rconway/35wtkit.pdf), assembly instructions.
* [Flowing gas CO2 laser conversion from sealed gas](https://www.photonlexicon.com/forums/showthread.php/17719-Flowing-gas-CO2-laser-conversion-from-sealed-gas)
* [First Homemade CO2 Laser Built From Scratch](http://jarrodkinsey.org/co2laser/co2laser.html)

References

* [Understanding CO2 laser](http://www.laserk.com/newsletters/whiteCO.html)
* [RP Photonics Encyclopedia: CO2 lasers](https://www.rp-photonics.com/co2_lasers.html), describes different types. Sealed tube versus
* [Homebrew CO2 Laser Design and Construction Notes](http://www.timefracture.org/laserdocs/laser_design_notes.html)
* [RepairFAQ: Home-Built Carbon Dioxide (CO2) Laser](http://www.repairfaq.org/sam/lasercc2.htm). Looots of information
* [RepairFAQ: Carbon Dioxide Lasers](http://www.repairfaq.org/sam/laserco2.htm). Loots of information

## Related projects...

Of mine

* [Clothing](../clothing), various techniques rely on laser
* [Rishalaser](../rishalaser), build of existing open-source low-powered laserengraver

Of others

* [MPlus One](http://www.thingiverse.com/thing:1104249).
Cantilevered, moving bed like PrinterBot Simple and Smartrap, with lasered/milled structure.
Maybe has potential in combination with tape principle, possibly making even cheaper than a CoreXY?

Possible addons

* [Lasercut vacuum table](http://hackaday.com/2016/03/19/diy-vacuum-table-makes-lasering-even-easier)
* [Air assist for diode laser](http://www.thingiverse.com/thing:1688209), 3d-printed using a radial fan

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
This rotated quite nicely, with not too much play.
Considering the application of belt pulley, where some excentricity is quite OK.
Indicates that if one can figure out a practical assembly, the idea has some merit.

It could be that in larger scale, and with a more adhesive tape and, or with simpler geometry,
that the idea would have some merit. But with v-style 608 the process was too fiddly to be practical.

For TapeXY it could be possible to design an alternative idler/pulley solution.
For instance one could integrate the belt bottom/top guides, and use top/bottom of
rotating part for supporting the (tiny) axial load.

It is however desirable to be compatible with a standard solution,
or at least also allow a standard solution - since a hacked thing will (probably?)
never be as good as a proper bearing.

TODO

* Test cutting low-friction tape to revolved V-shape using laser.
If necessary, try to use additional glue. A jig for pressing the tape against when adhering could also help?
* Try an inverted design: inward V on inner part, outward V on outer ring.
This should be easier to adhere tape to, as the ring has shape towards the top/bottom, not hidden inside.
* Test using UHMW PE / PTFE tape.
* Design an integrated bearing+belt idler for CoreXY usage, compatible with 608-based

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
