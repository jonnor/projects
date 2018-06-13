

# Resin-based

Etsy.com. [Lots](https://www.etsy.com/no-en/search?q=epoxy+jewelry&explicit=1&page=3) of amazing looking products. Mostly rings,pendants.
Pure resin or resin+wood. 200-400 NOK. Sometimes glow-in-the-dark.
Resin 'stone' with wood base, silver ring inlay. 700-800 NOK.

Maybe silver + resin cast rings has good opportunity? Not found, might be able to push price up.

# Silver-based

Oxididation. Electroetching with laser-engraved masks?

# Integrated electronics

## Power source

Commonly available.

* CR2032 20x3.2mm 200mAh 3V. CR2025/CR2016
* CR1632 16x3.2mm 135mAh 3V. CR1620/CR1616
* CR1225 12x2.5mm 50mAh 3V.

1.5V, need multiple cells, or step-up

* SR54 11.6x3.1mm 80mAh 1.5V
* SR44 11.6x5.4mm 140mAh 1.5V

## 

* Necklace, 2 parts on front connected with a tube. LED (and switch?) in one, battery in other.
* Pendant with small lit gemstone. LED and switch IC PCB underneath gemstone. Battery in/on clasp. 
* Pendant big. All electronics, incl battery, in pendant.

## Tested

Using bent copper wires on PCB for coincell battery holder.
GND as wire loop lying on PCB, VBAT as a loop standing out from board, that coincell slides underneath. Works nicely.
A jig could help bending correct wires before placing.

# TODO

Capacitive touch on/off

* Test connecting jewelry to GND. Have a hole/slit in housing, where a metallic piece/wire rests as the electrode.

Practical sizes

* Test a CR coincell holder inline with the PCB instead of on the back.
U-shape opening on one side. Wires on each side for GND/VBAT.
Reduces thickness by board+component height, approx 3 mm.
* Test using silver chains as conductor to battery.
Challenge: Has to be safe to have them touching, avoid shorts.
Current limiter. Active, passive resistor.
* Test milling PCBs for TSSOP8, 0.65mm pitch.
* Use the microcontroller also for low-power capacitive sensing? Looks feasible with QTouch or TinyTouchLib on Attiny
Removing dedicated switch IC simplifies architecture, smaller footprint. Ex: AtTiny10 in SOT-23-6.
Makes software tuning of sensitivity possible?
Also enables riches UIs.

Lights in motion

* Add microcontroller
* Add 3-4 LEDs
* Decide how uC,battery,switch,LED parts should go together.
Challenges:
Need ability to move LEDs around to fit purpose
LEDS ofte need some distance to lit object
Battery is quite big.
Want to keep touchcap wire short.
Want to minimize wiring

* Find a good multiconductor cable?

Consumer friendliness

* Ensure easy to put in battery correctly.
* Ensure that putting battery incorrectly does not cause damage?
* Maybe allow to adjust brightness. Touch-and-hold during startup?

# Parts

Thin multiconductor cable.
[Digikey](https://www.digikey.com/products/en/cables-wires/multiple-conductor-cables/473?k=&pkeyword=&pv81=110&FV=138000a%2C138000b%2C138001a%2C1380056%2C674008c%2C674008d%2C67400b4%2C674013d%2C6740020%2C6740198%2C6740029%2C674019e%2C674019f%2C67401a1%2C67401b1%2C674002d%2C674002f%2C67401e3%2C67401e7%2C6740036%2C6740236%2C674003a%2C674003b%2C674003c%2C6740040%2C6740043%2C6740044%2C6740047%2C67402e1%2Cffe001d9%2C4f0000c%2C4f0007c%2C4f00002&quantity=0&ColumnSort=1000011&page=1&stock=1&nstock=1&pageSize=25)

[ATTiny10](https://www.digikey.no/product-detail/en/microchip-technology/ATTINY10-TS8R/ATTINY10-TS8RCT-ND/2477247)
