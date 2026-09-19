

##

Uses FM modulation with AFSK AX.25 framing, 1200-baud.

Most widely used as a "tracker" network, with beacons transmitting basic info, and then can be monitored locally or via internet.

But according to the creators, "APRS is a LOCAL RF network" - especially useful for event-like information that should be broadcast locally.

> If something is happening now, or there is information that could be valuable to you,
then it should show up on your APRS radio in your mobile.

## Understanding APRS

A lot of reference materials here:
https://github.com/wb2osz/aprsspec
From specification to explainers, and links to other resources.

## Payload formatting

APRS has defined data formats for
Telemetry (analog/digital channel values) and Status Reports (text description).

## LoRa APRS

Uses 70 cm band / 433 Mhz.
Compatible payloads with traditional 2m VHF APRS.
Bridging between the two APRS networks exists.
Uses TNC-2 Monitoring

https://how.aprs.works/lora-aprs-bringing-aprs-into-the-21st-century/

## APRS monitoring websites

- [aprs.fi](https://aprs.fi/#!lat=59.9133&lng=10.7389)
- [aprs.to](https://aprs.to/?center=59.9142,10.7419&zoom=11)

## Uses of APRS


### Local Info initiative
https://www.aprs.org/localinfo.html
Sends information about the local preferred repeater etc.

### APRS for sattelite communication

#### ISS
https://spaceaprs.com/iss

https://amsat-uk.org/beginners/how-to-hear-the-iss/
descrives ISS as sending APRS on 144 Mhz.
But this digipeater seems to be down at the moment?

https://www.ariss.org/current-status-of-iss-stations.html
Says APRS is currently active on 437.825 MHz.
As of Sept 2026 there are currently many days between each.

#### SONATE-2
APRS digipeater on SONATE-2. Callsign DP0SNX
https://www.informatik.uni-wuerzburg.de/en/space-technology/projects/active/sonate-2/information-for-radio-amateurs/

https://spaceaprs.com/sonate-2
As of September 2026, seems to be active.
Making frequent high angle passes over Norway.
Not heard by that many?!

### APRS Thursday

Every thursday is APRS thursday!
https://aprsph.net/aprsthursday/
Encouraged to check in. All checkins are logged.

### APRS for establishing local ham connection

The standardized Direct APRS Text Page allows sending to a specific ham.
Can then ask to go on local VHF repeater, right now or at a scheduled time.

An APRS object can 

## APRS Objects for marking local object of interest

Ex for an event. Mark bathrooms, parking, etc

Or in disaster situation. Mark car crash.

 Unlocking the Power of APRS Objects More Than Just Positions!
https://www.youtube.com/watch?v=JQw_2BnLbUQ
Can chose whether objects are local-only or repeated.
One can register an object in direwolf.

## APRS on the go

BLE specification for TCN
https://github.com/hessu/aprs-specs/blob/master/BLE-KISS-API.md
Supported by for example the aprs.fi app
USB KISS TNC. Serial based.
TCP KISS port. With Direwolf etc

Some apps can decode APRS from phone input.
For example APRSdroid or aprs.fi app.
With APRSdroid, have to go to Preferences -> Connection -> AFSK.

## APRS from UV-K5 handlheld

A 2.5mm to 3.5mm adapter with 3.5mm TRRS connection, to USB-C worked fine.
With both PC analog input, USB soundcard and Android phone.

https://www.kjell.com/no/produkter/lyd-og-bilde/kabler-og-adaptere/aux-kabel/35-mm-til-25-mm/adapterkabel-35-mm-til-25-mm-vinklet-p39116
https://www.kjell.com/no/produkter/lyd-og-bilde/kabler-og-adaptere/aux-kabel/35-mm-kabler/luxorparts-lydkabel-med-35-mm-kontakt-1-m-p65395
https://www.kjell.com/no/produkter/data/kabler-og-adaptere/usb/usb-til-35-mm/linocell-usb-c-til-35-mm-svart-p65369

! Must be TRRS. With a TRS 3.5 mm cable, had noisy shifts when using with USB soundcoard.
And PC does not detect as plugged in. Not tested on phone.


## Ideas


### APRS for sensor network

Maybe it to could be interesting to use sensors to detect phenomena, and then notify on APRS.

Requiresments for a good fit.
- Should be quite rare / low frequency information. Either rare regular updates, or rare events. Limited channel space.
- Should be of public interest. Meaningful/useful to broadcast.
- Most interesting for things relevant to the local area. Local sensing gives that automatically?
- Things of interest to hams. Since they are most likely to have APRS
- 
Must also avoid flooding channel. Ex: maximum of transmission every 10-30 minutes.


- Weather station. A bit boring
- Lighting strike tracking. Cooler. Rare, testing difficult
- Noise monitoring. Relevant. If near roads can be used as traffic proxy.
- Traffic monitoring. Counts of passing vechicles
- Waterway monitoring. Say Akerselva at Bitraf
- UV index.
- RF/EMF noise. Especially relevant for hams. But maybe to hyper-local?

