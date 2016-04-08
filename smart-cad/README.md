

Working from reference data
-----------------------

Especially when creating replacement, augmentation or connecting parts,
working from reference images is extremely handy.
Smarter handling could drastically reduce modelling time,
and potentially allow effective modelling with less precise user interfaces (mobile, augmented),
or by less adept users.

Image could be of actual object from camera/smartphone,
from image on Internet, but also be imported technical drawing.

Image workbench in FreeCAD allows importing image as plane in 3d-view.
This is already useful for reference, by approx rescaling to physical size,
then using as backdrop when creating Sketch/Draft objects.

* Scale image to fit physical world dimensions
* Align line horizontally/vertically
* Apply lens distortion correction
* Apply perspective correction

Computer vision / feature detection

* Detect outlines/contours
* Detect holes
* Detect text / OCR
* Detect dimensions (in tech drawing)
* Detect bounding box, centerline, symmetry

Allow selecting features to go into different "layers" -> sketches, polylines
Likely that computer-vision will do better with a bit of input from user,
particularly to adjust sensitivity levels.
In general should assume that user chose a sane image,
and increase sensitivity until at least some features are found.
Maybe allow to set "these features I want", and "these are not features" constraints.
Feature-free constaint could be done by marking a whole area
And then let algorithm try different variations until both are satisfied
Could also allow to specify "points outside object", and which are "inside" contour
Process must be iterative and non-destructive

When user takes picture in-the-moment, live feedback could be very useful.
Different lighting conditions, background, angles can severely influence effectiveness of CV.

Pipeline

* Camera/lens correction. Noise removal.
Input=camera/lens-model or calibration/characterization data. Use heuristics based on metadata to provide default
* Projection correction.
Input=4 points forming a rectangle.
Computer-vision could suggest defaults.
* Mapping to physical/real-world units.
Input=distance between two points.
If there is a scale/meter in picture, computer-vision defaults.
* Scaling image down to desired resolution.
Input=resolution in physical unit (can be default or presets, 0.1mm or so)
* Cropping/selecting area of interest.
Possibly done N times, for multiple objects from single image
* Adaptive feature extractors.
Maybe including image normalization (contrast,levels)
Filtering, gaussian/box/blur
Morphopogical noise removal, erosion/dilation/opening/closing
Allow specifying constraints, on both number of features, which areas have features/not
* Higher-level features, derived on basic features
Combining multiple lines into one.
Making use of repetition to determine groups.

Ideas

* Use printed, smart tag sticker as a reference for size and projection?
Standard size, rectangular points. Stick onto object plane, detect using computer vision.
* Store the objects in a database with image descriptors, perform lookup
* Use multi-view (like Google Lens Blur) to build depth-map to assist in
* Use saliency/foreground extraction to better determine which part of image is "the object" or not
* Have presets for common tasks, templates for interfacing/joinery. Allow to build/save new ones.


Usecases

* 3d-print a replacement or adapter part
* 2d/3d-model of interior features, to aid buying correctly sized parts/furniture

Challenges

* Working primarily for planes, general 3d surfaces much more difficult.

Development

* Use primarily end-to-end, data-driven tests. Input=image, ref/output=set of extracted features (json/yaml)
* Kernel in C/C++, UI in Python/CoffeeScript. Inputs/outputs serialized, images communicated as URIs/blobs.

Resources:

* [Converting between Bezier curves and lines+arcs](http://itc.ktu.lt/itc354/Riskus354.pdf)
* [Error propagation in geometry-based grouping](http://www.freidok.uni-freiburg.de/volltexte/2932/pdf/thesis_a5_9pt.pdf),
good info on camera models, joining line segments, detecting orthogonal and revolved bodies
* [Nexus 5 insintric camera parameters](http://rkdasari.com/2013/02/14/camera-calibration-matrix-finding-intrinsic-parameters/)
* [4-point perpective calibration](http://w3.impa.br/~zang/qtcalib/nochess.html)

Movable parts & Animation
---------------------

When building things which have moving parts, like scissors or a folding knife,
one needs to design geometry which accomodates the moving part at multiple positions,
and the transitions between them.

Uses

* Animation, for product visualization
* Finding geometry which the moving object traces, for cutout
* Evaluating fit at each stationary point

Common cases

* Motion around pivot point
* Linear motion constrained to path

Implementation idea?

* Define path for object/point to follow.
* Define Poses along this path `0.0 - 1.0`
* GUI to jump between poses
* GUI to slide along them continiously
* Be able to set up simple timeline with drivers of poses

Joinery/connections
----------------------

Creating joinery between two or more pieces can be time-consuming when
have to be modelled manually. One could perhaps create a joinery object
which has all the features needed, and applying it to.

When dividing up a part into multiple to fit build volume, as in "partitioning/tiling"
the object could also handle splitting the part into multiples. In some cases just

Especially when using a standard set of vitamins/hardware,
to keep part requirements low and reproducability high.

Examples:

* M4 bolt counterbored in one part, press-fit hex nut in another part, 3d-printed.
* Mortise in one part, tendon in another, 3d-printed.
* Finger or dovetail-joints between two pieces mounted 90 degrees on eachother
* [Halved joint](http://en.wikipedia.org/wiki/Halved_joint)

## Cutsheet autolayout

When working with multi-part designs on CNC router or lasercutter,
need to layout parts into a cutsheet for a job. This can take a significant amount of time to do manually.
An automated tool could help:

* Avoid having to layout normal job manually.
Especially useful when having parametric parts, possibly being changed iteratively.
* Reuse material which is usually thrown away.
By quickly adopting a cutsheet to left-over/already-cut material, or adding parts to a planned sheet.
* Making efficient use of machines. Both keeping high uptime, maximizing items made when runnnig job.

Computationally, this is a 2d polygon version of the [packing problem](https://en.wikipedia.org/wiki/Packing_problems)

For reusing material, tool should allow:

* Take camera picture of leftover materials
* Or, remember left-over geometry from past jobs.
One could for instance 'label' (etch/pocket) left-over material for easy retrieval.

Avoidance areas, for bad material, for instance finish or structural deficiencies.
Avoidance area can also be used to auto-add parts around an existing, manually laid out, job.

It should be possible to specifying number of instances desired per part,
instead of having to duplicate the part geometry.

Tools should be able to calculate

* Given a set of parts, and a particular material, lay them out
* Given a particular material, find parts that fit from a library, and lay them out
* Given a library of parts, and library of left-over materials, show which things can be made?

Some complex considerations: material grain direction, sharing cutlines

Tool should be usable with any combination of CAD / CAM software (independent),
but integration with scriptable packages should be possible.

### Possible implementation

Take a set of DXF files (one per part) as input.
Filenames can indicate numbers of instances of each part (part-rev2-3x.dxf).
Takes material geometry either as a JPEG/PNG file (from camera), or a DXF file
Internally both of these material inputs gets converted into same representation.
Material geometry would need to have real-world dimensions set. Unless overridden, use DPI metadata.
Unless overridden, image origin should coincide with job origin, with same X,Y axis.

Optionally a DXF file (or image?) can be used to specify avoidance areas.
Effective available area, is avoidance area subtracted from material area.

Tool should have mode to observe filesystem for changes in the files?

CAD/CAM integration could be plugin which exports geometry from program into appropriate file layout,
then runs the program to produce output file, then loads this into program.

### Challenges

* Need to build up library of *useful*  (or at least desirable) parts
* Different material requirements for parts.
Examples: Type of material (plywood, MDF, acrylic), thickness of material
* Different CAM settings for part geometry.
Examples: cutting speeds, laser power. Raster versus vector, pocket versus cut. Pocket/cut depth

## Objects

Objects suitable or designed for fabrication from scrap material

* [Trashcan](../random/thrashbin.fcstd) designed to only use short staves. Inspired by Waste Bin by Astrid Lubsen
* [SketchChair](http://www.sketchchair.cc/), slice-based open source chair, could possibly be suited
* [POD by Samuelle Javelle](http://teobonobo.blogspot.no/2013/12/pod-samuel-javelle_6.html)
* Pintres: CNC'ed furniture inspiration [1](https://www.pinterest.com/pin/478789004105748170/)
* [Sanding blocks](http://www.thingiverse.com/thing:23863). [Remix](http://www.thingiverse.com/thing:1273771)
* [Customizable hexagonal shelves](http://www.thingiverse.com/thing:1199930)
* [Drawer organizer/divider](http://www.thingiverse.com/thing:1003796)
* [Rack](http://www.thingiverse.com/thing:875448)
* [Parametric bookshelf](http://www.thingiverse.com/thing:1108893)
* [](http://www.thingiverse.com/thing:1373)


### Related ideas

* Could expand this to 3d-printing / additive manufacturing.
An example of wasted materials there is supports. Instead of printing only some throw-away structure,
could insert some useful parts to make up the bulk. The orientation of parts could be set
* Have a queue of desired objects ("wishlist"), which would be first-priority when attempting to add filler-objects.
Should be super-easy for anyone with access to add to list, maybe by referring to a URL to part.
Should then get a notification once part has been produced.

### Possible codenames

Misteltein, Norwegian name for [Mistletoe](https://en.wikipedia.org/wiki/Mistletoe).
Because the added part geometries can be seen as parasites on the job being run, adding more useful things.

## Freeform / assisted drawing

References:

* [Collection of assisted drawing research](https://medium.com/@samim/assisted-drawing-7b26c81daf2dd)

## Slicing for fabricating

For users it can be very challenging to design, especially when having to construct
3D shapes as 2D geometry suitable for CNC/laser.
Also, often it is desirable to not design something from scratch
- but reuse existing models, or scanned geometry.

Instead can design in 3D, and then slice it automatically into 2d geometry realizable on laser or CNC.

123D Make is example of propriatary software for this purpose.
It is also not cross-platform, for instance does not work on Linux.

Done well, would have very strong synergies with the auto-layout and joinery generation
- because then any 3d-model could potentially be used for making things from scrap
- not just objects designed for this purpose.

Existing open work

* [Uinsg Skeinforge to slice STL into SVG](http://www.nycresistor.com/2012/02/27/laser-slicing/)
* [Slicing 3D CAD Model in STL Format and Laser Path Generation](http://www.ijimt.org/papers/431-M1007.pdf) (paper)
* [SketchChair: Online parametric chair-generator based on slices for CNC](http://www.sketchchair.cc/)
* [PuzzleCut: OpenSCAD library that cuts objects into interlocking pieces](http://www.thingiverse.com/thing:35834)
* [Slicing sides of model with OpenSCAD for faster/detailed printing](http://geekygulati.com/2014/05/10/slicing-and-dicing-with-openscad/)

Related

* [Papercraft: Unfolding STL models to make laser cut patterns](https://github.com/osresearch/papercraft) [website](https://trmm.net/Unfolding_STL)


## UX concept ideas

### Input types

* Touchscreeen. Finger or (bad) stylus
* Projector with marker pointing device
* Mouse + keyboard

Everything is currently focused on mouse+keyboard, restricting "serious" CAD work to primarily
desktop/laptop. To open possibilities for mobile personal device, and collaborative tables
- the two other ones are very interesting.

### Context aware actions

Based primarily on current selection (number of objects, types).
Presented as a visual menu, easily reachable with pointing device.
Each action in the menu has an accociated keyboard accelerator,
a character which ideally is a nemonic of the action name.

May need some sub-menu for when many actions are applicable.
Such a group could presented as an action in the top-level menu.

Ideally it is primarily a direct manipulation of the objects.

The same action-list should be filter/searchable by typing in words on keyboard.
If the query is specific enough basically becomes a command.
Hitting enter would then trigger it.

Examples would be when working with Sketches:
adding/manipulating geometry, adding and manipulating constraints.

Triggering an action should then allow entering its parameters (if any).
This should (at least allow), on-canvas preview&manipulation.

Open questions:
How to let user know that with current selection, a certain action cannot be performed
- that they need to change their selection first?
If there is space in the group, maybe can show grayed out - with explanations of needed selection/context?

Implementation ideas:
Actions should be an atomic unit, a 'component', registered with introspection data.
Open code of action component, should be accessible in program.
Actions installable though plugins (as a collection).
Actions described as contracts??
Is a triggered action which is still being edited like an opened, but not committed transaction?
Can one use state diffing (kinda React-style), to implement undo-system (and revision control)?
Indirection between state produced by action, and canonical state of program.

## next level constraints

Right now only on geometry. Should be able to define in terms of production costs (or time), generality, performance.

References:
* https://github.com/kragen/laserboot/blob/master/README.md


## Digital calipers as input device

Another possible tool in getting away from desktop-oriented CAD.
Needs to input precise measurements. These often come from calipers anyway,
so why not use that input device directly instead of reading and entering in machine.
Possible with [digital calipers](https://en.wikipedia.org/wiki/Calipers#Digital_caliper).
Seems most rely on a RS232/USB cable, which is a bit of a bummer.
But perhaps one could fabricate some, using PCB etching, with wireless support??



# Inspiration

[Design at Large- Stefanie Mueller](https://www.youtube.com/watch?v=cLUyTK72xXU)

In order to enable non-professional users to digitally fabricate, we need to:
* increase the
* 
Need to move to 'direct '

LaserOrigimi, folding to make 3d objects
LaserSheet
WirePrint 

http://crossfab-workshop.com/



