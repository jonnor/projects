# Makerbot

## Using open software

My housemate has a `Makerbot Replicator 2`.
However, it does not accept G-code, and the `Makerware` software is propriatary, Windows-only.
So I cannot use it without borrowing my friends Windows laptop.

Others have hit the same problem, and it does look like there are ways to convert from gcode to the custom `X3G` format.

References

* [GPX Python script for Cura (2013)](http://www.thingiverse.com/thing:81425)
* [GPX](https://github.com/markwal/GPX). Converts gcode to X3G format.
* [Using GPX with Cura 15.04](https://groups.google.com/forum/?fromgroups=#!topic/gpx-converter/LBFZgCDg6yg)
* [X3GWriter.py script for Cura (2?)](https://github.com/Ghostkeeper/X3GWriter).
Small wrapper around a binary-only `cura_x3g.exe`, undocumented where this comes from.
Filed a [request for docs](https://github.com/Ghostkeeper/X3GWriter/issues/1).
