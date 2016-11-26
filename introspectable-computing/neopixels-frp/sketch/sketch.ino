
#include "pixels.hpp"

Config config;
State state;

void setup() {
  pinMode(config.leds[0].pinR, OUTPUT);
  pinMode(config.leds[0].pinG, OUTPUT);
  pinMode(config.leds[0].pinB, OUTPUT);
}

bool
realizeState(const State &state, const Config &config) {
  analogWrite(config.leds[0].pinR, state.ledColors[0].r);
  analogWrite(config.leds[0].pinG, state.ledColors[0].g);
  analogWrite(config.leds[0].pinB, state.ledColors[0].b);
  return true;
}

void loop() {
  // put your main code here, to run repeatedly:
  const Input input = { (long)millis(), 1000, { 0, 255, 255 } };
  state = nextState(input, state);
  //delay(1);
  realizeState(state, config);
}
