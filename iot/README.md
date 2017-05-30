
# Devices

Designed for easy fabrication in a hackerspace/makerspace/fablab.
Sends and receives data on MQTT, with WiFi as the main transport.
The devices are stupid sensor/actuators, application ideas to happen elsewhere. Remote tunable.
Firmware to supports the [MsgFlo](https://msgflo.org) discovery protocol.

Project nickname: `stupidsmart`.

## 4 Buttons

For simple user interfaces

Features

* 4 RGB leds, with PWM control
* 4 capacitive touch areas.
* Exchangable paper labels
* Sends message on state change.
Maybe, configurable sensitivity? Threshold, hysteresis, mintime.
Maybe, also send raw capacity read value. Can be used for analog inputs!
* Each LED channel individually controllable
* Maybe. Space for optional LiPo battery

Fabrication

* 3d-printed chassis/casing
* Simple PCB / handwired electronics 
* Copper-tape for capacitive touch
* Designed for ESP8266 modules like NodeMCU

Example usecases

* Doorbell
* Start/stop thing
* Simon Says!

Implementation

* Multiplex/charlieplex the LED channels. 7 pins?
* Use the timed-discharge trick for capacitive sensing. 4 pins?

### TODO

Make v0 hardware.
* Just hand-solder a stripboard.
* Use single-channel LED.
* Can use aluminum foil instead of copper.
* Use cardboard instead of 3d-print.
* Tape the shit together.

Make v0 software
* Setup on ESP8266
* On/off cap sensing
* On/off LED support


## 433 gateway

Bridges to 433Mhz devices.
Allows using existing non-IoT devices, found readily in local shops.

Features

* Read and write support

Usecases

* Remote controlled relays
* Weather stations

## Environment monitor

Features

* Temperature
* PIR motion
* Sound level
* Ambient light

## Device current sensing

Allegro ACS712 is a nice fully-integrated IC based on Hall-sensor, available from many places online:

* [Sparkfun](https://www.sparkfun.com/products/11005)

# References

Solar cell panels

* http://www.dx.com/p/lx-b150-1-5w-laminated-solar-monocrystalline-silicon-cell-panel-board-black-dark-blue-218501
* http://www.dx.com/p/lx-b580-0-8w-pet-laminated-solar-monocrystalline-silicon-cell-panel-black-blue-184629
* http://www.dx.com/p/si-solar-cell-panel-4-5v-5ma-12984
* http://www.dx.com/p/si-solar-cell-panel-4v-6ma-12985
