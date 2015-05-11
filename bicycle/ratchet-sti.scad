/* 
Parametric ratchet mechanism
License: CC BY-NC-SA 3.0
Version: 0.1
Date: 2010-05-23
By: rustedrobot

Changelog:
2012-02-06 - rustedrobot - added slant parmeter to demo

*/

// http://www.thingiverse.com/thing:8752
// TODO: adapt to make pull STI compatible
// 2.8mm pull. angle=
use <RatchetLib.scad>;

// inner (teeth) ring
inner_ring_diameter=30;		// outer diameter of the inner ring
inner_ring_height=5;		// height of the inner ring
inner_ring_thickness=6;		// thickess of the inner ring

// outer (arms) ring
outer_ring_diameter=50;		// outer diameter of the outer ring
outer_ring_height=10;		// height of the outer ring
outer_ring_thickness=2;		// thickness of the outer ring

// arms for outer ring (and cutting ratchet teeth on inner ring)
teeth=2*6;
arm_type="straight";		// the arm type (currently straight only)
arms=3;					// total number of radially symmetric arms 
teeth_multiple=ceil(teeth/arms);	// how many times more teeth than arms we will have
arm_height=inner_ring_height+5;				// height of the arm
arm_head_width=2;			// size of the head of the arm
arm_head_length=4;			// length of the arm head
arm_shaft_width=2;			// width of non-head part of the arm

// other settings
ratchet_direction="counter-clockwise";
// which way the outer ring should be able to move
slant=0; // slant in degrees of the ratchet arm head, between 0 and 50
tolerance=0.1; // padding around arm head with when cutting ratchet teeth
facets=50; // number of facets for cylinders

// =======================================================================
outer_ratchet_ring(
	ratchet_direction,
	inner_ring_diameter,
	inner_ring_height,
	inner_ring_thickness,
	outer_ring_diameter,
	outer_ring_height,
	outer_ring_thickness,
	arms,
	arm_type,
	arm_head_width,
	arm_head_length,
	arm_shaft_width,
	arm_height,
	tolerance,
	slant,
	facets
	);

inner_ratchet_ring(
	ratchet_direction,
	inner_ring_diameter,
	inner_ring_height,
	inner_ring_thickness,
	outer_ring_diameter,
	outer_ring_height,
	outer_ring_thickness,
	arms,
	arm_type,
	arm_head_width,
	arm_head_length,
	arm_height,
	teeth_multiple,
	tolerance,
	slant,
	facets);