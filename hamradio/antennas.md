
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


## Impedance matching

Critical for transmission.
Poor impedance matching will cause reflected energy back into transmitter.
Reduces efficiency of transmitted power.
May destroy the transmitter.


## Turnstile antenna

Aka crossed-dipole antenna.

Circular polarization.
Omnidirectional.

Made by crossing two half-wave dipole elements at 90-degree angles,
and connecting them with a coaxial phasing harness to achieve circular polarization.


https://alicja.space/blog/how-to-build-turnstile-antenna
Practical build using 3d-printed parts.
! need 75 ohm cable stub

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


## Projects

## Dipole for VHF/UHF 2m/70cm

Initial build done.
Brief RX testing.
Extremly brief testing on TX by an operator.

## First 10 meter band antenna

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
