
Repeater systems.

## Digital Mobile Radio (DMR).
 
DMR Tier I products are for licence-free use in the European PMR446 band.
Maximum of 0.5 watts RF.

DMR uses the internet as the backbone for carrying communications.
Adding an MMDVM board to a Raspberry Pi is one common way to create a hotspot.

Uses AMBE vocoder.

## DMR handhelds

Baofeng DM-32UV seems nice. 80 USD. Also has GPS and APRS.
! no open firmware as of November 2026?

Lilygo T-TWR plus. Development kit. Using SA868 module with ESP32.
https://github.com/Xinyuan-LilyGO/T-TWR
Supported by OpenRTX.

## Open source firmware

OpenRTX. Firmware for various digital mode handheld/portable radios.
https://github.com/OpenRTX/OpenRTX/


## AMBE vocoder

Low bitrate speech encoding.
Developed by Digital Voice Systems Inc. (DVSI).
Proprietary and patented.

Multiple incompatible versions: AMBE original, AMBE+ and AMBE+2.

Open-source implementations:
- https://github.com/arancormonk/mbelib-neo

## Brandmeister network
https://brandmeister.network

Hoseline - listen live to talkgroups from network.
https://hose.brandmeister.network/

Repeaters in Norway
https://brandmeister.no/repeaters

## World Wide Check-In
A weekly international net operating on Talk Group 91 of the BrandMeister network.
Every Saturday at 16:00 UTC.

## EchoLink

https://echolink.org/

A VoIP system that links FM repeaters and simplex nodes to the internet,
and to PC or phone users.
It needs licensed-callsign validation.

Very few to no EchoLink repeaters in Norway?

## AllStarLink 

A VoIP linking system for FM.

## SVTLink

https://github.com/sm0svx/svxlink
Supports EchoLink directly.

Typically on UHF or VHF?

SvxReflector can connect multiple repeaters into a network.

SVX Reflector network
https://www.reflector-network.com/

Swedish network
https://svxportal.sm2ampr.net/map.php

Presentation om SvxLink på SSA:s Årsmöte 2025
https://youtu.be/RFMwINp5ucA?si=T6USLPnryCVNx-C5

LB4OK - Stian near Bergen is a Norwegian ham that has tested SvxLink with success.
https://lb4ok.no/svxlink-node-in-a-box/

### TETRA - Terrestrial Trunked Radio 
Formerly Trans-European Trunked Radio
Digital protocol. Uses TDMA.
Used for emergency services in many countries.

https://en.wikipedia.org/wiki/TETRA

Similar to P25.

HamTetra Network
All about Tetra for Amateur Radio Ops
https://www.hamtetra.com/


## DMRGateway
https://github.com/g4klx/DMRGateway

## MMDVM (Multi-Mode Digital Voice Modem)
https://github.com/g4klx/MMDVM

Runs on the Arduino Due, the ST-Micro STM32F4xxx and STM32F7xxx processors, as well as the Teensy 3.5/3.6.


## WPSD

https://w0chp.radio/wpsd/
Supports DMR, D-Star, Yaesu System Fusion (YSF), P25, NXDN, and POCSAG.

WPSD has taken over from MMDVM?

## Pi-star

https://www.pistar.uk/

Pre-configured SD Card image for the Raspbperry Pi (and other ARM based single board computers).


### Hardware for MMDVM / WPSD


Multiple hardware boards for MMDVM
https://zumradio.com/products.html

https://www.bi7jta.org/shop

MMDVM_HS_Hat for RPI Zero
https://github.com/mathisschmieder/MMDVM_HS_Hat
