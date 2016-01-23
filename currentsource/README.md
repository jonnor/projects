# Linear constant-current source

Useful for driving LEDs, laser diodes, or performing electrolysis.
Each module can deliver up to 2 amps of current, but can also be parallel coupled to share a larger load.

Designed for easy reproduction in a fablab or makerspace, with a CNC-millable single-layer PCB and no special components.
The board has 0.1" DIP style connectors, and can be used directly in a breadboard, or easily used as a 

Can be digitally controlled using PWM (ex using a microcontroller/Arduino),
both setting target/max current and performing high-frequency pulsing.
Or the target current can be set using any other voltage reference, like a zener diode.

Since this is a linear, good cooling is required. Power dissipated in the transistor is 

## Status
In development

## TODO

* Complete board layout
* Verify module functionality, including Iset and PWM from microcontroller
* Verify current sharing using multiple modules
* Test with laser diode
* Test with a power LED

## References

Calculators

* [PWM RC filter](http://sim.okawa-denshi.jp/en/PWMtool.php).
For 300 Hz PWM (Arduino `digitalWrite` default), need on order of `100k/1uF`, giving `Fc=1.6Hz, Uripple>0.05V, Tsettle<0.25sec`

Parts

* [Farnell: Current sense resistors](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&categoryId=700000050528&sort=P_PRICE&pageSize=25&showResults=true&aa=true&pf=110005192,110005252,110018072,110030112,110035095,110056631,110057315,110071516,110081932,110083417,110103671,110112375&min=110071516)
* [Farnell: Power MOSFET]()
