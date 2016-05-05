
# 3d-printable brushless DC motor

Inspired by [3d-printed DC motor by pitrack]
(http://www.instructables.com/id/3D-Printed-DC-Motor/step4/Mechanical-Design/)

Overall this design is less printable (more vitamins),
but is hopefully practical and powerful enough to be useful in realistic scenarios.

![Model](./doc/outrunner-rev0.png)
![PCB](./doc/pcb-rev0.png)

## Notable changes

* Integrated driver electronics. Standard components, designed for reuse.
* Outrunner design instead of inrunner
* Using iron-core (M4 bolts) electromagnets instead of air
* Has a bearing (608) and a metal axel (M8)
* 6 teeh stator, 8-10 pole rotor instead of 3/4
* Smaller distance between rotor and stator magnets

Important features retained

* 3d-printable w/common vitamins
* Winding of electromagnets done separately, facilicated by winding tool

Drawbacks

* More vitamins required
* Magnets have to be glued to rotor


## Usecases

* PC/cooling fan. Radial or axial. 80/120 mm.
* Peristaltic pump (fluids). Might need gearing
* Impeller pump (fluids), for instance for hydroponics.
* Camera jig, using belt/wires to translate to linear motion
* Electromagnet winding tool, so it can help replicate itself!
* Extruder/print cooling fan. Requires minimization
* Spindle motor for CNC. For instance by letting motor wrap around a ER chuck+shank.
[1](http://www.openbuilds.com/threads/brushless-dc-motor-spindle.266/)
[2](http://kreature.org/projects/mini-cnc/collet_spindle/spindle.jpg)

## TODO

* Complete uC and Hall-sensor part of electronics
* Calculate appropriate number of windings
* Manufacture, assemble and test prototype

## References

* [Good video explanation](https://www.youtube.com/watch?feature=player_detailpage&v=C1-klL3B9LU#t=734)
* [Atmel: Sensorless commutation of brushless motor using back-EMF implemented in uC](http://www.gaw.ru/pdf/Atmel/app/avr/AVR440.pdf).
Also shows use of tapered air-gaps to ensure known starting position of rotor (and direction?).
* [uC centric, well documented brushless motor driver board](http://danstrother.com/2011/01/12/brushless-dc-motor-controller-board/)
* [DIY brushless motor implemented on PCB](https://www.youtube.com/watch?v=dSkj-OdujoU)


> The thickness of the iron lamination sheets varies between about 0.05 and 0.5 mm in most electrical machines.
The choice of lamination thickness depends on a balance between performance and cost.
[Ementor: Lamination thickness](http://www.emetor.org/glossary/lamination-thickness/)

## Winding

> Y pattern gives high torque at low RPM and the ∆ pattern gives low torque at low RPM
> ...
> The higher the number of rotor poles, the higher the torque but the lower speed
> ...
http://www.edn.com/design/sensors/4406682/Brushless-DC-Motors---Part-I--Construction-and-Operating-Principles

* [Common winding schemes](http://www.bavaria-direct.co.za/scheme/common/)
* [Electric motor winding calculator](https://www.emetor.com/edit/windings/)
* [Very thourough walkthrough (text+picture) of rewinding brushless mototor](http://www.rcgroups.com/forums/showthread.php?t=666877)
* [Winding diagram table](http://www.bavaria-direct.co.za/info/#), from 3n2p to 18n20p

## Firmware

Existing open source firmware.
Used in multi-copter etc, compatible with many many ESC packages.
Many using AVR atmega8/16 uCs.
These typically take servo-style 1ms -> 2ms pulse widths to mean 0% -> 100%.
Though on some high performance setups, the maximum pulsewidth is sometimes set to 125 us instead.

* [SimonK](https://github.com/sim-/tgy) (assembler, some german license)
* [BLHeli](https://github.com/bitdump/BLHeli) (assembler, GPL)

## ESC

Example [Atmel-based ESCs](https://github.com/bitdump/BLHeli/blob/master/Atmel/BLHeli%20supported%20Atmel%20ESCs.pdf).
BlueSeries 12A, HobbyKing 6A and YEP 7A are quite simple-looking designs. Most things look to be variations around exacly the same pattern.

Commercial

* Available for RC-use for `< 10 EUR`.
[HobbyKing](http://www.hobbyking.com/hobbyking/store/uh_listCategoriesAndProducts.asp?cwhl=XX&idCategory=61&v=&sortlist=P&LiPoConfig=&CatSortOrder=asc)

Principles

* Well explained [principle circuit](http://www.rcgroups.com/forums/showthread.php?t=1679621)
* [Another simple schematic](http://www.avrfreaks.net/comment/435508#comment-435508)

Open source

* [VESC - open source ESC](http://vedder.se/2014/01/a-custom-bldc-motor-controller/) [github](https://github.com/vedderb/bldc)
* [Open-BLDC](http://open-bldc.org/wiki/Open-BLDC), not updated since 2012.
* [Hackaday.io; OpenBLDC](https://hackaday.io/project/1490-openbldc), schematics and [Arduio controller code](https://github.com/Neuromancer2701/BLDC_ros_controller). MIT licensed.
[github](https://github.com/open-bldc) has links to simulation tools and firmware in C.
* [Simple with board and code](http://davidegironi.blogspot.no/2013/09/a-simple-brushless-sensorless-motor.html#.VvxblbPuRhE),
using [IR2101 driver](http://www.irf.com/part/High-and-Low-Side-Driver/_/A~IRS2001).

## Existing motors

* Outrunners available for `10 EUR`
[HobbyKing: 22-27 mm](http://www.hobbyking.com/hobbyking/store/uh_listCategoriesAndProducts.asp?cwhl=XX&idCategory=1219&v=&sortlist=P&LiPoConfig=&CatSortOrder=asc)
[HobbyKing: micro](http://www.hobbyking.com/hobbyking/store/uh_listCategoriesAndProducts.asp?cwhl=XX&idCategory=518&v=&sortlist=P&LiPoConfig=&CatSortOrder=asc)
* [Banggood](http://www.banggood.com/search/brushless-motor/0-0-0-1-3-45-0-price-0-100_p-1.html?sortType=asc)

## Sourcing locally

* Neodym magnets.
[Kjell](http://www.kjell.com/se/sortiment/hus-halsa-fritid/ovrigt/gadgets/neodymmagnet-8-mm-10-pack-p50070)
Clas Ohlson

# Fabricated stepper motor

* Should be able to mill 0.5mm silicone iron on Shopbot
* Using 2mm bit, tooth spacing of ~3mm
* 200/6 = 33 steps = 10.8 deg -> diameter = 32 mm
* 200/4 = 50 steps = 7.2 deg -> diameter = 48 mm

[FreeCAD project file](./stepper-motor.fcstd)

## Etching steel

Tin-can materials are magnetic (3/3 tested). A thickness of 0.3 mm (approx 0.012") seems to be common.
The material is some form of steel.

Steel can be etched using a acid and electrical current.
Here is one [etching steel with vinegar, salt and 12v battery charged](https://www.youtube.com/watch?v=zhWNmNYT-Q4).
Another electro etch [using a metallic electrolyte](http://www.nontoxicprint.com/electroetching.htm).

Creating an etch mask can be done with the laser, like with PCB production:
[1](http://www.instructables.com/id/PCB-plastic-mask-etching-with-CO2-laser/)
[2](http://www.instructables.com/id/Custom-PCB-Prototyping-using-a-Laser-Cutter)

Some [safety considerations using NaCL-based etching](http://www.es.crujera.com/publicaciones/articulos/the-basis-of-electro-etchin/appendix-b---practical.html).

Using a 15ish percent vinegar solution (diluted from 35% percent with hot tapwater)
with approx 1 table spoons salt per 1 dl. Current was around 0.60 - 0.70 amps,
driven by a 12v power supply.

Was able to etch through the 0.3 mm 'tin can' in less than 30 minutes.
The mask was open on each side, so to get through etch is only 0.15 mm deep.
This requires precise registration of two-sided mask.
The fast etch time, suggest that maybe doing a one-sided etch is possible as well.

Without a permantent magnet one can only build a [reluctance motor](https://en.wikipedia.org/wiki/Reluctance_motor) with this steel,
like a stepper based on [switched reluctance motor](https://en.wikipedia.org/wiki/Switched_reluctance_motor).
By adding a circular, axially oriented magnet in the center, one can build a
[hybrid stepper motor](http://www.nmbtc.com/step-motors/engineering/construction-and-operating-theory/),
like the typical NEMA17 used in 3d-printers. Excellent [video explanation](https://www.youtube.com/watch?feature=player_detailpage&v=Qc8zcst2blU#t=1823)

![First attempt at etching stepper motor parts](./doc/etch-first-stepper-parts.jpg)
Caliper is set to NEMA17 size (1.7" / 42 mm), for reference.

Removing resist with laser worked pretty well, but the acrylic spray-pain partly dissolved in the electrolyte - causing uneven etch.
Another problem is that material which have been etched sticks in the gaps, making it seem as if it has not etched through when it has
(possibly also interfering with etching action).
A pump/nozzle which would 'shoot' the electrolyte at the plate with a bit of force would likely improve that.

Would need to find a better spray (laquer is mentioned online), or use a tape.
Maybe regular scotch packaging tape,or wide PET/Kapton as used in 3d-printing.
Etching time was approx 30 minutes, from one side, with 1.5 amp current in 10% vinegar solution.

A flipping-jig would be needed to do two-sided masks (and etch).
A challenge in using recycled can material is that it is not flat, causing focus problems on laser.
A hydraulic piston with solid steel top and bottom plates, could possibly be used to squeeze material flat.

### Mask making

Using plastic tape selectively removed by laser-cutter to create masks was partially successful.
The tricky thing is finding settings/materials where the tape *and* its glue gets removed cleanly,
without causing too much removal (widens etchline) or bubbling of the plastic on edges.

Actually heat-resistant PET plastic, sometimes used as replacement for Kapton on 3d-printers,
appears to cut very nicely. However 2 passes seems to be way to go, one to deconstruct the plastic, and one to clean up.
Used 20%, 0.1mm linewidth, 200 mm/s on Redsail 60w.

Other techniques which may be worth trying instead for selective-laser removal is:

* Coating with paraffin/stearine, for instance from melted candles
* Coating with spay/fluid wax used for polishing (usually carnauba-wax). [Example](http://www.clasohlson.com/no/Hurtigvoks-/34-917)
* Coating with a varnish. Examples: [1](http://www.clasohlson.com/no/Original-Ferniss/34-1316)
[2](http://www.clasohlson.com/no/Winsor-&amp;-Newton-blank-maleferniss/34-4612)
[3](http://www.clasohlson.com/no/Liquitex-medium-og-ferniss/34-4085)

In [etching](https://en.wikipedia.org/wiki/Etching), the material laid down to protect against the etchant is called the *ground*.
This page has many [modern alternatives for ground](http://www.nontoxicprint.com/hardandsoftground.htm),
including a type of commonly found acrylic wood finishing.

## References

* [LiniStepper, (old) open-source stepper controller](http://www.romanblack.com/lini.htm)
* [L297 stepper controller, app note](http://www.st.com/st-web-ui/static/active/en/resource/technical/document/application_note/CD00003803.pdf).
Describes how PWM chopping with H-bridge current sensing, is used to control current in motor.
* [Open Source Ecology, quest for open stepper motor](http://opensourceecology.org/wiki/Open_Source_Stepper_Motor_Controller)
* [Open Source Ecology, quest for open stepper controller](http://opensourceecology.org/wiki/Open_Source_Stepper_Motor_Controller)

# Servomechanisms

The closed-loop nature of [servomechanisms](https://en.wikipedia.org/wiki/Servomechanism)
can be beneficial to locally fabricated machines, because it can be used to compansate for or correct errors.
This could allow to use cheaper/simple production methods and materials.
Also, it can allow machines to run closer to their theoretical limits - because there is
a way to detect & correct errors. Current generation Repraps 3d-printers will just continue running obliviously
after missing step(s), often leading to broken models.
Robotic arms with many degrees of freedom typically also rely on servos/feedback in order to accurately position their limbs.

Two types of systems are interesting:

1) Servo/feedback mechansism in motor. Either stepper motors, or 'servos' based on geared brushless DC motors
Typically [rotary encoders](https://en.wikipedia.org/wiki/Rotary_encoder) are used for this.
2) Servo/feedback mechanism in larger machine, like the position of a 3d-printer head along an axis.
Typically [linear encoders](https://en.wikipedia.org/wiki/Linear_encoder).

And, it is interesting to figure out:

1) How to integrate cheap, off-the-shelf encoders to form a closed loop system.
2) How to fabricate encoders using typical fablab equipment.
Using lasercutter to make optical systems, or using PCB etching for conductive both seems promising avenues.

Probably it makes sense to start with a usecase which does not require sub-millimeter precision.

## Encoder

References
* Farnell: [Photointerruptors](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000005979&sort=P_PRICE&pageSize=25&showResults=true&aa=true&pf=111784929,111784930,111784932,111784933,111784934,111784935,111899261,112041178&max=111784935)
5 - 10 NOK/piece, 0.5 - 0.15 mm aperture.
* [Quadrature encoder from two photointerruptors](https://frobotme.wordpress.com/2014/05/25/a-simple-diy-quadrature-encoder-for-arduino-using-optical-sensors/), by offsetting them from eachother.
* [How Quadrature encoders work](http://www.dynapar.com/Technology/Encoder_Basics/Quadrature_Encoder/)
* [ServoStrap](https://github.com/danithebest91/ServoStrap), 3d-printer based on closed-loop DC motors salvaged from printer.
* [HackADay: Closed loop control for 3d-printer](https://hackaday.com/2015/01/20/closed-loop-control-for-3d-printers/#more-144269). Based on ServoStrap.
* [DigiKey: Designers guide to Encoders](http://www.digikey.com/en/articles/techzone/2012/apr/a-designers-guide-to-encoders)
* [Linear position tracking with (off-the-shelf) quadrature encoder](http://benkrasnow.blogspot.no/2010/02/linear-position-tracking-with.html)
* [DIY differential optical encoder](http://groups.csail.mit.edu/mac/users/pmitros/encoder/)
* [OpenEncoder, rotary magnet encoder PCB](http://www.openservo.com/OpenEncoder)

# Linear motors

Most [Linear motors](https://en.wikipedia.org/wiki/Linear_motor) are like rotary motors, just unfolded.
Therefor the common variations exist, including linear stepper motors, linear brushless, linear permanent magnet.

## Linear stepper motor

Linear stepper motor. Simplest example is [Sawyer](http://machinedesign.com/linear-motion/linear-motors-step-out),
a hybrid stepper (variable reluctance with single magnet).
Windings are on the moving part (called 'forcer), so cables have to be carried along.

The grid structure required for variable reluctance is easier to manufacture with a CNC when linear,
because it can be done from above as straight pockets.

## Brushless linear motor

The magnets are in the track, and windings in the moving forcer.
Typically a flat strip with forcer on top, or a U-profile with forcer inside.
Coupled with a linear encoder, can get a high-precision linear servo motor.
They are used for high-end pick&place, laser and water cutters.
Commercially available from [H2W](http://www.h2wtech.com/category/brushless-linear#productInfo1) [vid](https://www.youtube.com/watch?v=TPCgbfWZ6IQ),
[MITSUBISHI](https://www.youtube.com/watch?v=2pbYb5HNJ2M).

[Linear motor applications, includes section on commutation](https://www.aerotech.com/media/136335/linear-motors-application-en.pdf])


## Voice coil actuator

Voice coil actuator or [Voice coil motor](http://www.moticont.com/voice-coil-motor.htm).
Short throw, up to couple inches. Designed for a set throw distance.
http://electronicdesign.com/components/what-s-difference-between-voice-coil-actuators-and-solenoids

* [Instructable, voice coil, equations](http://www.instructables.com/id/Electromagnetic-Actuator/step4/Wind-bobbin/#step1)

## Tubular motor

Also called linear shaft motors.
Commercially available from Faulhaber, Moticon and LinMot.
Rod-magnets placed inside tube, each repelling eachother. `N/S<->S/N<->N/S<->S/N`
Either rod or circular casing can be stationary.

Could be good for moving the shuttle/rapier when doing weft insertion on a loom.
Could possibly be used for controlling the heddles.

If minimized and made cheap, potentially also individual heddle control, for Jaquis/digital loom.
Coupled with a linear encoder, could maybe be used for a shape display.

* [YouTube: Simple DIY version](https://www.youtube.com/watch?v=3PLWTF_6odc). Quite jerky motion.
* [YouTube: DIY version with sinusoidal commutation](https://www.youtube.com/watch?v=PXybuXsqEWo)
* [Youtube: DIY controller with position control](https://www.youtube.com/watch?v=PWSf_NWGty8)
* Background on [shaft motors](https://electromate.wordpress.com/2012/01/29/linear-motor-lowdown/) 

# Coil winding automation

Commercial systems

* [Youtube: BLDC coil winding machine](https://www.youtube.com/watch?v=MrdzaA8CClk).
For an inrunner, whole cycle shown in real-time.
Does complex patterns by 'tieing off' the copper wire on a post outside the stator.
* [Youtube](https://www.youtube.com/watch?v=d77b1C-ruw8). Another inrunner using same principle, doing 4-5 simultanously.
* [Youtube: Winding of a 4" brushless motor](https://www.youtube.com/watch?v=2JsRYUTK5Pw).
* [2](https://www.youtube.com/watch?v=nFZVhA13EfY)
* [Youtube: rushless dc motor supplier auto winding](https://www.youtube.com/watch?v=3ws1P5hZBWo),
shows sliding geometry used on spinner to lay out wire back and forth on armature.
* [Youtube](https://www.youtube.com/watch?v=IcmNN4ZSLeo), also shows guiding mechanism working
relative to the armature geometry, and also the arm which spins the wire.

General principles

* Stator sits on a turntable/spike, which can rotate 360 degrees
* One armature is wound at a time, from start to finish
* Some winding configurations requires some windings go one way, and some the opposite
* The armature can be all wound with loose ends at each side,
then connected to form correct configuration afterwards.
* For small-ish motors, easier to autowind outrunners than inrunners.
This because the spinner can put windings onto stator from outside.
* Thinner gauge wire is preferred because it is easier to automatically wind
(number of windings will affect Kv number).
* For outrunners, a large wheel spins the incoming wire, guided into right place by some (motor size specific) geometry
* For inrunners, a 'finger' guides the wire around the , with a reprociating motion.
* This spinner wheel moves in and out on the armature to lay out the wire

Open sources

* [Coil winding machine](http://www.thingiverse.com/thing:981327)

# Servomotor

There are some RepRap designs for servos, including some deltas like [Enemy](http://reprap.org/wiki/Enemy_Delta_Robot).

If one can fabricate a precise rotary encoder.
Either resistive, capacitive or inductive

## References

* [OpenServo, PCB/encoder replacement for servos](http://www.openservo.com/FrontPage)
* [IntelliServo, digitally controllable servo board](http://hackaday.com/2016/04/22/intelliservo/)

# Research

* [3d-printed transformer](http://3dprint.com/80379/3d-printed-power-transformer), says electromagnets with ProtoPasta Magnetic Iron not working well.
* Another magnetic 3d-printer material, from Graphene 3D. [Announcement](http://3dprint.com/115769/graphene-3d-magnetic-filament/)

# References

* [Thingiverse: Open Motor](http://www.thingiverse.com/thing:46428)
* [15-deg stepper motor (halfstep capable)](https://www.youtube.com/watch?v=v2FNUNALSTw)
* [Another printed brushless](http://3dprint.com/89359/3d-print-brushless-pulse-motor)

# Related projects

* [Current source](../currentsource), electronics module for digitally controllable constant current source.
Could possibly be used for 2-phase unipolar motors. But possibly better, would be to take that concept
and create H-bridge modules with current sensing/control. Such H-bridge could replace them entirely,
but also be used for stepper-motors and brushless DC-motors. Forming a generic, software-defined 'drive' system.
