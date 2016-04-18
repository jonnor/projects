
Experiments around the piezeoelectric effect,
both [sensors](https://en.wikipedia.org/wiki/Piezoelectric_sensor) and transducers.



## Piezo preamp

For a capacitive sensor like a piezo element, a [Charge amplifier](https://en.wikipedia.org/wiki/Charge_amplifier)
is better than a voltage or current amplifier.

Gain is `G = Cinput / Cfeedback`. It is neccesary to limit the DC amplification using.
And to correct for input bias causing DC offset on output, `R1 == R2`, where R1 is on the negative input connected to.

It may be desirable to add another (voltage) gain stage after the charge-amp, to maybe bring output up to line level.



Parts:

* Opamp: [TL062](http://www.ti.com/lit/ds/symlink/tl064.pdf), low power consumption
| [Farnell](http://no.farnell.com/webapp/wcs/stores/servlet/Search?catalogId=15001&langId=47&storeId=10169&sort=P_PRICE&st=tl062&showResults=true&aa=true&sf=722&pf=110153707)
* Feedback capacitor

Ideas:

* Put double pads on feedback capacitor slot, to allow modifying/testing alternate values
* Can one make a "socket" for SMD capacitors, that allows switching them out?

References:

* [DIYAudio: Guitar charge-amp preamp](http://www.diyaudio.com/forums/instruments-amps/203183-charge-amplifier-guitar-preamp-questions.html), with schematics and some good commentary
* [Electric violin charge-amp preamp](http://www.endolith.com/wordpress/2007/10/13/electric-violin/)
* [Texas Instruments: Signal Conditioning of Piezoelectic Sensors](http://www.ti.com/lit/an/sloa033a/sloa033a.pdf)
* [DigiKey: Fundamentals of Piezoelectric Shock and Vibration Sensors](http://www.digikey.com/en/articles/techzone/2011/dec/fundamentals-of-piezoelectric-shock-and-vibration-sensors)

### Uses

Music

* Acoustic or electric guitar pickups
* Electric violin pickups
* Piano contact mic
* Electronic drum velocity sensitive trigger
* Pickup for spring reverb

Digital fabrication

* Vibration sensing of CNC spindles, for auto-calibration
* Touch-probe measurements for 3d-printer using differences in free-running and touching resonance


## Piezo driver

* [Speakers](https://en.wikipedia.org/wiki/Piezoelectric_speaker) and buzzers
* Ultrasound transducer vaperizators, for aeroponics
* Micro-pumps and droplet valves

## Synthetization

There are many recipies to make Rochelle salts, which are piezo-electric.

* http://makezine.com/2008/07/31/how-to-make-piezo-crystal/
* http://www.seawhy.com/xlroch.html 
* https://www.youtube.com/watch?v=K3G2QM5a-9U
* [Very detailed](http://www.extremenxt.com/blog/?page_id=77)

Rochell salts are [Potassium sodium tartrate](https://en.wikipedia.org/wiki/Potassium_sodium_tartrate),
which can be purchased directly [Amazon](http://www.amazon.com/s/ref=nb_sb_noss?url=search-alias%3Daps&field-keywords=Potassium+sodium+tartrate).

It can also be made from two fairly common ingredients

* [Potassium bitartrate](https://en.wikipedia.org/wiki/Potassium_bitartrate) "Cream of tartar"
* [Sodium carbonate](https://en.wikipedia.org/wiki/Sodium_carbonate) "soda ash" or "washing soda",
which can be make easily from sodium bicarbonate.

This should be usable for simple piezo sensors, like for triggering samples/drums.

Some cool things could be possible when synthesizing the piezo elements / crystals oneself.
For instance, can possibly create a shape that is needed / desired,
both for astetic effects and to make particular objects. Say like a speaker driver.

One could possibly embed electrical wire, solving the issue of 
