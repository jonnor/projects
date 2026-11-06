
## Software Defined Radio

Simple DIY versions

- [Doctor Volt: Super Simple Breadboard-SDR Receiver from 50 kHz to 30 MHz](https://www.youtube.com/watch?v=HCDi5qV1cmU).
Using Tayloe Quadrature Detector, with ESP32 for clock generation, then into a soundcard.
Used [Quisk](https://james.ahlstrom.name/quisk/) as the SDR software. Python-based. 
Allows scripts for communicating the frequency changes to the ESP32 for control.
Up to 20 Mhz with ESP32. And up to 30 Mhz with optional Si5351.
- [](https://www.youtube.com/watch?v=nQ5e2Z3nYso).
Decoding lots of different digital transmissions, using ESP32 SDR receiver.
- [PicoRX](https://github.com/dawsonjon/PicoRX). RPI Pico based SDR.
Using a Tayloe Quadrature Detector.

References

- Dan Tayloe 2003: A Low-noise, High-performance Zero IF Quadrature Detector/Preamplifier.
[Link1](https://lea.hamradio.si/~s53dz/arhiv/7-SDR/doc/303Tayloe58.pdf).
Describes using an analog 1:4 multiplexer to chop up signal to do I-Q decoding.


## Testing

## OpenWebRX+ with RTL-SDR

OpenWebRX sets a center frequency for RTL-SDR.
RTL-SDR can only decode within the bandwidth from the center frequency.
Practical bandwidth is up to 2.4 MHz, so -+1.2 Mhz.
Common for all users.
Normally set using one of the selectable profiles.
Makes it quite annoying to do exploration on wider range of spectrum.
Especially for high frequencies like VHF, since need to move.

Makes it mostly relevant for providing easy (multi-user) access to predefined.
Of course antenna choice and location will also in practice limit what the SDR is actually good for.

## OpenWebRX+ on RPI 3b
With RPi3b, the CPU usage is around 50% with a single user of the web interface.

So will be very limited for multiple users. Should have RPI 4 or RPI 5 for multiple users,
and a regular PC for many users.
