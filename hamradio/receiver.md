
## Sept 16

LC filter

Double tuned. For RF
https://73qrz.com/bandpass-calc


https://www.hackatronic.com/lc-filters-circuit-diagram-working-types-and-applications/

https://www.pa3cor.nl/uncategorized/1-transistor-cw-filter/

Advanced filters. Multiple Feedback
https://codingace.net/general/second_order_bandpass_filter.html

https://www.dxzone.com/catalog/Technical_Reference/Filters/

https://www.circuits-diy.com/simple-am-receiver-using-bc547-transistor/

https://electronics-diy.com/electronic_schematic.php?id=188


## Impedance matching

A bipolar or JFET transistor based will naturally have a high imput impedance.
Can be in 10k order.

A common choice is to design input to have 450 ohm.
Then one can use a 1:9 transformer.
The impedance transformer will also increase the voltage a lot.

In a JFET common source, can use 450 ohm resistor at gate.

## AM demodulation

Also called AM decoder or AM envelope detector.

- Diode detector.
- Infinite impedance detector

### Diode detector

Simplest mechanism.
Sensitivity limited by the forward voltage.
Lower forward voltage is better. Ex. Schottky Diode.
Biasing can be used 

Figure 4 - Improved Diode Detector.
Using adjustable bias on the diodes.
https://sound-au.com/articles/am-radio.htm

Suitable Schottky should be low capacitance. And low threshold.
Example BAT46.

### Infinite impedance detector

Using a triode type circuit as the rectifier.
Originall using vacum tubes.
Can be implemented with a JFET.
https://baltic-lab.com/2023/02/jfet-based-infinite-impedance-detector-for-am-demodulation/

Elliot Sound provides two designs.
Figure 5 - FET Based Infinite Impedance Detector and Figure 6 - Improved Infinite Impedance Detector.
Latter is adapted from a circuit in the ARRL Handbook.
https://sound-au.com/articles/am-radio.htm

Suitable JFET SMD? MMBFJ310
