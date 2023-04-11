
## Concept

Universal distortion effect.
Analog signal path, with digital control.

### Signal path

Pre-gain
|  Splitter
|  Pre. filter EQ
|  Non-linearity
|  Post. filter EQ
|  Post-gain
Dry/wet balancer

## Questions

- What kind of range is needed to express the frequency responses in typical amps (and cabinets)?
Can it be done with a graphic EQ?
Or should one have parametric EQ?

Could look at https://github.com/jatalahd/tsc for the tone stacks

## Filters

Graphic or parametric equalizer.
Integrated circuits with analog signal path, and digital control.

https://octopart.com/search?q=graphic+equalizer&currency=USD&specs=0

### Discrete design

Elliot Sound Constant-Q graphic EQ
https://sound-au.com/project75.htm
Easily choose the amount of filters

Suggets NE5532 / OPA2134

All potmeters are 100 k

### LC7527

- 7-band graphic equalizers
- Each band operates in ±2 dB steps.
- Each band has a maximum boost of +12 dB and a
maximum cut of –12 dB for a total of 13 settings.
- ! Independent left and right channel operation
- Serial data input supports CCB format communications

4 USD per each

### TEA6360

- Stereo
- 5-band
- Centre frequency, bandwidth and maximum boost/cut defined by external components
- Choise for variable or constant Q-factor
- I2C bus control

15 USD

### TDA7317

- VOLUME CONTROL IN 0.375dB STEP
- FIVE BANDS STEREO GRAPHIC EQUALIZER CENTER FREQUENCY, BANDWIDTH, MAX BOOST/CUT DEFINED BY EXTERNAL COMPONENTS
- ±14dB CUT/BOOST CONTROL IN 2dB/STEP
- Stereo

1 to 15 USD

Circuits
https://electro-dan.co.uk/Electronics/TDA7317.aspx

### LA7522

- 7 bands
- 13 positions, 2db/step
- +- 12 dB
- Serial data control, 2 lines
- Stereo

Not available?

### LMC835 

- Stereo
- 7 bands
- +-12 dB or +-6 dB range 
-  25 steps each
- 3 digital input pins to control

Used with external resonator circuits.

!!! Requires external opamp, capacitor, resistor network. PER BAND

2-10 USD per

### M61528FP

- 3 bands equalizer with SCF
- 4 independent fixed equalizer controls
- +8dB to –8dB / 0.5dB step
- Adjustable Q factor

### PT2313

- PT2313 is a pin drop replacement for TDA7313


### TDA7439DS

3 band tone controlAudio processor

### LM1036

- DC controlled
- tone (bass/treble)
- volume and balance


### LC75341
LC75341M

- volume, balance
- a 2- band equalizer
- input switching functions
- controlled from serially transferred data.


### M5243AFP09


## TM2313

TM2313 is a three-pair input four-channel output digital control audio processing chip. 
volume, bass, treble, channel equalization, pre/post attenuation, and loudness processing
All functions are driven and realized by PC bus programming.
SOP28/DIP28 package

### KA2223

- analog control. 100k pots
- +- 12 dB

5 bands
