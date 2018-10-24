
# Wind turbines

Vertical designs can collect wind from all sides, and exploit gusty winds, making them suitable for more different sites.
Small to medium horizontal designs get this property by letting the body spin to meet the wind, and using rotors.

Standard vertical windmills have significant torque ripple. Sweeping the blades to form a helical turbine eliminates this.
The most common design is a Darrieus, which uses the lift of airfoils. Its major problem is that it is inherently
[not self-starting](http://forthewind.weebly.com/the-darrieus-self-starting-problem.html).

Using a Darrieus/Savonius hybrid is the simplest solution, but reduces maximum efficiency.
More original solutions includes foldable [airfoils](http://www.webalice.it/acecere48/finalreport.pdf)

## Costs
Banggood.com has both horizontal and vertical turbine designs for 12-24V. Prices down to 200 USD for 200W. 

## Airfoil design

[NACA](https://en.wikipedia.org/wiki/NACA_airfoil) is a series of airfoil designs, defined by a formula with 4/5 parameters.
These are commonly used and well-understood. Airfoiltools.com has [a calculator](http://airfoiltools.com/airfoil/naca4digit).

[Xfoil](http://web.mit.edu/drela/Public/web/xfoil/) is an open-source (GPL) software for simulating airfoils.

## Siting

Where turbines should be positioned to be efficient.

In an off-the-grid setting, most important is that there is good wind when there is bad sun? Ie winter

* Wind atlas, with annual power density. http://www.renewableenergyst.org/wind.htm
* WindFinder.com statistics [Hvar](https://www.windfinder.com/windstatistics/hvar) [Brac](https://www.windfinder.com/windstatistics/brac)


## Open designs

* [Zoetrope](http://www.applied-sciences.net/library/data/zoetrope-wind-turbine.pdf),
plans for a simple vertical tubine made out of metal, that can be assembled with power tools.
* [Thingiverse: Lenz2 helical XL](http://www.thingiverse.com/thing:99132).
An earlier Youtube video showed using a stepper-motor as the generator on a smaller design, via belt+pulley.
* [Thingiverse: Savonius Darrieus Turbine](http://www.thingiverse.com/thing:1502662)

# Generators

DC voltage generation generally is easier than AC mains, because not needing to regulate the frequency, and can use many poles.
Efficient and cheap DC/DC converters, as well as inverter electronics for AC mains voltage exists.

## Axial versus radial

* 

References

* [Axial-flux vs. radial-flux permanent-magnet synchronous generators for micro-wind turbine application ](http://innowecs.utcluj.ro/art_pulicate/0764-epe2013-full-15251784.pdf)
Compares using FEA, two types of axial-flux and one type of radial-flux. `The results show that the axial-flux PMSG is the best solution for micro-wind turbine application`.

## Axial flux

Design for fabbability

* Laser-cut or CNC-milled wooden base-plates
* Laser-cut fabric (linen/hemp/jute)
* Impregnated with polyester resin
* Less than 50 cm diameter
* Design in room for the wires
* Design in coil bobbins, and other things needed for sub-assemblies

References

* [Design and Testing of a Permanent Magnet Axial Flux Wind Power Generator](http://ijme.us/cd_08/PDF/190%20ENT%20202.pdf).
Gives a `analytic solution for magnetic field strength in the airgap`. Allows to evaluate back emf, and machine torque
and voltages for specified electrical loading conditions. Uses a method `of dividing the machine into radial slices`.
* [Excel spreadsheet](http://www.nadaparasiempre.com/hobbies/wind-energy/generator/index.html) for calculating parameters of generator
[Alternative source](http://www.fieldlines.com/index.php?topic=143174.0)

## Coil winding

Could one wind coil bobbins with a lightweight XYZ machine, like a 3d-printer or small CNC mill?
By movin

[Thingiverse: Coil Winding Machine](http://www.thingiverse.com/thing:981327)


## Open designs

* [3d-printable 50w by Energy Creator](http://www.3ders.org/articles/20160305-3d-printed-pmg-generator-has-everything-you-need-to-power-a-50w-lightbulb.html).
Seems to use an original stator configuration, which is claimed to be more efficient and easy to construct.
35 USD download for files and instruction videos.
* [3d-printable, 12volt+ axial flux](http://www.thingiverse.com/thing:633603)
* [3d-printable axial flux](http://www.thingiverse.com/thing:687743)
* [3d-printable axial flux](http://www.thingiverse.com/thing:1416740)
* [3d-printable dual axial flux](https://hackaday.io/project/159568/logs). 100watt. Seems well designed.

Off-the-shelf

* Using a car/motorcycle alternator. Example: [Biltema](http://www.biltema.no/no/Bil---MC/Bilreservedeler/Elektrisk-anlegg/Dynamo/)


# Vertical turbines

* Using a [single-side consentrator](https://youtu.be/NiHG5ahf4zQ?t=945), increasing efficiency `from <20% to 30% efficiency`

# Horizontal turbines

Open designs

* [Functional horizontal wind turbine with axial flow generator](http://www.thingiverse.com/thing:948375)
