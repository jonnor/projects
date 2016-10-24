
# Bitraf Shopbot course, software/CAM part (in VCarve)

## Intro / meta-information

* We will walk through a simple CNC project from start to end:
* Making a little design. 
* Importing the DXF geometry into VCarve
* Setting up toolpath (drill, pocket, profile)
* Exporting the gcode for use with Shopbot

## Making a design (in Inkscape)

Can be done in any software that can export to DXF.

Smart to set the size of the material (alternative, size of Shopbot workarea)
as the "document size" when designing.

In Inkscape,
* File -> Document Properties
* Default Units: mm
* Document Size. 

The design should ideally have something to pocket (for instance text),
some internal cutout that something should fit into (to demo dogbones),
and need cutout (to show use of tabs).
Can for instance be a sign.

## Importing into VCarve

* Which machines have it installed: Common machines in the lab, Shopbot PC, course laptop
* Open the program

User interface basics. "where to find what"
* Drawing/geometry tools on the left. Not so much used, since we design our favorite CAD software.
* Toolpath operations on right hand size. Contains what we use most of the time.
Behind slider menu button. Recommend click to make the menu always show

* Setting up a new document: File -> New
* Like before, use material (or machine) size as size
* Set material thickness.
Sidenote: Always remember to measure material thickness, in multiple places.

Walkthrough of other options:
* Doublecheck that "Offset" is not in use
* Normally (almost always) use bottom-left as 'Origin'

## Setting up toolpaths

### Adding geometry for holddown

* We drill with the machine so we know exactly where the holddown screws are.
* We make the geometry of the holes 22mm diameter, so that we have a clear "avoidance area"
for typical screw head / bit size.
* As long as we don't cross into the circle with our tool, we are safe from collision
* Usually use at least 4 holes, on all sides of a part. More if parts are big

### Setting up drill job

* Marking the holddown circles
* Adding drill operation
* Setting depth
* (quick walkthrough of the more advanced options, what they are / can be useful for). Example: peck-drilling

! Give a good name to your toolpath operations.
Easy to navigate later, and especially when exporting/importing with Shopbot control software.
Should contain:
Type of operation / geometry affected,
tool used,
and a number for running order.

Good to use all CAPS for HOLDDOWN (since it is not safe to run twice)

### Pocketing text

* Adding pocket operation
* Setting depth
* Number of passes/pass-depth (quick explanation, more later in bit setting)
* Pocket mode, raster versus offset. (quick explanation)
* Normally use Offset
* Conventional versus climb (quick explanation)
* (quick walkthrough of other options, what they are / can be useful for). Example: clearance tool

### Profile internal hole

* Adding profile operation
* Setting depth
! Always go a bit deeper than material thickness. At least +0.5mm, normally +1mm.
* Choose Inside
* (quick note on open vectors, can get wierd results. Tool for closing open vectors)
* Allowance + last-pass: (quick explanation)
using to add tolerances for parts that fit together (if not done in CAD)
using to get better precision and/or finish quality.
* Using dogbone/T-bone fillets for fitting pieces with sharp inner corners


### Profile outer hole

* Add Profile operation
* Set depth
* Adding tabs to keep part steady after

### Exporting toolpaths

Smart to always "Recaculate all" before exporting, know everything is up-to-date

! Doublecheck post-processor is set to Shopbot (mm)
! Doublecheck "output visible toolpaths" is on
* Select
* Can have many operations in one job in one file, as long as they have same tool, and no manual steps are needed in between.
* Will run in the order they appear in the file (sort using VCarve operations list)
* Might want to keep final cutout in separate job, in case needing to fix something on the part. 
After cutout, workpiece is much less stable.

! ALWAYS export HOLDDOWN separately


### Bit settings

Mostly we use endmill. Sometimes use ballnose (3d-milling) and v-bits (chamfering/vcarving)

* Diameter. Critical, determines offset from inner/outer lines. Specified on tool
* Passdepth (maximum)
* Step-over. Typically set around 50%
* Feedrate. Depends on diameter, passdepth, material
* Plungerate. Typically way lower than feedrate, endmills are bad for cutting down, good for sideways
* Settings are "Black magic".
Use defaults, tune from there, ask for help.
Alternatively, use a chip load calculator.


### Other CAM operations in VCarve

* Drill, Pocket, Profile covers 90% ++ of usage
* More advanced operartions available, not part of this course
* Quick mentioning what other operations are available, and what they might be useful for
* Example: V-carving, 3d-milling (rough, finishing)


