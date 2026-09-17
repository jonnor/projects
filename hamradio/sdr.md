
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


