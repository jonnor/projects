
# FreeCAD tools & learnings

[FreeCAD](http://freecadweb.org/) is an excellent open source parametric solid modelling CAD software,
which I use for almost all my modelling. Here are some tools, tips & tricks that I've developed.

## Macros

## Image scale to reference

When you import an image into 3d-view using a ImagePlane, the image is sized based on DPI*pixels.
If the image is a photograph of an object, this is unlikely to be the correct physical length.
The [imageScaleReference](./macros/imageScaleReference.FCMacro) macro lets you *scale image
by specifying the distance between two points*.
Very useful when working with images as references, to trace complex curves,
design something that fits or interfaces.


## Tools

* RML-format CAM post-processor, [for Roland MDX](https://github.com/FreeCAD/FreeCAD/blob/master/src/Mod/Path/PathScripts/rml_post.py)


## TODO

* Test wether FreeCAD macros are picked up when in subdirectories
* Create separate repo for FreeCAD macros
* Maybe also add custom workbench setup?

# Wanted

### Creating joinery.
Tools/scripts for creating everything from simple dowel+hole/mortise+tendon, finger-joints and cross-laps.

* https://en.wikipedia.org/wiki/Woodworking_joints
* http://www.core77.com/posts/43001/Reference-The-Ultimate-Wood-Joint-Visual-Reference-Guide

Related to below idea about sectioning models, as in that case joinery could be automatically made.
Related to Daniel. working on scripts for doing living-hinge type things.
Look at how people do this in advanced tools like Rhino/Grasshopper, AutoCAD etc?
[FreeCAD forum discussion](http://forum.freecadweb.org/viewtopic.php?f=8&t=13023&p=104266#p104266)

### On-canvas labelling of parts

A good 3d-model is useful for illustrating a concept.
But to make it really understandable, would be nice to be able to have text labels pointing at the individual parts.
Could use the names of objects. Needs no extra UI and encourages good naming.

Related, it could be desirable to name a constraint, and show that name as well.
Especially for parametric models that are designed for customization.

### Better exporting tools

Produce all the 'deliverables'. Could be a script/macro.
Should be runnable both from within GUI and commandline (for use on Travis CI).
Could for instance walk through document, and export everything with names
'part.stl', 'mypart.dxf' and 'ppp.step,stl'. Should have option for the prefix. Maybe default to 'export/$project-' ?

### Unrolling a sketch line

For use with PathArray where one is a complex geometry, and
one is the same just linear. Should update length of linear line to match sketch geometry.
Maybe related: http://www.freecadweb.org/wiki/index.php?title=Macro_unrollRuledSurface

### A parametric/connected 'cross-section tool'.
Currently the Part::CrossSection creates a copy which is not updated on changes to the part it comes from.
I often used this for DXF export (for lasercut/milling). Then it is irritating (and error-prone) that
it does not update...

It may be that Draft::Shape2dView does update


## Learned

Rebasing part features
----------------------

Sometimes one changes a feature that other part features depend on,
for instance adds chamfer/fillet to a flat geometry. This operation
creates a new object, but existing geometry still references the old object.

Can be done manually in the Python console.
Use `Tools -> Dependency Graph` to see existing relationships.

Challenges is that different operations
Here are some 

    .Shapes = [new]
    .Objects = [new]
    .Base = new

TODO: create a macro which can do this?

Needs to take the old object and the new objects as input.
(rebase everything that depends on it)
Should be an undoable operation as it probably does not work in all cases...


Partitioning/sectioning/tile model
------------------------

Sometimes one would like to split up a model
For instance to create composite objects which are bigger than available printer build volume,
to use multiple printers in parallel or to keep time of individual jobs down.

Example use is for hollow objects which will be coated with glass fiber, like foils/wings.

Can be done manually by creating a set of `Cube` and using `Intersection boolean` for each tile.


Macro in progress

    import math

    doc = App.ActiveDocument

    target = Gui.Selection.getSelection()[0]
    assert(target)
    bounds = target.Shape.BoundBox

    # TODO: accept size from GUI?
    # TODO: consider size only as a maximum
    size = (60, 60, 60)
    origin = (bounds.XMin, bounds.YMin, bounds.ZMin)
    tiles = (int(math.ceil((bounds.XMax-bounds.XMin)/size[0])),
	         int(math.ceil((bounds.YMax-bounds.YMin)/size[1])),
	         int(math.ceil((bounds.ZMax-bounds.ZMin)/size[2]))
    )

    # TODO: make tiles be symmetric to centerline of object?
    # TODO: export as .stl files for 3d-printing (or wirecutting/milling)?

    objects = []

    for tx in range(0, tiles[0]):
	    for ty in range(0, tiles[1]):
		    tile = doc.addObject("Part::Box","Box")
		    tile.Height, tile.Width, tile.Length = size[0], size[1], size[2]
		    tile.Placement.move(App.Vector(origin[0]+size[0]*tx, origin[1]+size[1]*ty, origin[2]+0))
		    common = doc.addObject("Part::MultiCommon","Common")
		    common.Shapes = [tile, target]
		    objects.append(tile)
		    objects.append(common)

    group = doc.addObject("App::DocumentObjectGroup","Group")
    group.Group = objects
    group.Label = "Tiles of " + str(target.Label)

    doc.recompute()


Should take object, origin/start of the grid,
the axis to lay out grid across,
and size/number of partitions.

Plane could default to XY/ZY
Origin should default to lower left in plane

In simple mode could just select object, (max) size for a tile,


Considering structural strength of parts
------------------------------

For 3d-printing, direction when producing matters a lot.
Having a visualization of the intended printing direction,
and thus the layer direction.

Rules of thumb


