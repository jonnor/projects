# Linear constant-current source

Useful for driving LEDs, laser diodes, or other circuits which demand a current source
(and not a voltage source)- like when performing electroplating, electroetching or electroforming.

## Features

Designed for easy reproduction in a fablab or makerspace, with a CNC-millable single-layer PCB and no special components.
The board has 0.1" single-inline header-style connectors, and can be used directly in a breadboard, used as a daughterboard, or used standalone with wires.

Can be digitally controlled using PWM (ex using a microcontroller/Arduino),
both setting target/max current and performing high-frequency pulsing.
Or the target current can be set using any other voltage reference, like a zener diode.

Provided there is adequate cooling, each module can deliver up to 5 amps of current.
As this is a linear regulator, power dissipated as heat in the output is `Pd = (Vin-Vout)*Iout`.
You can wire multiple modules up in parallel to share the load, and the SIL connector layout makes this easy.

Compact size (20x40mm), including two M3 mounting holes (1.5" spacing).

## Status
In development

## Done

* Mill and assemble first board. Basic functionality verification, including `Iset` and `PWM` from microcontroller.
MOSFET pinout was wrong, otherwise worked OK. This has now been rectified.

## TODO

0.1

* Verify current sharing using multiple modules
* Test with laser diode
* Test with a power LED
* Verify working with 3.3v uC. Needs suitable opamp and MOSFET
* Make 1 or 2 testing jigs
* Make production run of 5 boards

Related

* Order 1206/1210 capacitors. Big enough to place traces under, unlike 0805.
* Order 0 ohm resistors, for bridges (alternative to vias). 1206.
[Farnell](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=44&storeId=10151&categoryId=700000005450&pageSize=25&showResults=true&pf=110071175,111629309,111629358,111629382)
* Order SMD 2.54mm headers. [Farnell](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000005017&sort=P_PRICE&pageSize=25&showResults=true&pf=110063161,110178988,110195024,111981269)
* Maybe add some PNP compliments (BC856)

0.2

* Use KiCAD instead of Fritzing
* Use one of opamps as a 10x amplifier of Rsense signal, instead of attenuating Iset input.
Maximises use the finite DAC precision, reduces Iset ripple, and easier to test/debug.
* Expose the amplified `Ifeedback` signal, for detecting when failing to regulate
* Arduino library and MicroFlo component for controlling

## BOM

* SO8 opamp (LM358 etc)
* D2PAK transitor
* 2512 current sense resistor
* 1206 1uF filtering capacitors
* 1206 resistors

## Application boards

Simple power LED

* LED mounted on back of module
* Zener/diodes voltage reference
* Trimpot
* micro-USB power connector

Laserdiode

* PWM and current control via microcontroller

Electrolysis

* 4x modules with active heatsink(s)
* Up to 20 amp current?

Functional tester

* Couple of switchable loads
* Measure current by measuring voltage over these known loads
* Arduino as I/O extender for computer running test over USB

## LED lighting

Big armatures by having multiple LEDs in a chain on a single current source.
With a 24volt powersupply should be able to put 6 LEDs (maaybe 7). And 3 on 12V supply.
Or one single on 5V/USB.

Something I'd actually want/need is a lamp for bookreading, both next to bed and in sofa.

### Construction ideas

Tincans can possibly make a nice body

Aluminum plate could make for good armature basis, acts both as a heatsink and reflector.
Can be bent into many different shapes. May also be able to use it as conductor.
Sandblasted or opal-colored acrylic could be used as diffusor.

For on-the-cheap, may be possible to use cardboard plus aluminum foil.
Layering paper and al-foil one could also make the traces for connecting the LEDs.
White print paper, or baking-paper could be used for diffusors.
Possibly interesting for fast experimentation with shapes, with hand-cut or laser-cut cardboard.

If one could construct a socket for the LED, which would take conductors in-out, and press
them against the connectors on the LED, could avoid soldering. Possibly 3d-printed. Examples
[1](http://www.thingiverse.com/thing:897957) [2](http://www.thingiverse.com/thing:170562)

Could maybe make a multi-conductor tape by cutting up foil in strips, applied next to eachother
onto a (possibly double sided) tape. A device with cutters, dividers and rollers could do this semi-automatically.

Stained glass soldered together also looks quite epic.
[instruction video](https://www.youtube.com/watch?v=EGx90bUJCPc)
[2](https://www.youtube.com/watch?v=CvckB6ToyQU).
Can also be used to construct 3d-shapes, like [this terrarium](https://www.youtube.com/watch?v=JUo5q0rKOn8)

### Controls

Would want at minimum physical controls, to set the current/lightlevel (potmeter/rotary encoder etc).
and to turn on and off (toggle switch). Perhaps a tiny not-brigth LED for locating the light in the dark,
and indicating when thing is powered but turned off/down. This could be the voltage-reference also?

If making mood-lights, candle-emulation flickering migth be interesting.

Could possibly make Phillips Hue compatible. Resources:

* [Instructables: RGB moodlamp syncs with Hue](http://www.instructables.com/id/High-Power-RGB-LED-Moodlamp-which-syncs-with-Phili/)
* [Control Hue from Arduino](http://www.makeuseof.com/tag/control-philips-hue-lights-arduino-and-motion-sensor/)
* [ESP8266HueEmulator](https://github.com/probonopd/ESP8266HueEmulator)
* [Hue bridge in Python](https://github.com/mjg59/ulfire)


### Parts

* ~ 1W/100lumen/350mA looks to be around 10 NOK/piece.
[Farnell](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000006148&sort=P_PRICE&pageSize=25&showResults=true&aa=true&sf=722&pf=110123293,110123306,110123341,110123356,110133845,110133852,110133859,110133881,110133882,110133887,110133892,110133897,110133904,110133914,110144659,110144664,110144668,110144714,110155291,110155292,110155296,110155302,110155310,110155374,110155388,110165919,110165952,110165956,110165957,110182255,110184700,110186475,110193711,110195065,110197226,110201762,110418066,110418258,110433218&min=110165956&max=110433218,110133881)
* 3W/200lm/750mA around 5/NOK per watt.
[AdaFruit](https://www.sparkfun.com/products/13104)

### Thermal design

* [Elliot Sound: Primer on heatsinks](http://sound.westhost.com/heatsinks.htm)
* [Heat sink calculator](http://www.daycounter.com/Calculators/Heat-Sink-Temperature-Calculator.phtml)
* [How to design flat-plate heatsink](http://www.heatsinkcalculator.com/blog/how-to-design-a-flat-plate-heat-sink/)
* [Calculator: Thermal resistance in solid](http://mustcalculate.com/electronics/thermalresistance.php?mat=al&w=100&wu=mm&l=100&lu=mm&t=0.01&tu=mm)
* [Calculator: Natural Convection on Isothermal Vertical Plate](http://www.thermal-wizard.com/tmwiz/convect/natural/vp-isot/vp-isot.htm)
* [Calculator: Natural convection on isothermal horizontal plate](http://www.thermal-wizard.com/tmwiz/convect/natural/hup-isot/hup-isot.htm)

## Ideas

### Solder and paste mask using laser

For producing PCB with solder mask, (and SMD solder/paste application)

* Mill the PCB traces
* Apply a thin heat-resistant tape, to become soldermask (Kapton)
* Apply a thicker tape, used for solderpaste deposit (Ductape)
* Use lasercutter to selectively open holes in tape
* Squigee/scrape on solderpaste
* Remove the upper tape, leaving the lower tape in place
* Place components -> solder with hotair or oven

Initial testing done, February 23, 2015

* Heat-resistant PET cut very nicely on the laser. Using raster engrave to vaporize whole areas.
Kapton was a bit nastier, leaving a bit of dark burnt material behind. Maybe settings tweaking can improve it.
* 2 passes needed for clean(ish) surface afterwards. It *may* be that cleaning is needed for good solder.
* Used 20%, 0.1mm linewidth, 200mm/s on PET, 40% on Kapton
* Heat-resistive PET tape was spectacular fail: melted and shrank in solderoven, leaving a horrible mess.
* Kapton tape worked OK in oven, no melting.
* Kapton/PET tapes way too thin for applying solderpaste.
Need separate layer of thicker tape. Ducttape tested, seems suitable thickness.
* The solder paste tape-mask worked also when separate and manually aligned afterwards.

Next steps

* Do complete test one PCB with CNC-milled traces
* Document the process with step-by-step instruction with images
* Make a short video walkthrough
* Research more safety of lasering reflective materials
* Make some jig for having good registration between CNC mill and lasercutter.
[fellesverkstedet/tool-connections](https://github.com/fellesverkstedet/tool-connections) good basis.
* Try Mylar as alternative to Kapton (source: Jensa)

Might want to take extra care add test-probe pads to circuits made in this manner, cause
otherwise they will be underneath the soldermask.

### Automated testing

Ideally want to use the same testcases to drive both

* pre-build simulation verification
* acceptance test of completed board/system

Could be specified using an FBP graph and fbp-spec (data-driven). NoFlo and MicroFlo could be useful here.
The data-centered approach is nice because it reflects how electronics datasheets are usually setup.
Alternatively, could perhaps use Gherkin-style (behavior driven) prose.
For sure one would want to be able to generate documentation, of which tests are ran
and what their outcome is. Primarily for datasheet 'what can it do',
and secondarily as a QA report for a particular device.

A Arduino/microcontroller based setup with some standardized extensions might be able to test most systems.
One could then adapt/add a application-specific test circuit to this, for instance via another shield.
This should then have connectors that directly interface with the device-under-test,
so that it can be plugged in, tests ran, -> done. For acceptance test it would end there.
When debugging it may be useful to be able to stimulate the tests again and again,
and observe/capture data (possibly using additional instruments) of other testpoints.

When manufacturing is done by another party, one should be able to send such a test setup to them,
so that verification can happen on-site, before shipping. And be used to improve process / yield rates.

Best practice would be that all points needed to test and verify function and perfomance
is available from the outside, via the normal module connectors 'black box testing'.
Having dedicated testing connectors 'grey box testing'.

### Currentsource v1 tests

System has

    Inputs:
        Iset
        PWM
    Outputs:
        Iout. Where a variable load Rl can be connected, which current Iload flows through
        Ifeedback. Voltage reflecting Iout
    Two power sources: VCC and VPWR

    NC: not connected

Testcases (VCC=3.3 unless otherwise noted)
    
    # basic regulation,
    # should set current to Iset, and no failure signalled
    Iset=1V, PWM=NC, VPWR=5V, Rl=1ohm
    => Iload=1A, Ifeedback == Iset == 1V

    # insufficient voltage for load,
    # should do its best and signal failure
    Iset=1V, PWM=NC, VPWR=5V, Rl=10ohm
    => Iload=0.2A, Ifeedback less than Iset

    # pwm connected but not used,
    # current is what Iset

    # pwm modulation
    # Iload varies between 0 and Iset

    # two modules connected together with no PWM,
    # should share current evenly, and double in load
    
    # two modules connected together with same PWM,
    # should share current evenly, and double in load


### References

Simulation tools, open source

* [Tutorial: Simulating KiCAD schematics with ngSPICE](http://stffrdhrn.github.io/electronics/2015/04/28/simulating_kicad_schematics_in_spice.html).
[demo repo](https://github.com/stffrdhrn/kicad-spice-demo)
* [Quick Guide: KiCAD SPICE simulation](http://mithatkonar.com/wiki/doku.php/kicad/kicad_spice_quick_guide)
* [gnucap](http://www.gnucap.org/dokuwiki/doku.php?id=gnucap:start) "modern post-spice circuit simulator"
* [gnucap emscripten](https://github.com/logical/Gnucap-Emscripten), compiled to JavaScript. Proof-of-concept
* [ngscipe emscripten](https://github.com/concord-consortium/build-ngspice-js), compiled to JavaScript. Proof-of-concept

Testing hardware

* TODO: figure out what exists, both Arduino-based and specialized DAQ/testing hardware

## References

Calculators

* [PWM RC filter](http://sim.okawa-denshi.jp/en/PWMtool.php).
For 300 Hz PWM (Arduino `digitalWrite` default), need on order of `100k/1uF`, giving `Fc=1.6Hz, Uripple>0.05V, Tsettle<0.25sec`

Parts

* [Farnell: S08 opamps](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000004295&sort=P_PRICE&pageSize=25&showResults=true&pf=110052822,110075784,110153707,111439590,111439591)
* [Farnell: Current sense resistors](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000050528&sort=P_PRICE&pageSize=25&showResults=true&aa=true&pf=110005192,110005252,110018072,110030112,110035095,110056631,110057315,110071516,110081932,110083417,110103671,110112375&min=110071516)
* [Farnell: Power MOSFET TO220](http://uk.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=44&storeId=10151&categoryId=700000043507&sort=P_PRICE&st=mosfet&pageSize=25&showResults=true&aa=true&pf=110029860,110126877,110126879,110126886,110126931,110126938,110126950,110127029,110127508,110137512,110137513,110148318,110148320,110148322,110148324,110148364,110148372,110148418,110148808,110158844,110158845,110158855,110169483,110169484,110169489,110169512,110169536,110169579,110169624,110174022,110180370,110184753,110187489,110187528,110189467,110190503,110196584,110199950,110203560,110204181,111489640,111489641,111997170&min=110126877)
* [Farnell: Power MOSFET D2PAK](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000043507&sort=P_PRICE&st=TO-263&pageSize=25&showResults=true&aa=true&pf=110007507,110007518,110007519,110007533,110007539,110007545,110007548,110007553,110007561,110007565,110007578,110007581,110007585,110007596,110007598,110007622,110007624,110007626,110007632,110007639,110007642,110007658,110008044,110022458,110022462,110022466,110022474,110022479,110022488,110022502,110022512,110022541,110022564,110022566,110022567,110022568,110022578,110022874,110022934,110022942,110022981,110022985,110029860,110037381,110037389,110037394,110037403,110037430,110037433,110037442,110037464,110037469,110037471,110037476,110037498,110037508,110037529,110037530,110037539,110037543,110037548,110037875,110037983,110042613,110046420,110046957,110048153,110049699,110050383,110052390,110053053,110053986,110054480,110054664,110054775,110056057,110056386,110056949,110059363,110059575,110061128,110063195,110065847,110066405,110068302,110068488,110068571,110068614,110069541,110069895,110072650,110073084,110073210,110074963,110075747,110076804,110076853,110077367,110078553,110078659,110078671,110078828,110079346,110080754,110081438,110081805,110082056,110083858,110083923,110084326,110084521,110085559,110086600,110086684,110086975,110087589,110087915,110088383,110089430,110089730,110090476,110090809,110092103,110092244,110092768,110093363,110093446,110093522,110093557,110094890,110095521,110095928,110096195,110097020,110099720,110102046,110104615,110107838,110108215,110109136,110109642,110111423,110112864,110113287,110113669,110116270,110116401,110117335,110117787,110158844,110302329,110325262,110451461,110451578,110453114,110453209,110453402,110453404,110453490,110453491,110453581,110453582,110453668,110453751,110453752,111229742,111229800,111229823,111229838,111229909,111229966,111230005,111230012,111230022,111270354,111332330,111334918&max=110007518)
* [Farnell: ~1uF electrolyt capacitor](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000005423&sort=P_PRICE&pageSize=25&showResults=true&sf=502,722&pf=110000001,110029771,110055165,110057658,110059735,110116694,110119861,110124836,110129851,110130340,110130369,110141064,110141066,110141074,110141096,110141101,110141104,110141112,110141155,110151906,110183885,110195220,110200287,110202689,110202702,110203983,111439590,111854956,111854958&min=110029771,110130369&max=110057658)
* [Farnell: 1uF ceramic capacitor](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000005423&sort=P_PRICE&pageSize=25&showResults=true&aa=true&sf=502,722&pf=110000001,110029771,110055165,110057658,110059735,110116694,110119861,110124836,110129851,110130340,110130369,110141064,110141066,110141074,110141096,110141101,110141104,110141112,110141155,110151906,110183885,110195220,110200287,110202689,110202702,110203983,111439590,111854952,111854956,111854958&min=110029771,110130369&max=110057658)
* [Farnell: SOT-23 NPN transistor](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000004650&sort=P_PRICE&st=sot-23&pageSize=25&showResults=true&aa=true&sf=502,722&pf=110007698,110007702,110007742,110022626,110022627,110022629,110022654,110029860,110037580,110037581,110037598,110037599,110048867,110067889,110082473,110083316,110090637,110108049,110115116,110126933,110126969,110126992,110126995,110127003,110148362,110148434,110148436,110148439,110148441,110158858,110158899,110158968,110169515,110169599,110172521,110177947,110181557,110183000,110184539,110185777,110189047,110192807,110194959,110195841,110196287,110198727,110199149,110201688,110203007,110203830,110204108,110231779,110286384&min=110082473,110158858)

## Related projects

* [Electromotors](../brushless). Has some similar needs, but more complex. May eventually superseed this project.
