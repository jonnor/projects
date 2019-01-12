

# Resin-based

Etsy.com. [Lots](https://www.etsy.com/no-en/search?q=epoxy+jewelry&explicit=1&page=3) of amazing looking products. Mostly rings,pendants.
Pure resin or resin+wood. 200-400 NOK. Sometimes glow-in-the-dark.
Resin 'stone' with wood base, silver ring inlay. 700-800 NOK.

Maybe silver + resin cast rings has good opportunity? Not found, might be able to push price up.

# Silver-based

Oxididation. Electroetching with laser-engraved masks?

# Gemstones

Small oval gemstones, 10-20 mm. [1](https://www.gemselect.com/group/gemselect.php?a=0&base_shape=Oval,Pear,Round&min_l=10.00&max_l=20.00&min_w=10.00&max_w=20.00&styles=Cabochon%27,%27Plain-Cut&price_asc=1&page=1)

# Integrated electronics

## Power source

Commonly available.

* CR2032 20x3.2mm 200mAh 3V. CR2025/CR2016
* CR1632 16x3.2mm 135mAh 3V. CR1620/CR1616
* CR1225 12x2.5mm 50mAh 3V.

1.5V, need multiple cells, or step-up

* SR54 11.6x3.1mm 80mAh 1.5V
* SR44 11.6x5.4mm 140mAh 1.5V

## Structures

* Necklace, 2 parts on front connected with a tube. LED (and switch?) in one, battery in other.
* Pendant small. Eg with lit gemstone. LED and switch IC PCB underneath gemstone. Battery in/on clasp. 
* Pendant big. All electronics, incl battery, in pendant.

## Tested

Using bent copper wires on PCB for coincell battery holder.
GND as wire loop lying on PCB, VBAT as a loop standing out from board, that coincell slides underneath. Works nicely.
A jig could help bending correct wires before placing.

## Lights in motion

Animation ideas

* Subtle glow
* Glitter/sparkle. Random high-intensity bursts, alternating positions
* Together<->apart / center<->sides. 
* Swipe across. Random triggered, varying intensity
* Tick-tock. Move back/forward in a way that suggests clock motion

## Interactivity

* Touch. Proximity. Gestures. Capacitive sensing.
* "move me". Motion. Angle. Accelerometer
* Sound. Music, wearer talking. Microphone.
* "I feel you". Body state. Temperature, breathing, heartbeat.
* Distance

Modulate intensity using touch proximity?

Accelerometers are available with `<10uA` consumption in low power mode.
I2C communication and configurable interrupts. Ex: LIS3DE, MMA8653FC 

# Learnings

Minimum hole size in cardboard. Vector: 0.5mm

# Rev2

* LiPo battery, integrated charger. LIR2450-LIR2016
* Low-power MCU with hardware CapSense. Wake-on-touch.
[ATTiny3217 family](https://www.microchip.com/design-centers/8-bit/avr-mcus/device-selection/attiny3217)
* LED RGB array support. APA102 type. Two-wire, hardware SPI. 5V stepup.
* Pogopin connector, charge/reprogram. TX/RX/GND/VCC/RESET
* Pogopin to Micro USB docking-board. Incl USB-serial adapter.
* 20mm diameter max
* ? couple of APA102-2020 on board. For easy experimentation
* ? photodiode for configuring from phone.
* ? TC2030-MCP-BL ISP connection. http://www.tag-connect.com/tag-connect-pinout-specifications

ATTiny1617
Running. 10uA @ 32kHz, 4V. 2.5mA @ 5 Mhz.
Idle. Approx half.
Standby. 0.1uA (no pheripherals)
ADC/PTC and RTC can operate in Standby.
24QFN packages, 0.5mm pitch.
2.7V needed for 10Mhz.
ADC @ 50ksps: 325 uA.
10us wakeup from Standby.

PTC Low Power Mode, uses Sleepwalking to autonomously perform touch detection on a single sensor.
Only interrupts CPU when a valid touch is registered. Typical power consumption `<10uA`.
100mAh, 10uA => 1 year.

References

* UPDI is new 1-wire program and debug interface [pyupdi](https://github.com/mraardvark/pyupdi/blob/master/pyupdi.py)
* ATTiny with UPDI on Tag-Connect header, schematic. https://smayze.wordpress.com/2017/12/29/a-look-into-integrated-light-sources/
* [](AT12405: Low Power Sensor Design with PTC)

# TODO

Rev 1.1

* Test using a pogopin to connect back to PCB
* Twistlock tweaks. 
Add room for battery wire
Add holes for connecting sides
Add holes for connecting front
More size for

Rev 2.0 concept test

* Etch flexible PCB for APA102-2020 array.
Footprint. https://sc01.alicdn.com/kf/HTB1UE2.RpXXXXa_apXX760XFXXXt/221092177/HTB1UE2.RpXXXXa_apXX760XFXXXt.png
KiCAD. https://github.com/greatscottgadgets/gsg-kicad-lib/blob/master/gsg-modules.pretty/APA102-2020.kicad_mod
* Implement APA102 control
* Test capacitive touch proximity

Rev 2.0

* Design and send
* Implement capacitive touch on AtTiny.
* Finish code simulation setup
* Add simple animation, ex subtle glow
* Fabricate PCB for controller
* Make docking station hardware
* Deign and make docking PCB.
* Implement power saving
* Implement undervoltage protection.
http://www.ti.com/product/lm2623 ? Or just in uC software?

Later

* Setup simulation in Blender. Or raytracing in FreeCAD
* Test lasercut a reflector that covers electronics
* Find a way to put lightsource on top, battery/electronics in bottom.
LED w/connectors.
OR Convex reflector/mirror. 
* Move to separate repository 

Software control

* Create programming adapter with pogopins


# Ideas

Practical sizes

* Test a CR coincell holder inline with the PCB instead of on the back.
U-shape opening on one side. Wires on each side for GND/VBAT.
Reduces thickness by board+component height, approx 3 mm.
* Test using silver chains as conductor to battery.
Challenge: Has to be safe to have them touching, avoid shorts.
Current limiter. Active, passive resistor.

Consumer friendliness

* Ensure easy to put in battery correctly.
* Ensure that putting battery incorrectly does not cause damage?
* Maybe allow to adjust brightness. Touch-and-hold during startup?

Capacitive touch on/off

* Test have a hole/slit in housing, where a metallic piece/wire rests as the electrode.
Jewelry connected to GND.
* Test having a wire antenna sticking out towards front of rosebud.
With high sensitivity, can one switch using a gesture?

# Parts

Thin multiconductor cable.
[Digikey](https://www.digikey.com/products/en/cables-wires/multiple-conductor-cables/473?k=&pkeyword=&pv81=110&FV=138000a%2C138000b%2C138001a%2C1380056%2C674008c%2C674008d%2C67400b4%2C674013d%2C6740020%2C6740198%2C6740029%2C674019e%2C674019f%2C67401a1%2C67401b1%2C674002d%2C674002f%2C67401e3%2C67401e7%2C6740036%2C6740236%2C674003a%2C674003b%2C674003c%2C6740040%2C6740043%2C6740044%2C6740047%2C67402e1%2Cffe001d9%2C4f0000c%2C4f0007c%2C4f00002&quantity=0&ColumnSort=1000011&page=1&stock=1&nstock=1&pageSize=25)

[Small white power LEDs](https://www.digikey.no/products/en/optoelectronics/led-lighting-white/124?FV=b83bfa%2Cb84343%2Cb84345%2Cb8442f%2Cb84ff4%2Cb85aca%2Cb85ada%2Cb864db%2Cb86a30%2Cb86c09%2Cb87c2f%2Cb89a25%2Cb8a3d7%2Cb8a955%2Cb8a959%2Cb8a95c%2Cb8a95e%2Cb8a95f%2Cb8a962%2Cb8a96a%2Cb8a976%2Cb8a977%2Cb8a9a2%2Cb8a9a3%2Cb8a9a7%2Cb8a9a8%2Cb8a9ab%2Cb8a9ac%2Cb8a9ad%2Cb8a9ae%2Cb8a9af%2Cb8a9b0%2Cb8a9b1%2Cb8a9b6%2Cb8a9bc%2Cb8a9bd%2Cb8a9c0%2Cb8a9c1%2Cb8a9c8%2Cb8a9c9%2Cb8a9cd%2Cb8a9cf%2Cb8a9d0%2Cb8a9d2%2Cb8ab18%2Cb8b1f6%2Cb8b748%2C1140003%2C89c0103%2C89c0029%2C89c002b%2C89c002d%2C89c002f%2C89c0033%2Cab00066%2Cab00069%2Cab0006a%2Cab0006e%2Cab00072%2Cab00074%2Cab00075%2Cab0007a%2Cab000ad%2Cab000b8%2Cab00002%2Cab000d4%2Cab000d7%2Cab000d8%2Cab000e3%2Cab000e4%2Cab000ec%2Cab000fd%2Cab000ff%2Cab00121%2Cab00123%2Cab00003%2Cab00140%2Cab00141%2Cab00173%2Cab0023f%2Cab00007%2Cab00008%2Cab00051%2Cab00053%2Cab00054%2Cab0005b%2Cab00061%2Cab00062%2Cffe0007c&quantity=10&ColumnSort=1000011&page=1&stock=1&nstock=1&pageSize=25)

[White LEDs sidelight](https://www.digikey.no/products/en/optoelectronics/led-indication-discrete/105?FV=940066%2C940008%2C9403c3%2C9403c5%2C9403c6%2C1140160%2C89c0501%2C89c0515%2C89c0088%2C89c057f%2C89c0590%2C89c0592%2C89c0593%2C89c059a%2C89c059c%2C89c059d%2C89c00b1%2C89c00b2%2C89c00b3%2C89c00b4%2C89c00b5%2C89c00b6%2C89c00b7%2C89c00b9%2C89c00ba%2C89c00bc%2C89c00bd%2C89c00be%2C89c00c0%2C89c00c1%2C89c00c2%2C89c00c3%2C89c00c4%2C89c00c5%2C89c00c6%2C89c00c7%2C89c00c9%2C89c00cb%2C89c00cc%2C89c00cd%2C89c00ce%2C89c00d0%2C89c00d1%2C89c00d2%2C89c00d3%2C89c00d4%2C89c00d5%2C89c00d6%2C89c00d7%2C89c00da%2C89c00db%2C89c00dd%2C89c00df%2C89c00e1%2C89c00e2%2C89c00f1%2C89c00f2%2C89c00f3%2C89c00fa%2C89c0103%2C89c010a%2C89c0029%2C89c002a%2C89c002b%2C89c002c%2C89c01be%2C89c002d%2C89c002f%2C89c0030%2C89c0031%2C89c01ea%2C89c01f3%2C89c0032%2C89c01f4%2C89c01f5%2C89c01f6%2C89c01f8%2C89c0033%2C89c01fe%2C89c0200%2C89c0201%2C89c0034%2C89c0213%2C89c0214%2C89c0037%2C89c02d1%2C89c02dd%2C89c02e3%2C89c02e4%2C89c02e6%2C89c02ea%2C89c02eb%2C89c02ec%2C89c02f5%2C89c02f6%2C89c02f7%2C89c02fc%2C89c02fd%2C89c02fe%2C89c0303%2C89c0306%2C89c0328%2C89c0366%2C89c0369%2Cffe00069&quantity=10&ColumnSort=1000011&page=1&stock=1&nstock=1&datasheet=1&pageSize=25)


