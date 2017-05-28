import math

D=2.85
r=(D/2.0)
A=math.pi*(r**2)
C=D*math.pi
print("A=%f, C=%f" % (A, C))
thickness=1
W=A/thickness
Cr=(thickness*2)+W+W
print("W=%f, Cr=%f" % (W, Cr))
ratio=Cr/C
print("ratio=%f" % ratio)
