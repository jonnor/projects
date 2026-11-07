
# Sattelite ground station

Goal: Receive metrics from sattelites like ISS, FRAMSAT-1, Sonate-2 or similar.
UHF. 435 Mhz range


Use SatNOGS with RPI and RTL-SDR.
https://wiki.satnogs.org/Build
Recommended to have a bandpass and LNA.


## Antenna

Turnstile.


https://alicja.space/blog/how-to-build-turnstile-antenna
For 435 Mhz / 70 cm.
Practical build using 3d-printed parts.

https://iz7boj.wordpress.com/2018/12/02/double-turnstile-construction-for-satellites-receiving-in-435mhz-band/



## My turnstile

Principle

- 3d printed caps on each side
- Tubular middle part. Pick common PVC tube diam
- Antenna connector. SMA? BNC? Hide inside tube
- Threaded rods as active element and reflector
- Attach threaded rods to 3dp with nuts
- Connect theaded rods using cableshoes and nuts. ! space to screw
- Connection to. Tubular under? Need cable out on side
- V2: Integrat VNA, bandpass. With bias tee power

Materials needed

- RG58 cable
! 75 ohm cable stub. Ex RG59
https://www.kjell.com/no/sok?q=RG59&search=true

- Rods Threaded M4.
Approx (17*4)+(35*2) = 138 cm
Min 2x 1 meter.
https://www.clasohlson.com/no/p/11-992-4
- Nuts. M4
- Cableshoes M4

Dimensioning

Inner coax stuff.
One around 12 cm long.
Other around 24 cm
Outer diameter 6.1 mm.
2x wide
