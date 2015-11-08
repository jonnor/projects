use <rack_and_pinion.scad> // http://www.thingiverse.com/thing:172508/#files

//CP (mm/tooth), width (mm), thickness(of base) (mm), # teeth
width = 6;
cp=4;
rackTeeth = 20;
//rack(cp,rackTeeth,width,2);

// a simple pinion and translation / rotation to make it mesh the rack
pinionTeeth = 10;
shaftDiameter = 0;
translate([0,-10.5,0]) rotate([0,0,360/10/2]) pinion(cp,pinionTeeth,width,shaftDiameter);