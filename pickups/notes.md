
# Inductor guitar pickups

> Can one create custom guitar pickups
> without having to wind the coils
> by utilizing standard off-the-shelf inductors instead?

We want at least one inductor per string.
Kind of like a hexaphonic pickup.
But without it being a goal per-se of having individual string outputs.


## Design A: Passive

See: [scpu10](./hardware/scpu10/).

Using Tunable Pickup by TheScientificGuitarist as a known-good reference for decent sounding.
Target inductance of 100 mH. And target DC resistance of 4 ohms.

String distance is approx 10 mm. So limited to inductors with 8-9 mm diameter.

However due to off-the-shelf inductors being smaller physically, we cannot quite get there.

- RL622-103K-RC. 10 mH. 25 ohm. 
- RL622-103K-RC. 100 mH. 235 ohm.

Using a "inline humbucker" single coil design with 2 parts, each with 3 inductors in series.
Get 150 mH and 325 ohms with 100 mH inductors,
or 15 mH and 37.5 ohm with 10 mH inductors.

So around 1 order of magnitude off for both parameters. Maybe still worth a shot?

In the best case, the output level is just 10x too low.
Which can be compensated with higher gain.
In the not-so-good case, the changed parameters means that.

Other questions: Audio transformers only specify down to 300 Hz. Is there a low pass below that?
A bit high for a guitar, is it not?


## Design B: Active

When using active amplification, it becomes much easier to get the desired output level.

Disadvantage is needing power, and a bit more electronics.

Staus. NOT STARTED.

May need as much as 100x gain. So best with a two-stage opamp.
Can use dml10 design as starting point. Needs around 20x10mm board real estate

Possibly using SMD inductor instead of through-hole.
Reduces total height of pickup, which may let the neodym magnets can get into more effective range?
And assembly is easier/cheaper.
Candidate. Murata 22R686MC. 7.8 mm diameter. 7.5mm height. Up to 68 mH.


## References

Tunable Pickup by TheScientificGuitarist.
https://www.youtube.com/watch?v=9aojyjsl3MI&t=1s
Shows using neodym magnets underneath custom wound low-inductance coils. 250x turns. On top of a PCB.
Inline humbucker design. Good for reducing hum, in single coil package
The metal rods on top is great for making sure the signal is uniform across gap.
Shows how classic design gives a resonant low-pass filter. That is characteristic of the sound.
Which can be created actively instead of coming from the inherent properties of magnetic coils.

Estimating that Tunable Pickup has an inductance approx 20-60x less than a regular pickup.
Based on a typical number of windings being 5-15k, and this is only 250.
Assuming 4000 mH inductance of a typical coil, this gives an inductance of 73-200 mH.
Since there are many unknowns, lets just say it is probably closer to 100 mH than 10 mH.
The DC resistance is said to be 4 ohms.


Elliot on Sound
https://sound-au.com/articles/audio-xfmrs.htm
Discusses using a series capacitance to boost/extend bass response below 300 Hz


EMG81 Pickup Analysis
https://www.electrosmash.com/emg81

Differential amplifier. Single stage.
Differential gain of 5.5x
Coil is 5500-6000 turn. Which is still probably in the 1 Henry range.
Deliberately unbalances the differential inputs, to shift the resonant peaks from coils.

Bajaman make an DIY active preamp, with some modifications on the EMG-81 circuit.
https://www.freestompboxes.org/viewtopic.php?t=880&hilit=emg&start=20



Alegree: What's inside an active humbucker and how does it work?
https://www.youtube.com/watch?v=-GizpvRJ9uw
Explains the tone shaping done in classical active pickups.


LM4250 replacement.
https://www.talkbass.com/threads/g-l-mm-pre-ampers-fyi-replacement-lm4250s.1433436/#post-23991914
With 1.5MΩ on pin 8, the op amp has a GBW of 180KHz, slew rate of 0.1V/µs, and quiescent current of about 30µA

Only quite special thing here is the adjustable Iset. \
And that it is configured for very low power.

TL062 is 250 uA.
OPA2170 is a modern alternative?
TLV9102 also. TLV2170. 
GBW 1 Mhz might get limiting if needing a lot of gain though.

https://www.analog.com/en/resources/analog-dialogue/articles/techniques-to-avoid-instability-capacitive-loading.html
