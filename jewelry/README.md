

# Resin-based

Etsy.com. [Lots](https://www.etsy.com/no-en/search?q=epoxy+jewelry&explicit=1&page=3) of amazing looking products. Mostly rings,pendants.
Pure resin or resin+wood. 200-400 NOK. Sometimes glow-in-the-dark.
Resin 'stone' with wood base, silver ring inlay. 700-800 NOK.

Maybe silver + resin cast rings has good opportunity? Not found, might be able to push price up.

# Silver-based

Oxididation. Electroetching with laser-engraved masks?

# Gemstones

Small oval gemstones, 10-20 mm. [1](https://www.gemselect.com/group/gemselect.php?a=0&base_shape=Oval,Pear,Round&min_l=10.00&max_l=20.00&min_w=10.00&max_w=20.00&styles=Cabochon%27,%27Plain-Cut&price_asc=1&page=1)


# Rechargable

Power board for wearable or other battery powered electronics.

- Integrated charger for LIR coincell batteries.
- Integrated touch-controller for power on/off.
- Charging via USB 4pin magnetic cable.
- Fits LIR16xx,LIR20xx and LIR24xx directly.
- Board fits within 20 mm diameter, 2 mm height

## Board connector

Finish base board
- Make notches for battery pins
- Add throughhole connectors for outputs
- Try to find a 1.0mm pitch connector
Alt, is there some 1.27mm or 1.0mm flat cable
- Finish routing

Top PCB flexible
- For 3030 LED
Calculate length needed
4/5 pin connetor pitch.
- Use FPC connector also this side?
Then need to get some standard cable


## TODO

- Order base PCBs
- Order PCBA components
- Design and print a test stand

After receiving parts

- Design and print a test holder
- Test the PCBs

Projected update

- Make LED/touch PCB for top.
Connections power,GND,touch
- Integrate into domed design
Add rotation lock/keying in bottom versus sides
- Attempt to print including light-holes

## Parts 

Diode Shottky SOD323
https://www.digikey.com/en/products/filter/diodes-rectifiers-single/280?s=N4IgjCBcpgbFoDGUBmBDANgZwKYBoQB7KAbRAGYBOAJgBZ4DaAGJuiRlsSiAXQIAcALlBABlQQCcAlgDsA5iAC%2BBSvGghkkdNnxFSIZk3IB2ABwg%2BIISPHT5SggFpqCDVEkBXXcUhkArCAqFgLCkCAOII4B6prauAQ%2BZC6W1mFKyiBqoFIAJiKOYEzsVqHhBACOggCeIoWBINX8OCJoWMiKikA

PMOS SOT-223
https://www.digikey.com/en/products/filter/transistors-fets-mosfets-single/278?s=N4IgjCBcoGwAwyqAxlAZgQwDYGcCmANCAPZQDaIAzABwCsYclIAukQA4AuUIAyhwE4BLAHYBzEAF8iMMACYkIVJEy5CJcuBi0YsuCCKzDYGAE59IWTQAsc87NoB2KzCYHqT2lfOmwn7ybAHRGkTWV9zahsrWgjHLXMGOGiHBLgk2mpUpOp5IkSraky8uAyTM2LaUIg8hhgHGJrPMISrBDhq8BtaSoTHOAdXcD66BJNKJJSDNOodO0ofYIsHeuMWdi5IXgERcSlwWQCFJRV8IlJIClbaSiDzK5vJkFb2kwankqt6u4-ltZBObh8IRiSREAC08mgiigAgArmpzhQ3mZWP8NiBJHtEFDBAATbhghgdAGbcwARw4AE9uAxzFS2HhuBgcKgJBIgA

1.27 mm headers

LIR1620 / LIR1632
LIR2032
LIR2450
Rainpro @ Aliexpress

FPC connector
https://www.digikey.com/en/products/detail/te-connectivity-amp-connectors/1734839-5/1860461


# Watch
Watch case 42 mm 43mm 
For movement ST36 ETA6497 ETA6498 P212
transparent back

https://www.aliexpress.com/item/4000229421123.html
https://www.aliexpress.com/item/4000689159663.html
https://www.aliexpress.com/item/32907052343.html

# Integrated electronics

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

* "touch me". Touch. Proximity. Gestures. Capacitive sensing.
* "move me". Motion. Angle. Accelerometer
* "I hear you". Sound. Music, wearer talking. Microphone.
* "I feel you". Body state. Temperature, breathing, heartbeat.
* "get close to me". Distance

Modulate intensity using touch proximity?

Accelerometers are available with `<10uA` consumption in low power mode.
I2C communication and configurable interrupts. Ex: LIS3DE, MMA8653FC 

# Learnings

Minimum hole size in cardboard. Vector: 0.5mm

# Rev2

* Total size `<40mm` diam, `<15 mm` height. Domed top. PCB 20mm diam, `<3mm` component height.
* LiPo battery, integrated charger. LIR2450-LIR2016
* Pogopin connector for charging
* TPP223 touch controller
* 3030 or 3535 white LED. Low-profile, 1mm. Low voltage? 3V
* LED constant-current driver

0.6mm PCB is OK priced on PCBWay. 0.4 and 0.2mm twice the price.
10mA on time.

FPC connector.
https://www.digikey.com/products/en/connectors-interconnects/ffc-fpc-flat-flexible-connectors/399?FV=fff40016%2Cfff80421%2C1600018%2C1600006%2C1b4c0008%2Cffe0018f%2Cfffc0017%2Cfffc0384&quantity=20&ColumnSort=1000011&page=2&stock=1&nstock=1&pageSize=25

100mAh, 10uA => 1 year.

LEDs

https://www.digikey.com/products/en/optoelectronics/led-lighting-white/124?FV=7%7C2%2C37%7C421162%2C319%7C133405%2C319%7C134015%2C319%7C134067%2C319%7C134280%2C319%7C134430%2C319%7C134479%2C319%7C134532%2C319%7C134768%2C319%7C135281%2C319%7C135361%2C319%7C135451%2C319%7C135630%2C319%7C135739%2C319%7C136170%2C319%7C136604%2C319%7C136643%2C319%7C136960%2C319%7C137263%2C319%7C137391%2C319%7C202627%2C319%7C202630%2C1500%7C4992%2C1500%7C5027%2C1500%7C5068%2C1500%7C5221%2C1500%7C5295%2C1500%7C5576%2C1500%7C5588%2C1500%7C5744%2C1500%7C5802%2C1500%7C5803%2C1500%7C5812%2C1500%7C5916%2C1500%7C5964%2C1500%7C6031%2C1500%7C6094%2C1500%7C6506%2C-8%7C124%2C1291%7C182983%2C1291%7C193429&quantity=10&ColumnSort=1000011&page=2&stock=1&nstock=1&pageSize=25

# TODO

* Make bottom PCB.
* Make LED PCB. Touch sensor electrode also?


Dock

* Fabricate a PCB for dock
* Make docking station mechanics


Later

* Move to separate repository


## USB DFU

USB DFU on STM32L432 and STM32L433
not conforming to spec?
https://community.st.com/s/question/0D50X00009XkfyUSAR/usb-dfu-on-stm32l432-and-stm32l433
Issue seems fixed in latest st-util?
https://sourceforge.net/p/dfu-util/tickets/40/

User-mode bootloader
https://github.com/nichtgedacht/L433CCTx-bootloader

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



