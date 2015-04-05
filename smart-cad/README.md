

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
Input=camera/lens-model or calibration/characterization data. Use heuristics to provide default
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
Maybe including image pre-processing priming/normalization (contrast,levels)
Allow specifying constraints, on both number of features, which areas have features/not
* Higher-level features, derived on basic features
Combining multiple lines into one.
Making use of repetition to determine groups.

Ideas

* Use printed, smart tag sticker as a reference for size and projection?
Standard size, rectangular points. Stick onto object plane, detect using computer vision.
* Store the 
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

* [Finding rectangles, correct perspective](http://opencv-code.com/tutorials/automatic-perspective-correction-for-quadrilateral-objects/)
* [Converting between Bezier curves and lines+arcs](http://itc.ktu.lt/itc354/Riskus354.pdf)


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
