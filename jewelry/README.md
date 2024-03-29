

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

## Top PCB

Projected. 3030 with touch on back

- 3030 LED on top
- 4 pin connector 1.0mm pitch
- Touch plate on the bottom.
Rounded rectangle
Keep below 12mm diameter?

## Tests

Tested charging. Seems to work as-intended.
Tested reverse-polarity protection. Works.

Tested attaching battery.
The solder joints may come out on lower side of PCB.
Can interfere with mounting. Should adapt bottom plate to accomodate.

Tested attaching cable for top PCB.
The purchased FFC just melts the backing material instantly. FAIL. Should use a Kapton-based instead.
It was possible to remove the thick spacers, add a Kapton+HT polyester layers, and melt away the plastic, and then solder this on.
However it remains quite tricky to do.
A jig to help with alignment would help.
Proper light and flux would also help.
Longer traces and wider pitch should be considered for next revision.

Need approx 45 mm FPC cable to get to top of dome.

Tested having an external copper piece for touch.
Using a resing printed dome, approx 1mm thick. Touching from outside.
With a single wire and 47 pF, did not react.
With alu foil of approx 10x10 mm and 47 pF, did not react.
With alu foil of approx 10x0 mm and C2 removed, reacts easily.
Need no or a small value for C2. Test 1 pF?


## TODO

Projected PCB rev 1 testing

- Add flat part to model dome, for LED PCB
- Assemble a complete piece
- Make stand functional
Thickness and tolerances on connector needs fixing
Orientation of cable outlet should be rotated 90degrees
- Test connector and charging, reliability/ease-of-use
- Try plugging the chargint through-hole.
See if one can use just SMT pads. Frees up a lot of board space for components.



Projected PCB rev 2 send


- Make LED/touch PCB for top.
Connections power,GND,touch
Include into main PCB project?
- Probably, use SMT pads for charging
- Maybe switch to 1.27mm solder tab FPC


Projected PCB rev 2 testing

- Make jig for holding PCBs and FPC cable for soldering
- Complete assembly. 3 units



## Next version


APA102 2020 strip
- ish 4 mm wide
- 4 pin connector. On LED side?
- space for 0603 capacitor
- at least 60mm length, for Atlantis earcuffs
- connector for chaining
- exposed pads between LEDs for ability to cut-to-length
- as close as possible. Ex 3 mm spacing 
can skip in software if not all are used

Insp. https://www.pcbway.com/project/shareproject/SK9822_APA102_LED_Breakout_board_array.html

Merge with "projected"

TODO:
- Test APA102 2020 / SK9822 at 3.6V power
Has been reported working ok.
https://forum.pjrc.com/threads/30020-Teensy-APA102-POV-Poi-Pixel-Poi-Build-Tutorial?p=84907&viewfull=1#post84907
- Integrate a microcontroller. ATtiny1616 ?
- Do touch control in microcontroller
- Support USB reconfiguration/programming over magnet connector
- Support APA102 style LEDs.
Put 1 on PCB, then to connector
VCC,GND,clk,data

## Notes
On two different magnetic USB cables, of same format. 4 pins
5V at tip, GND at base towards cable. Same.
However the magnets were oriented the other direction. South/North

## 2 pin inline

2 pin magnetic pogo pins
Many different sizes. Pin distances from 2 to 4mm
14 mm total length
https://www.aliexpress.com/item/4001134405952.html
https://www.aliexpress.com/item/33009498882.html
https://www.cletk.com/connector/high-class-2-pin-magnetic-charging-cable-for-smart-watch
https://www.aliexpress.com/item/4001065386444.html
https://www.aliexpress.com/item/4000209947392.html
https://www.aliexpress.com/item/4001149140826.html
https://www.aliexpress.com/item/1005002013444317.html

## Rotary magnetic

About 7.5 to 8.5 mm diameter

https://www.aliexpress.com/item/1005002177757313.html
https://www.aliexpress.com/item/4001135270257.html
https://www.aliexpress.com/item/4000109101082.html
https://www.aliexpress.com/item/4000109004581.html

## Parts 

Diode Shottky SOD323
https://www.digikey.com/en/products/filter/diodes-rectifiers-single/280?s=N4IgjCBcpgbFoDGUBmBDANgZwKYBoQB7KAbRAGYBOAJgBZ4DaAGJuiRlsSiAXQIAcALlBABlQQCcAlgDsA5iAC%2BBSvGghkkdNnxFSIZk3IB2ABwg%2BIISPHT5SggFpqCDVEkBXXcUhkArCAqFgLCkCAOII4B6prauAQ%2BZC6W1mFKyiBqoFIAJiKOYEzsVqHhBACOggCeIoWBINX8OCJoWMiKikA

PMOS SOT-223
https://www.digikey.com/en/products/filter/transistors-fets-mosfets-single/278?s=N4IgjCBcoGwAwyqAxlAZgQwDYGcCmANCAPZQDaIAzABwCsYclIAukQA4AuUIAyhwE4BLAHYBzEAF8iMMACYkIVJEy5CJcuBi0YsuCCKzDYGAE59IWTQAsc87NoB2KzCYHqT2lfOmwn7ybAHRGkTWV9zahsrWgjHLXMGOGiHBLgk2mpUpOp5IkSraky8uAyTM2LaUIg8hhgHGJrPMISrBDhq8BtaSoTHOAdXcD66BJNKJJSDNOodO0ofYIsHeuMWdi5IXgERcSlwWQCFJRV8IlJIClbaSiDzK5vJkFb2kwankqt6u4-ltZBObh8IRiSREAC08mgiigAgArmpzhQ3mZWP8NiBJHtEFDBAATbhghgdAGbcwARw4AE9uAxzFS2HhuBgcKgJBIgA


LIR1620 / LIR1632
LIR2032
LIR2450
Rainpro @ Aliexpress

LED driver. Linear regulator, low-dropout

BCR430U

## JST SUR 0.8 mm pitch connector

SM04B-SRSS-TB(LF)(SN) 
https://www.digikey.no/product-detail/no/jst-sales-america-inc/SM04B-SRSS-TB-LF-SN/455-1804-6-ND/1963508

There are now SUR connectors from JST also.
They have 0.8 mm pitch, and 1 mm height

https://www.digikey.com/en/products/detail/jst-sales-america-inc/SM04B-SURS-TF-LF-SN/7230518
https://www.digikey.com/en/products/detail/jst-sales-america-inc/A04SUR04SUR32W102A/9947438

https://www.aliexpress.com/item/32835280612.html?spm=a2g0o.cart.0.0.44853c0032a3Bk&mp=1
https://www.aliexpress.com/item/32834920580.html?spm=a2g0o.cart.0.0.44853c0032a3Bk&mp=1
https://www.aliexpress.com/item/4001089049756.html?spm=a2g0o.cart.0.0.44853c0032a3Bk&mp=1
https://www.aliexpress.com/item/4001089049756.html?spm=a2g0o.cart.0.0.44853c0032a3Bk&mp=1

FPC connector
https://www.digikey.com/en/products/detail/te-connectivity-amp-connectors/1734839-5/1860461


BCR430U


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



