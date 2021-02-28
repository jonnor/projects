
## Rendering

Blender commandline takes --python script argument
Cycles is availble headless. EEVE is not?

Command line rendering reference
https://docs.blender.org/manual/en/2.92/advanced/command_line/render.html
can render a .blend file with just a couple of arguments

shows Python API a little bit
https://stackoverflow.com/questions/14982836/rendering-and-saving-images-through-blender-python

Many examples of doing useful render things with Python,
with Blender bpy API
generating items from scratch
https://github.com/yuki-koyama/blender-cli-rendering/blob/master/04_principled_bsdf.py

There are Docker files for Blender 

https://github.com/ikester/blender-docker
allows to render a .blend with docker run
using the blender CLI

https://github.com/nytimes/rd-blender-docker
explicitly for headless usage

## Web API
? nothing ready made exists. TODO: search a bit more 

proof of concept. RabbitMQ queue. No HTTP frontend
https://github.com/MartijnBraam/blendqueue


- API frontend with HTTP API. Flask etc
- Render worker. Launch Blender as subprocess
- RabbitMQ communication

Blender is GPL, so this software should be too
