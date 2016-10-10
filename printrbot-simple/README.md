Jon's Printrbot Simple   
======================= 

Based on a version 1401 (early 2014) Simple Wooden Makers kit

Modifications
--------------

* [Tower with filament spool](http://help.printrbot.com/Guide/Installing+the+Simple+Tower+%28or+Tower+Tall%29/65)
* Autoleveling probe
| [Thingiverse](http://www.thingiverse.com/thing:456027)
| [FreeCAD](./autolevelprobe-mount.fcstd)
| [STL](./autolevelprobe-mount.stl)
|
* NinjaFlex mod


TODO
----

* Raspberry Pi mounted, running Octoprint on WiFi
* Webcam w/LED lights mounted, connected to RPi
* Relay for turning on/off printer from RPi


## Ninjastruder

Switch to [NinjaStruder](http://www.thingiverse.com/thing:1494685), a Bowden-capable extruder
designed for flexible filaments like NinjaFlex. Primarily to test for other 3d-printer builds,
but also to improve the Printrbot by reducing weight on the Y axis.

### Status

Printed and assembled NinjaStruder. Using E3D v5 hotend. Tested extrusion working.

### TODO

Working

* Split off, and connect 12v power for the hotend fan
* Make a new mount for the hotend. Include Z-level inductive probe.
Consider Richrap style quick-connect?
* Make a mount for the extruder.
Need to take into account Bowden path to hotend, and filament path from spoolholder.
* Connect back the print FAN
* Connect extruder/hotend wires properly
* Calibrate extruder steps
* Calibrate Z-height
* Run tests with Ninjaflex
* Change temp probe setting in Marlin?

Next

* Add the files of custom additions made to Thingiverse
* Publish a "I Made it" on the Ninjastruder

### Notes

[NinjaStruder gear upgrade 2:1](http://www.thingiverse.com/thing:1785884)

With original direct extruder (and original Ubis hotend). `M92 X83.00 Y85.50 Z2010.00 E95.00`.
