
import subprocess
import FreeCAD as App
import Part


base = "/home/jon/projects/smart-cad"

# TODO: add code for recompiling the C++ code

# note, XSize and YSize are actually set by the GUI in FreeCAD?

def detect_circles(image, sketch):

    output = subprocess.check_output([base+'/detect-circles', image.ImageFile])

    # assumes image is positioned at 0,0,0
    topRight = App.Vector(-image.XSize/2, image.YSize/2, 0)

    for line in output.split("\n"):
        tok = line.split(' ')
        if len(tok) >= 4 and tok[0] == 'circle':
            x = float(tok[1])
            y = float(tok[2])
            radius = float(tok[3])
            circle = Part.Circle(topRight+App.Vector(x,-y,0),App.Vector(0,0,1),radius)
            sketch.addGeometry(circle)

    return sketch

def correct_perspective(image, sketch):

    # assumes image is positioned at 0,0,0
    topRight = App.Vector(-image.XSize/2, image.YSize/2, 0)

    points = []
    for v in sketch.Geometry:
        points.append(v.x-topRight.x)
        points.append(topRight.y-v.y)

    args = [base+'/correct-perspective', image.ImageFile]
    args += [str(p) for p in points]
    output = subprocess.check_output(args)

    oldfile = image.ImageFile
    filename = output.strip()
    image.ImageFile = filename

    return oldfile

if __name__ == '__main__':
    pass
