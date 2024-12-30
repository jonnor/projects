
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




# Background research

### Differentiable IIR filters 

DIFFERENTIABLE IIR FILTERS FOR MACHINE LEARNING APPLICATIONS
Boris Kuznetsov, Julian D. Parker and Fabián Esqueda
Native Instruments GmbH
2020
Notes the equivalence between RNN and IIR.

- SVF. State-Variable Filter
- TDF-II. Transposed Direct Form-II
- LSS. Linear state-space filter
- FIR. Convolution

Pytorch implementation here, including runnable example code
https://github.com/boris-kuz/differentiable_iir_filters

Wiener-Hammerstein model

- LTI filter
- non-linearity
- LTI filter

Used to model guitar amplifiers, audio distortion and tube-based preamps.
Has 4 references for this.

Creating the Wiener-Hammerstein using differentialbe IIRs for the LTI,
and a multi-layer-perceptron for the non-linearity.

The MLP structure.
4 densely-connected layers, 2 being hidden layers of width 20.
tanh activation function, after every hidden layer

Used to model a Boss DS-1 guitar distortion pedal.
All knobs on the pedal were set to 50% of their value.
Training was conducted by using a test signal consisting of a 90-second passage of electric guitar playing.
During training, using sequences of 2048 samples.
Uses MSE as the loss.
Claims accurate results.
Says they have some listening examples.

IDEA: Improve by using a more psycoacoustically relevant loss function?

### Virtual Analog Modeling of Guitar Amplifiers with Wiener-Hammerstein Models
Did listening tests.
On average no model was rated worse than ‘minor differences’.

Uses a psycoacoustically inspired cost function.
Based on STFT residuals. With some post-processing to cover frequency spectrum of guitar.


### Kemper

Is said to use a kind of Wiener-Hammerstein model.
With his own identification method. 

C. Kemper, “Musical instrument with acoustic transducer,”
US Patent: US20080134867 A1, July 2008.

## Others working on related

https://www.reddit.com/r/DSP/comments/10cxcpp/parameter_optimization_for_a_guitar_amp_sim/
Looking to implement Wiener-Hammerstein on Teensy

## Expression pedal


https://missionengineering.com/understanding-expression-pedals/
2*20k ohms
Use ADC to read it. Support a decent range.

## Distortion stage

Op-amp.
Diode-based.
Both hard-clipping and soft-clipping option.
Maybe possibility to change the diodes easily
https://generalguitargadgets.com/how-to-build-it/technical-help/articles/design-distortion/

https://www.guitarpedalx.com/news/news/a-brief-hobbyist-primer-on-clipping-diodes

Having a resistor divider for the hard-clipping circuit allows to softer a bit.
https://www.premierguitar.com/diode-stew

http://www.muzique.com/lab/sat2.htm
Shows many ways of modifying diode clippers, in adjutable ways.
Bottom is interesting. Shows a clipping mixer.
But supporing a diode pair also in the upper is the best, for full flexibility.

## Bypass

True bypass. Using relay.

Monostable is the typical.
Will draw some 10-100 mA however.
Not great for battery power. But probably acceptable.

More important is that there is no popping when switching.
https://www.coda-effects.com/2016/08/relay-bypass-with-anti-pop-system.html?m=0
Uses a small signal solid state relay "photoFET".
Pull down input signal actively, before switching over.

https://www.digikey.no/no/products/filter/faststoffreleer-solid-state-relays-ssr/183?s=N4IgjCBcoLQExVAYygFwE4FcCmAaEA9lANogCsI%2BAnCALoC%2B9%2BAbIiAJYAmUIMYADBHwAHVD0ogAjqgCePARNnDsPAIYBnFIyA

## Opamps

NE5532 is just 25 cents these days.
TL072 is 10 cents. Generally not worth saving on.

OPA2134 is 3 USD. Same with LM4562.

## User interface

- TFT/OLED screen.
- Rotary encoder. Minimum 1. Maybe a few more over time
- Audio input. 1/4" jack
- Audio output. 1/4" jack
- Foot switch input. 1/4" jack. Minimum 1. Maybe 2. For bypass/mode
- Expression pedal input. 1/4" jack
- Power input. DC barrel jack. 9V. Reverse polarity protection

Debug/setup

- USB to microcontroller

Bonus

- MIDI input. As option for controlling from somewhere else



## Controller

- I2C bus potmeters. 2 pins
- Display. Backlight (PWM), and I2C. Pins: 1 (if using shared bus). 3 if using dedicated I2C bus
- Encoder. Pushbutton, directions. 3 pins


## Tools

Opamp buffer with guitar jacks
https://www.pcbway.com/project/shareproject/Op_Amp_Buffer_with_In_Out_Guitar_Jacks_febae3f0.html
! no reverse polarity protection
Gain in and out.
Nice for prototyping

## Filters

Graphic or parametric equalizer.
Integrated circuits with analog signal path, and digital control.

https://octopart.com/search?q=graphic+equalizer&currency=USD&specs=0

### State variable

Most flexible basis for parametric EQ
https://sound-au.com/articles/state-variable.htm
4 opamp version. Plus 1 opamp per stage for summation.
Provides high/low/bandpass and notch
Multiple ones put into stages.

Based on APPLICATION NOTE 1762 - A Beginner's Guide to Filter Topologies (Maxim Integrated).
https://www.analog.com/en/resources/technical-articles/a-beginners-guide-to-filter-topologies.html

Dual-gang pot for frequency. Else single for Q and cut/boost. 4 pots total.

Can we get in a 4-way selector into each stage?
Analog multiplexer. Integrated circuit?

- DG4052E. Recommended on audio forums, oer old 4052? 1 USD.
- TPW4054. Mentions audio. 12V
- MAX4524L. TQFN10. +2V to +12V
- MAX4518. Audio grade. SO16. 4 USD.

Linearity, the characteristic to look for in the datasheet is "On resistance flatness" (0.2 Ω for DG451)

I2C GPIO expander? To control the mux
https://www.digikey.com/en/products/filter/interface/i-o-expanders/749?s=N4IgjCBcpgrALFUBjKAzAhgGwM4FMAaEAeygG0QBmWANgE4wAOEAXSIAcAXKEAZU4BOASwB2AcxABfInADsSEKkiZchEuRAAmAAyUwNeUU2Mw8MNpBGTsbYa3XzrDt0h9BoidJABaTQqWCAK5qpJAUsJYgdKySXjQKQgAmPN7mEM48kQCOnACePI5Eeex4PBg4qLFAA
Nah, just expose the pads directly.


High/low pass should maybe be separate, like a Bauxall style.
Then maybe 3 parametric bands would be enough.
But ideally want 5 ot maybe 6.

Examples of commercial parametric equalizer.

- Ibanez PTEQ Pentatone 5-band

Module.

- Audio In
- Audio Out
- VCC
- Gnd
- SDA
- SCL
- SW1
- SW2

http://www.geofex.com/Article_Folders/EQs/paramet.htm
Older design.

### Contant Q parametric eq

https://sound-au.com/project150.htm
Version with 16 dB cut/boost and Q of 2.
More fine tuned than a octave-band graphical (Q of 1.4).
Uses only 1 opamps per stage.

### Discrete design

Elliot Sound Constant-Q graphic EQ
https://sound-au.com/project75.htm
Easily choose the amount of filters
Suggets NE5532 / OPA2134
All potmeters are 100 k.

2-band parametric equalizer. Used in bass amplifier
https://sound-au.com/project152-1.htm


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
