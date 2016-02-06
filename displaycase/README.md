
# Lyngen

An octagonal display case, designed for mounting around a column -
especially the huge Norway spruce that holds the roof of [MIT Fablab Norway](http://www.fablab.no/).

![Render of design](./img/displaycase-render.png)

Concept by Haakon Karlsen, modelling & fabricated by [Jon Nordby](http://jonnor.com), with help from [Jens Dyvik](http://dyvikdesign.com).
First version made in Lyngen, after Nordic Fablab basecamp, January 2016.

## Materials

Top & bottom parts were milled in 27 mm wood used for benchplates, but any wood with thickness >18 mm should work.
The vertical panels are designed for 5.7 mm acrylic, but 6 mm should work without redesign.
By changing the parameters in the source files, can adapt to approx 5-8 mm.
Glass instead of acrylic can be used for the front, and vertical panels could be wood (plywood or MDF) instead of acrylic.

## Sources

DXF parts are made for a circular central column between 800-1000 mm circumference.
Adapt the parameters in the design for different sizes.

[FreeCAD project file](./lyngen.fcstd) |
[DXF lasercut parts](./export/lyngen-lasercut-1.dxf) |
[DXF milled parts](./export/lyngen-milled-1.dxf) |

Without too much work, the model could be adapted to mounting against a flat wall -
cut off and add a slot along the backside.

## How to build

### Make parts

* CNC-mill: 2 halves for top plate, 2 halves for bottom plate, 4 butterflies, and 4-8 brackets.
* Lasercut or mill, 8 side-walls
* Lasercut or mill, 8 back-walls
* Lasercut or mill, 12 shelves
* (optional) Lasercut or mill, 8 front windows

To be able to slide the front window out, the top plate groves should be cut all the way through (versus ~50% for bottom slots).

### Assembly

* Assemble the vertical panels to each of the bottom halves.
* Attach the brackets to the central column
* Move the bottom plate halves onto the brackets (second pair of hands useful here).
* Use the butterflies to connect the two pieces of bottom plate. Fasten the butterfly with short screws. 
* Slide the two halves of the top plate down onto the vertical plates.
* Use the butterflies to connect the two pieces of top plate. Fasten butterfly with short screws.
* (optional) Slide in front windows, through the top slot
* Attach bottom plate to brackets using screws, or use three-four wedges to prevent sideways motion.
* (optional) Use 2 brackets to fasten top plate to column, or add two wedges to prevent sideways motion.


# QR description tags

We want to have a physical description tag, which is linked to online documentation for more information.

[Example QR doc template](./img/qrdoc-template.png)

This allows viewers to quickly get to the story behind the, and for digitally fabricated objects,
to the files needed to reproduce it.

If you are deploying this, also consider providing a device which have a QR code reader included,
for instance an old smartphone and tablet. This allows people to scan without needing to
have a smartphone with installed app. Sadly QR-code apps, and user knowledge, is not that common yet...

## How to create new tag

[SVG template](./qrdoc-template.svg). Recommended print size: 80x40 mm

To create a new one:

1. Put your documentation online, with some URL
2. Generate a QR code for the URL, ex using [online tool](http://qr-code-generator.com/)
3. Open SVG template in [Inkscape](http://inkscape.org/)
4. Replace the URL, description, medium and QR-code with your data
5. Print out, or laser-engrave the label
6. Place onto object, or where object is displayed

## TODO

* Test writing QR-codes using laser-cutter. Especiallly in coode


## Related

* [Introspectable objects](https://github.com/jonnor/random/blob/master/digital-fabrication/introspectable-objects.md)
