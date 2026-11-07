
# Antennas

On VHF and UHF, size is rarely a concern.

On HF, from 10 to 80 meter bands, size can be a practical challenge.
Conventionals antennas only effective down to 1/4 wavelength.

With loading one can achieve an antenna that is electrically longer.
This is highly beneficial for the longer HF bands.

## Common antenna designs

- Dipole. Center fed design. Naturally around 50 ohm unbalanced.
- Inverted V dipole. Center mast highest. Sides can be wire.
- V-shape dipole
- Yagi. Directional antenna using reflectors. Often with a dipole driven element.
- Folded dipole. More compact by. Higher feed impedance, 73-300 ohm
- Flowerpot. Aka T2LT. Uses RF choke. Can be made with just coax.
- Quarter wave vertical.
- Quarter Wave ground-plane antenna. Vertical monopole with 4 radials pointing slightly downwards
- End-fed half-wave (EFHW). High impedance, requires 1:9 to 1:49 impedance transformer.
- End-Fed Long Wire (EFLW). Non-resonant. Can be used on multiple bands.
- Delta Loop. Triangular full-wavelength loop.
- Quadrifilar Helix antenna (QFH). Used for sattelite comms on VHF/UFH. Top feedpoint. Circular polarization.
- Moxon. Directional antenna from a dipole and a reflector, connected via insulators
- Magnetic loop.

## Impedance matching

Critical for transmission.
Poor impedance matching will cause reflected energy back into transmitter.
Reduces efficiency of transmitted power.
May destroy the transmitter.

## Jungle antenna

A portable 1/4 wave ground plane, made from wires and sticks.

## Turnstile antenna

Aka crossed-dipole antenna.

Circular polarization.
Omnidirectional.

Made by crossing two half-wave dipole elements at 90-degree angles,
and connecting them with a coaxial phasing harness to achieve circular polarization.

https://alicja.space/blog/how-to-build-turnstile-antenna
For 435 Mhz / 70 cm.
Practical build using 3d-printed parts.
! need 75 ohm cable stub
Ex RG59
https://www.kjell.com/no/sok?q=RG59&search=true

4mm tubes
https://www.elefun.no/vare-27547/materialer-metall-ror-ks-aluminiumsror-4mm-3stk

How To Build A MILSAT SATCOM Turnstile Antenna 
https://www.youtube.com/watch?v=Xdc7l0O5fYo&t=57s
! directional, using reflector.
Used to communicate with geostationary sattelites.
Using tape measure as elements. 3d-printed parts.
! need short 75 ohm stub


## Quadrifilar Helix or Quadrifilar Helicoidal antenna (QFH)

Omnidirectional.
Circular polarization.
Used for LEO sattelite radio.

146 MHz QFH Antenna for Amateur Radio Satellites
https://www.youtube.com/watch?v=EgY1MHaQ_us

3d-printed parts used to connect a central mast of PVC tubing,
and glassfiber rods going out.
Copper wire. Twisted entire thing after copper wire is mounted.

## Eggbeater antenna

Omnidirectional.
Circular polarization.
Used for LEO sattelite radio.

Has some lobes in the radiation pattern, but workable.
Also a null at the top, reducing gain right upwards.
Can have 4-6 dB gain outwards.

Original eggbeater had circular shaped elements.

k5oe Eggbeater II has square shaped elements.
Gives a much better reception at low-angles (closer to horizon).
Tradeoff is lower gain upwards.
http://wb5rmg.somenet.net/k5oe/Eggbeater_2.html
Used #10 gauge - 2.5 mm diameter copper

https://rz01.org/70cm-eggbeater-antenna/
Square-ish wire coils. Seems rather simple to build.

## Magnetic loop

Magnetic loop is narrow-band antenna that is magnetic-field dominant.
Main coupling mechanism is through the H-field, and it exhibits significant rejection of electric-field noise sources, particularly those in the near field.

The loop acts like a magnetic dipole.
The field strength near the loop is tied to the circulating current, which depends on the loop’s inductance and the tuning capacitor.

Can use multiple turns to increase inductance.

Radiation resistance is the part of the loop’s resistance that actually turns power into radio waves. For small loops (perimeter much less than a wavelength), radiation resistance is really low—usually under 1 ohm.
That means that low resistivity is critical to be effective at transmitting.


Figure 8 directivity pattern. Strong nulls at the side.
Can be used to cancel particular RF noise sources.

Narrow bandwidth and E-field rejection make it have excellent SNR.
important in locations with a lot of RF noise.
Which is common in many apartments/houses.

Want narrow bandwidth (high Q) at resonance.
For any specific frequency and magnetic loop antenna, its Q is proportional to its radiation efficiency.
Need a tuning capacitor. Variable is highly beneficial.
Need a VNA to check/tune it.

Circular configurations common.

Efficiency improves with higher cross section of the radiating elements.
Often built with copper tubing.
Quick and dirty version can be made with just coax cable.
Most designs do not pack small?

Magnetic loop antennas are often mounted on a tripod.

Popular variants

- Möbius loop
Made with

- YouLoop
Constructed from three semi-rigid coax cables.
Portable, can fold down into a smaller loop easily.
https://airspy.com/youloop/
Passive antenna. But would benefit from a VNA near the antenna.
For RTL-SDR should use AGC for low-signal.

## On the ground loop

## Active antennas

Contains active components integrated into the antenna design.
Most commonly a Low Noise Amplifier.

Popular active antennas

- Active magnetic loop
- Active mini whip

## PA0RDT active mini whip
RX only antenna for 10kHz-30Mhz listening.
Super small! Just 15 cm tall antenna element.

Antenna is built on a PCB.
Also uses simple cricuit consisting of one JFET and one bipolar transistor.
Using a Bias-T type power-feed unit to inject 12v.



## Projects

## Directional antenna for LoRa

Goal. Establish reliable connection from home to MeshCore.
Would be nice to enclose the antenna so it looks less odd.
Flag-style.
! should measure impedance and resonance with shell added

Needs boom and/or wall mounting. Screw holes and/or zipties.
Also need mounting for LoRa node. Maybe best kept separate?

Moxon is a simpler alternative to Yagi. Single reflector.
Integrated angle adjustments.
https://makerworld.com/en/models/1925186-moxon-antenna-868-mhz-wall-desk-mount#profileId-2066038

Integrated balun/choke by wrapping the coax
https://makerworld.com/en/models/1379081-433-mhz-moxon-antenna-1-1-swr#profileId-2964615

Simple frame, many makes
https://www.thingiverse.com/thing:3931824

Direct mount on SMA connector
https://www.printables.com/model/1378116-moxon-antenna-868mhz-meshtastic

https://la4o.no/medlemsmote-antennebygging-moxon-2m-antenne-onsdag-5-november

Could also be fun with a handheld one for wardriving.
Testing whether connection can be established with directional antenna over omnidirectional.
Using MeshMapper etc.
! must reduce transmit power to stay within limits

https://www.instructables.com/DIY-Yagi-Antenna-for-LoRa/
3d-printed square boom. Intended for handheld. Can easily be adapted.
Successful in establishing 40 km connection.

https://3g-aerial.biz/en/online-calculations/antenna-calculations/dl6wu-yagi-uda-antenna-online-calculator
Calculator supports boom correction. Can also output files for simulation.

For EU868.
4 elements can be under 20 cm long.
5 elements under 25 cm. Might fit diagonally on typical 3d-printer.


## Dipole for VHF/UHF 2m/70cm

Initial build done.
Brief RX testing.
Extremly brief testing on TX by an operator.

## Moxon for VHF

2M (144MHz) Pocket Moxon Antenna Build and Demo
https://www.youtube.com/watch?v=3HqDZlxQKCs
3d-printed parts and wire.
Folds down neatly.

Build a 2 Meter Ham Radio Moxon Antenna in 10 Minutes! 
https://www.youtube.com/watch?v=AOU2pBo0whA
Using stiff steal wire onto a BNC connector

Antennenbau 📡 2m & 70cm Moxon Beam
https://www.youtube.com/watch?v=YVxoLn2rXCw
Using stiff steel wire, and a PVC tube in the center

DL1DN/DL2MAN Moxon 2M/70cm Foldable Beam Antenna 
https://www.youtube.com/watch?v=pTfb-mkgNZM
3d-printed parts, glass fiber tubes with wire inside.
Longest pipes are 347 mm. Could be 2 printed pieces?

DL1DN/DL2MAN Moxon with 3d-printed printed rods instead of purchased
https://www.printables.com/model/1252145-tubes-for-moxon-antenna
DL1DN/DL2MAN Moxon adapted with shorter 3d-printed rods
https://www.printables.com/model/1392861-2m-moxon-tubes-for-smaller-printers

Camping style rod connectors are nice for quick assembly.

## Easy 10 meter band antenna

A flowerpot style is feasible for 10 meter band.
Overall length would be short of 3 meters.

https://hamradiodx.net/easy-to-build-10-meter-28-mhz-vertical-antenna-for-dx/

? need 12 meter of RG58 cable, and 2.5 meter of insulated copper 1–1.5 mm conductor. 

## Inverted V shape dipole for 10/20 meter

Need some rods on each side. Maybe 1-2 meters.
Need a mast in the center. Maybe 2-3 meters

https://www.kjell.com/no/produkter/lyd-og-bilde/kabler-og-adaptere/hoyttalerkabler/hoyttalerkabel-075-mm-hvit-25-m-p69242
https://www.clasohlson.com/no/p/49-333-25

https://www.kjell.com/no/produkter/elektro-og-verktoy/maleinstrumenter/malekabler-sonder-kontakter/polskruer/bnc-hann-til-polskrue-p37450

0,75 mm²
Bit smaller than 20 gauge.
Could use as small as 22 gauge, 0.66 mm2

https://km1ndy.com/diy-dipole-how-does-antenna-work/

https://www.youtube.com/watch?v=GZO2VsLRCZM
https://www.youtube.com/watch?v=xXSjSWqwXUQ
https://www.youtube.com/watch?v=1ifZt6kVzOo


## Loading coils

Adjustable loading coil can be made with just wire, and tapping in at specific point to tune.
Many 3d-printable designs available.
For example, https://www.printables.com/model/875179-portable-loading-coil-vertical-antenna-26uh/related

Or just build it out of scrap.
https://wb3gck.com/2023/09/24/junk-box-loading-coil/
