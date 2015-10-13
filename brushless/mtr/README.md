# Mtr: stepper controller+driver firmware

## Designed for

* Bipolar stepper motors
* Driving H-brige directly (discrete or integrated)
* Single motor/axis per microcontroller
* Per-axis kinematics handling (acceleration, positioning)
* Taking config+movement commands over I2C or serial
* With ability to syncronize multiple instances for multi-axis/tool systems
* Possibility of current limiting motor windings
* Possibility of closed-loop feedback
* Primarily running on ARM Cortex, secondarily on AVR 8bit (Arduino)
* Ability to be end2end tested, both on host/emulated and on-device

## Status
Just words

## TODO

0.0.1, proof of concept

* Implement basic full-step control
* Test with hardware

0.1.0, Minimally useful

* Implement configurable acceleration
* Implement microstepping
* Complete in a working single-axis machine


0.2.0, Syncronized multi-axis

* Implement shared-clock syncronization
* 


# Research

### Raster-engraving

Some custom Marlin-derivative firmware have support for raster-engraving using `G7`

    G7 N0 L68 DAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAhaGBUQFRiZ0ZPVExARUU6RTpITD1GU05Q

      N: new line: increments Y axis by LASER_RASTER_MM_PER_PULSE *
    LASER_RASTER_ASPECT_RATIO from Configuration.h 0 = negative movement
    in the X axis, 1 = positive X axis movement.
      L: byte length of the packed pixel set
      D: data, base 64 encoded 0-255/pixel 

* https://groups.google.com/forum/#!topic/lansing-makers-network/h4-NNiaeNv0
* http://wiki.lansingmakersnetwork.org/equipment/buildlog_laser_cutter
* https://github.com/wreality/imagetogcode

