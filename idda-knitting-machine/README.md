
Idda: A circular knitting machine
==================

Reverse engineered from the [Addi Express](https://www.google.no/?#q=addi+express).

Features

* 22 or 46 needle. 
* Can create circular and rectangular swatches (using back-and-forth knit)
* Max swatch for 46 needle: 17.75 inch
* Manual cast-on and bind-off
* Manual forwarding

Motivation

* Be able to replicate using distributed digital manufacturing (3d-print/CNC)
* Be able to customize. Different number of needles, needle/mask size, adapting to different materials, adding automation

Status
--------
**Paused**

The [Circular Knitic](http://www.varvarag.info/circular-knitic)
[(Github)](https://github.com/var-mar/circular_knitic)
[(docs)](http://issuu.com/marcanet/docs/circular_knitic_documentation)
is an open source functional implementation of the same mechanism as Idda.

We propose that further development is done as improvements to the base provided by the Circular Knitic.
For instance allowing it to be:

* Configured for different sizes
* Be reproducable with only one digital fabrication machine (need only 3d-print OR laser/CNC)
* Use less special parts (like steel needles and aluminum profiles)
* Improve the portability

There are some FreeCAD source files included here.

[Needle](./needle.fcstd)

![Needle prototype model](./doc/needle-prototype.png)

[Track](./track.fcstd)

![Track prototype model](./doc/track-prototype.png)


References
----------

* [Replacement needles](http://www.amazon.com/Express-Knitting-Machine-Replacement-Needles/dp/B004T2MHVA) for Adda Express
* [BangGood: DIY scart hat knitting machine](http://www.banggood.com/Creative-DIY-Scarf-Hat-Quick-Knitting-Machine-Handheld-Handwork-Weaving-Tool-for-Adult-Child-p-1030934.html),
a cheap copy (30 USD) with 22 needles. I purchased one of these for testing on May 03 2016.
* [Listing of different circular knitting machines](http://www.kobakant.at/DIY/?p=1144).
[PRYM 624170 Strickmühle MAXI](http://www.amazon.de/PRYM-624170-Strickm%C3%BChle-MAXI/dp/B000VKFJ32/ref=sr_1_4?ie=UTF8&s=garden&qid=1245759008&sr=8-4) seems to be the cheapest 44 needle, at around 50 EUR.
* Barbie / Mattel also has a [circular knitting machine](https://www.flickr.com/photos/plusea/3675240262)
* [List of antique manufacturers](cskms.org/where-to-find-a-csm/) for "circular sock machines".
These are often made of steel, as small-scale industrial units dating back to late 1800.
