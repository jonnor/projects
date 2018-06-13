
# Applications

* Image/texture synthesis for webdesign
* Making unique 2/3d-models for digital fabrication
* Image filtering

# Ideas

## Obeying mechanical constraints
In order to move away from just "texturing" but creating significant changes,
that may also have functional/structural impact,
and ensuring these preserve usefulness of object.
Minimum height/width, material thickness or strength.


## Simulated life
Simulate a dynamic system defined by 2/3d-topology, where
simulated life influence the topology based on simple rules.
Kind of a Game-of-Life.


'Series' of objects can be done using the same system, where each object instance
is a diffent generation of the system.

# References

Techniques

* Lindenmayer systems. "L-systems"

Other

* [Generative art links](http://blog.hvidtfeldts.net/index.php/generative-art-links/),
by Fragmentarium author.
* [What is Generative Art](http://philipgalanter.com/downloads/ga2003_paper.pdf)

Softwares

* TopMod3d. [Paper](https://www.viz.tamu.edu/faculty/ergun/research/topology/papers/cgi08.pdf)
GPL-licensed software for creating generative topological 3d-meshes.

# Information layout
Ex on website.

Greedy algorithm. Does optimal local choice
Operates section by section
Content-first layout.
Consecutive sections consider the top N items, ask sections to lay them out.
`O( (items/N) * templates )`

A section template

* Declares number of items supported
* Must support any item type(s) for these N items
* Given N items, scores the content-fit
* Standardized interface, pluggable
* Website config: template set

Template ex

* 1 full-spread.
* 2: Primary above, secondary below. And v.v.
* 2: Primary right, secondary left. And v.v.
* 3: Primary mid, secondary left+right. Flip r/l. Flip top/bottom
* 4: Pri/sec 1, pri/sec 2.
* 4: 4 equals
* 10: Gallery

Layout fitness

* Normal range: 0.0-1.0. Maybe allow impossible: infinity. 
* Spaciness: Right amount of whitespace between items
* Crampedness: Item should have enough space. Text legibility, image features
* Balance: Item should fill their space to same proportion
* Importance: Items are given space according to their relative importance
* Should these also be reported as 'features'?
* Might want/need to normalize scores based on the templates optimism to get fairness.
Calculate across (sample of) all possibilities contents.
For one template, can show content according to preference order.
For a piece of content, can show top-3 templates.

Section preference

* A way for user to directly influence choice

Layout diversity

* Pri: Avoiding repeated layouts
* Good: Having some structure
* maybe-nice-to-have: Rhythms of repeating elements

Content importance/emphasis

* Headlines+ 
* Images++

Content ordering

* Narrative
* Posted date
* Importance

