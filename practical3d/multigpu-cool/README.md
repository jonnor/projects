
# Multi GPU cooling

## Challenge
Most consumer GPUs are "open style" and do not push exhaust out of chassis.
Instead they push the typically right towards the CPU.
Or in the case of multiple GPUs, right onto the next GPU.
Which is very inefficient and leads to problems removing heat.

This is unlike workstation or server GPUs, which are either blower style or passive (fans external in chassis).

## Concept

Could it be possible to convert a GPU to blower or passive, for better multi-GPU cooling?
For example for the cost-effective 5060ti 16gb.
These have a heatsink which is pretty efficient. But the fans and shroud would need to be replaced.

This is called "deshrouding" in DYI PC community.
And is popular for small-form-factor (SFF) builds in particular. 

### Rear leading fins

If heatsink fins are leading in the rear direction, that is ideal.
That is basically how blower or passive heatsinks are.
Would just need to replace shroud and place new fans.
And it would eject exhaust out back of chassis.
Compatible with typical PCI mounting.
Need to ensure that there is no air leakage, and that the fans have sufficient airflow and static pressure.
Having push-pull on the fans might make sense.

#### Blower style

A blower-style would use centrifugal fan.
This limits how close GPUs can be mounted to eachother.
Need about 1 slot spacing extra.

The 5060ti "dual" fan style are quite short, from 230mm to 260mm.
That allows fitting a reasonably sized while still being within typical E-ATX width of 330 mm.

#### Passive style

For passive style, the cross-section of a single fan is rather small.
If considering multiple GPUs together it will be possible to use larger fans.
For example 2, 4, 6 or 8x GPUs together.

Could have a frame with fans on each side. Push-pull.
Space for GPUs in the middle. Have the shroud of the GPUs fit to the frame.


### Up leading fins

By far the most common for consumer RTX GPUs.

If the fins are oriented in the other direction it is more tricky.
Not really compatible with PCI motherboard mounting.
Would need PCIe adapters. Or very creative shrouding near motherboard.
Only really feasible if making a custom multi-GPU box?

To fit in typical chassis space.
Will have to stack 2 cards top of eachother.
And additional rows will have to be after eachother. So second row heated by first.
The PCIE connectors/boards may also limit airflow.

### Card compatibilty

For 5060 TI 16 GB.

Cooling fins in rear direction :D

- MSI GeForce RTX 5060 Ti 16G VENTUS 2X OC PLUS
- ASUS DUAL RTX 5060 Ti 16 GB

Cooling fins in up direction :(

- Basically all other 5060, 5070 cards...
- GIGABYTE RTX 5060 Ti WINDFORCE
- MSI GeForce RTX 5060 Ti 16G GAMING OC


### GPU backplanes

Can be direct electrical boards.
Or have PCIE switches.

Connector types

- SFF-8654 / SlimSAS. PCIE Gen 4.0. SlimSAS 4i - 4 lanes, and SlimSAS 8i - 8 lanes.
- SFF-8611 / Oculink. PCIE Gen 4.0. 4i almost only one used.
- MCIO / Mini Cool Edge. PCIE Gen 5.

Baseboards for 4U server can have up to 11 PCIE slots.

- 8654 To PCI-E 4.0 X16 & MCIO To PCIe 5.0 X16 baseboard. 11 slots
https://www.aliexpress.com/item/1005010450558406.html



https://www.ioi.com.tw/products/proddetail.aspx?AppID=1008&CatID=116&HostID=2121&ProdID=1160019


### Related work

Two people so far doing conversions of passive into a chassis
https://www.reddit.com/r/PcBuild/comments/1ubluto/how_much_airflow_is_needed_for_passive_cooled/
One added centrifugal fans to each GPU.
Other used one fan and pushed to two GPUs.

4U chassis with support for 8 GPUs.
https://onechassis.en.made-in-china.com/product/zGnpOUPAYjhC/China-4u-Rackmount-GPU-Server-Chassis-for-3090-4090-Cards-Ideal-for-Vfx-3D-Rendering-Graphics.html


8 3 slot GPUs. 2 height
https://a16z.com/building-an-efficient-gpu-server-with-nvidia-geforce-rtx-4090s-5090s/
Used off-the-shelf server components.
GPU backplane board with support for 8x GPUs. ASUS 90SC0M60


Dell T630 with 4x Tesla P40.
https://www.reddit.com/r/LocalLLaMA/comments/1924vtm/dell_t630_with_4x_tesla_p40_description_in/
Very tight fit though.

Centrifugal fan attachment for Tesla P4 (passive)
https://www.printables.com/model/1685699-fan-shroud-3d-model-for-dell-micro-65w-cpu-fan-nvi

Huge shroud from bottom to regular GPU
https://linustechtips.com/topic/1529112-cant-believe-i-didnt-do-this-sooner-gpu-shroud/

Another huge shroud, allows cold air from back of chassis.
https://www.printables.com/model/322158-gpu-airboxsupport

Retroffittable lower-fan attachment for regular GPUs.
That takes the air and vents it out back.
https://videocardz.com/newz/cooler-master-develoed-a-blower-fan-attachment-for-all-modern-gpus-lowers-temps-by-up-to-6c

