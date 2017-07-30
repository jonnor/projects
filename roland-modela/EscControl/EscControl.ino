
#include <Servo.h>

const uint8_t ON_SPEED = 180;
const uint8_t OFF_SPEED = 10;

const int8_t CONTROL_PIN = 8;
const int8_t ESC_PIN = 6; // must have PWM
const int8_t STATUS_PIN = LED_BUILTIN;

Servo esc;

void setup() {
  esc.attach(ESC_PIN);
  pinMode(CONTROL_PIN, INPUT);
  pinMode(STATUS_PIN, OUTPUT);
  Serial.begin(9600); // debugging
}


void loop() {

  const int spindleOn = !digitalRead(CONTROL_PIN);
  const int escSpeed = (spindleOn) ? ON_SPEED : OFF_SPEED;
  esc.write(escSpeed);
  digitalWrite(STATUS_PIN, spindleOn);

  delay(100); // no need to poll that often
  /*
    myservo.write(10);
    delay(2000);
    myservo.write(180);
   delay(2000);
   */
}
