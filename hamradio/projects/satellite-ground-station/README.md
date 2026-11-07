
# Sattelite ground station

Goal: Receive metrics from sattelites like ISS, FRAMSAT-1, Sonate-2 or similar.
UHF. 435 Mhz range


Use SatNOGS with RPI and RTL-SDR.
https://wiki.satnogs.org/Build
Recommended to have a bandpass and LNA.


## Antenna

Turnstile.




## References

### alicja.space

https://alicja.space/blog/how-to-build-turnstile-antenna
For 435 Mhz / 70 cm.
Practical build using 3d-printed parts.
Used 3/8 wavelenght distance to reflectors.

Measured SWR around 1.8 for 435.500 Mhz.
Was near 1 slightly below 400 Mhz! 380-390 Mhz.

### Ivo I6IBE

Intended for handheld usage more than stationary ground station?
Uses 1/4 wavelength distance for reflectors.

https://www.radioamatoripeligni.it/i6ibe/turnhard/turnhard.htm

Warns that the RG-59 coax positioning is important for SWR.

> We noticed that on these antennas,
> simply by POSITIONING the 75 Ohm RG-59 coaxial cables in a different position on the antenna boom,
> the SWR magically drops to 1:1.
> In practice, simply bundle the four coaxial cables together and solder the central ones and the four shields.
> Then, rotate the 75 Ohm cables 180 degrees (a U-turn) and solder the SO239 feeder.

Updated drawing is available.

### IZ7BOJ
https://iz7boj.wordpress.com/2018/12/02/double-turnstile-construction-for-satellites-receiving-in-435mhz-band/

Following a design from Ivo I6IBE

Used 1/4 wavelength distance to reflectors.
Tested with 


SA2KNG LSF Core Contributor

> When building these, the distance to the reflector can be used to tune the frequency and impedance.
> I suggest building it so the position can be adjusted while measuring with a SWR meter or VNA/SNA to it’s final position.

### VINNANT-ANTENA TUR 435/3-S

Can be tuned by moving the reflector ring up/down.
For 435Mhz-432Mhz-438Mhz 



### A Simple Fixed Antenna for VHF/UHF Satellite Work - L. B. Cebik W4RNL
https://www.qsl.net/xe1cdx/Hamdocs/satellite/A%20Simple%20Fixed%20Antenna%20for%20VHF-UHF%20Satellite%20Work.pdf
Proposes a dual Moxon turnstile.
Compares with crossed dipole. Both with screen reflector and 2-element turnstile.
Moxon version has wider beam. So better for low-angles than the 2-element turnstile.

## jonnor 435 turnstile

Basically a mix of IZ7BOJ and alicja.space

From alicja.space, the 3d printed parts, and putting the coax inside the structure.
From IZ7BOJ, the use of threaded rods and wire lugs.

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
- Washers. M4

- Cableshoes M4

Dimensioning

Inner coax stuff.
One around 12 cm long.
Other around 24 cm
Outer diameter 6.1 mm.
2x wide
