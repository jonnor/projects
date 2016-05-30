// ConstantSpeed.pde
// -*- mode: C++ -*-

#include <AccelStepper.h>

const int DIR_PIN = 12;
const int PULSE_PIN = 13;
const int MOTOR_TYPE_DRIVER = 1;
AccelStepper stepper(MOTOR_TYPE_DRIVER, PULSE_PIN, DIR_PIN);

void setup()
{  
   stepper.setSpeed(-1250);
}

void loop()
{  
   stepper.runSpeed();
}
