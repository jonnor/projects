
- Weather sattelites
- Amateur sattelites

## Radio communication

UFH in 70 cm band. ITU from 430 to 440 MHz, US 420 to 450 MHz.


## Two-Line Element Set (TLE)

Data format encoding a list of orbital elements of an Earth-orbiting object,
for a given point in time (the epoch).
Can be used to estimate future and past postition of the sattelite.

### FramSat-1

Launched Sep 5, 2026 by NTNU.


```
Norad ID: 100610
International Designator: 2026-203B
```

Transmits on 70 cm amateur band. At 


SatNOGS observations of FRAM-1.
Including data
https://network.satnogs.org/observations/?sat_id=BXJV-0815-0756-1233-1493&start=2026-09-17+18%3A56&end=2026-09-18+21%3A06&observer=&station=&results=w1&results=a1&results=d1&transmitter_mode=&transmitter_uuid=&experimental_observation=

Example with data
https://network.satnogs.org/observations/15015263/

Information about telemetry reception.
https://github.com/OrbitNTNU/framsat1-telemetry-decoder/blob/main/FramSat_1_Reception_Guide.pdf
Provides a GNU Radio workflow using RTL-SDR.

Telemetry decoder
https://github.com/OrbitNTNU/framsat1-telemetry-decoder
