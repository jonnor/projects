Shopbot control
================

Reverse engineering how the `PC<->Shopbot` communication works,
in order to be able to control it 

Motivation
-----------

For reference, two other motivations for replacing the host software are:

1. ability to have custom user interfaces, mobile/physical controls
2. ability to dynamically & continuously control cutting speed,
for instance based on sensor feedback (vibration, audio, current-draw)

Status
-------
All testing done on a Shopbot PRS Alpha from 2013. TODO: document versions of software/controller-board
Testing done over one evening 20 February 2015.

What we know

* How to set up Shopbot and the software so we can intercept the communication
* That the Shopbot does not use GCode, HPGL, [OpenSBP](http://www.opensbp.org/) or similar high-level protocol
* Roughly what happens during device init
* How the values of the digital inputs work
* How to set value of digital outputs
* That there is continious ping/pong communication even when not moving
* That the pong (from Shopbot) contains current position
* How the scaling factor/units for current position works

What we probably know

* That a lot of the logic happens on the host (as opposed on to on the machine), including kinematics.

What we don't know

* How to send move commands


Faking serialport communication
--------------------------------------

For setting up COM port in `Shopbot Control`, go to
`Values -> Inputs / driver definitions`
Standard baudrate (setting 5 - 921.6) is 962100 baud

http://com0com.sourceforge.net/
Had to use this driver for signed windows
http://code.google.com/p/powersdr-iq/downloads/detail?name=setup_com0com_W7_x64_signed.exe&can=2&q=

When the Shopbot Control control box is connected it will automatically be detected by control software.
Therefore, when overriding the COM port setting to emulate a Shopbot in software
one must unplug the USB connection to the Shopbot.

After changing the COM port to a custom value,
one has to restart the software and then go from
Preview to Move / Cut mode in order for SW to send handshake initialization sequence.


Findings from emulating both sides, one by one
--------------------------
Script: [shopbot-query.py](./tools/shopbot-query.py)

The values seem to be (in hex): EF FF FF FF FF (6 bytes).
It is repeated 4 times before software gives up and gives
a prompt asking to stay in Preview mode or Quit

When sending the init sequence (once), we get the response

    ['\xda\x0f\x03\x00\x00\x00\xe0\x00\x08\x1b\x02\xf2\x00\x00\x00\x00\xff\xff\x00\x00i\xad\x00\x00\xcei\x00\x00\x14\t\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00']

When sending the firmware response to the control software, it successfully goes into "Cut/Move mode" and sends

    ['\x81\xff\xff\xff\xff\xff\x00\x00i\xad\x00\x00\xcei\x00\x00\x14\t\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00']

Then Shopbot responds with (when being in position X=1000, Z=50, Y=0)

    ['\xda\x0f\x03\x00\x00\x00`\x00\x08\x18\x02\xfd\x00\x00\x00\x00\xff\xff\x00\x00i\xad\x00\x00\xcei\x00\x00\x14\t\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00']

However, just responding with that seems to cause initialization to be aborted.


Findings from man-in-the-middle
--------------
Script: [shopbot-mim.py](./tools/shopbot-mim.py)

For details, see the annotated data dumps:
[shopbot-movement1-notes.md](./shopbot-movement1-notes.md)

Looks like setting outputs is done using 0xf0 command followed by the bit value of the register.

    -> 6 '\xf0\x01\x00\xff\xff\xff'
    <- 50 '\xda\x0f\x03\x00\x00\x00\xe0\x00\x08\x15\x03\x05\x00\x00\x00\x00\xff\xff\x00\x01S\xd4\x00\x00\xc0\xba\x00\x00\x16\xe9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x002\xdd\x00\x00\x00\x01'
    -> 6 '\xf0\x00\x00\xff\xff\xff'
    <- 50 '\xda\x0f\x03\x00\x00\x00\xe0\x00\x08\x14\x03\x05\x00\x00\x00\x00\xff\xff\x00\x01S\xd4\x00\x00\xc0\xba\x00\x00\x16\xe9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x002\xdd\x00\x00\x00\x00'

    -> 6 '\xf0\x02\x00\xff\xff\xff'
    <- 50 '\xda\x0f\x03\x00\x00\x00\xe0\x00\x08\x16\x03\x04\x00\x00\x00\x00\xff\xff\x00\x01S\xd4\x00\x00\xc0\xba\x00\x00\x16\xe9\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x002\xdd\x00\x00\x00\x02'

    -> 6 '\xf0\x00\x00\xff\xff\xff'

Periodic pong messages seem to contain values of all axes, and the digital input pin registers.

    PING
    <- 50 : da 0f 03 00 00 00 e0 00 08 13 03 06 00 00 00 00 ff ff 00 01 5b 77 00 00 c0 ba 00 00 16 e9 00 00 00 00 00 00 00 00 00 00 00 00 00 00 3a 80 00 00 00 08
							          X? XX XX XX
									      Y? YY YY YY
				       						      Z? Z? ZZ ZZ
	       I
				       ?? ?? ??     seems to fluctuate
																	        ?? ?? ?? ?? ?? ?? seems to vary over different move values. Checksum??

    I: input pins. Active low?
    X/Y: axis values. val = position_mm * 97.749
    Z: axis values. val = position_mm * 117.3


Looks like most of path planning is on computer side (not firmware/controlbox):

- The jog/move speed commands don't seem to send anything
- pong message seems to show position of all axises continuously
- the movement payloads are huge, several kilobyte for a single 5-10 mm move
- sending data across slowly for a single move results in very jerky movement

This makes understanding the protocol trickier (as it might not be a straight forward translation of the OpenSBP format)
and re-implementing the host control software (as it needs to be near-real-time capable, and handle the kinematics)

Looks almost as if control software is just sending registers/commands for the different stepper motors directly.



