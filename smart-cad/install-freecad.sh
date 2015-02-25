cd freecad
TARGET_DIR=~/.FreeCAD
MODULES=Mod/*
MACROS=*.FCMacro

LINK="echo ln -s"
LINK="ln -s"

for f in $MACROS
do
    inp=`pwd`/$f
    link=$TARGET_DIR/$f
    $LINK $inp $link
done
for f in $MODULES
do
    inp=`pwd`/$f
    link=$TARGET_DIR/$f
    $LINK $inp $link
done
