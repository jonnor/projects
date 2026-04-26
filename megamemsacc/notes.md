
# TODO

- Check and fix midpoint subtraction for ADC
- Verify that the design of fingers is actually correct
- Do some calculations on the expected capacitive change from the finger structure
- Try improving the opamp. Charge amplifier, or transimpedance amplifier? Might need amplification
- Create a small jig to allow rotating the setup without touching it
- Increase the excitaiton/sample frequency.
- Try opamp with lower input bias and capacitance. Ex: OPA2333 / AD8066
- Try increasing capacitance of the fingers. Can 3x the height?
- Create a PCB to reduce noise from long cables
- Try a metal version of the fingers

## Test with 3d-printed fingers

There is very little change in output when the fingers shift from change in position,
until they hit the fingers directly.
Might be that the capacitance overall is too low? 
And/or that the reistance of the print is limiting SNR?
Or that the long cables etc has a high noise floor?

The electronics seems to work, at least for larger capacitance changes.
For example when putting my human finger over the overlap between fingers, the signal increases strongly.
Can see positive swing when doing it on one side, and then negative swing when doing it on the other side.

! the output of the opamp seems a bit messy? Might be that some DC bias is being amplified etc.

! the soundcard really loads the system when attached to proof mass.
Need proper oscilloscope to be able to actually debug.

! The practical swing is considerably less than the finger gap - because of poor printing tolerances.
There are slight angles on the different singers which means very quickly something touches somewhere.
Have under 1 mm in practice, despite 4.5 mm interfinger gap with 1.2 fingers.
