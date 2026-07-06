
# Multi GPU cooling

## Challenge
Most consumer GPUs are "open style" and do not push exhaust out of chassis.
Instead they push the typically right towards the CPU.
Or in the case of multiple GPUs, right onto the next GPU.
Which is very inefficient and leads to problems removing heat.

This is unlike workstation or server GPUs, which are either blower style or passive (fans external in chassis).
These can reach up to 8 GPUs in a standard rack chassis.
This density is likely not acheivable with open style GPU coolers.

## Concept

Could it be possible to convert a GPU to blower or passive, for better multi-GPU cooling?
For example for the cost-effective 5060ti 16gb.
These have a heatsink which is pretty good. But the fans and shroud would need to be replaced.
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

Could create a passive style shroud.
Which then has attachment points at the end a blower fan.
Blower fan might need a small adapter.

Blower fan candidates.
https://www.digikey.no/no/products/detail/cui-devices/CBM-979433B-135-540-22/16581760?so=87691300&content=productdetail_NO

Digikey has a large selection
https://www.digikey.no/no/products/filter/vifter/b%C3%B8rstel%C3%B8se-dc-vifter-bldc/217?__cf_chl_f_tk=j_ejDJl170NzwfQ9dq8ZXW1UDotKy0EABavd4shxLAQ-1783333677-1.0.1.1-fVfNwHPEhlOWzjiSgJFYk.C6ChEamfxjHHJZew0sVR8&s=N4IgjCBcoOwJwAYqgMZQGYEMA2BnApgDQgD2UA2iAMwBMCALDTCMbQ1QKwgC6xADgBcoIAMoCATgEsAdgHMQAXwXEAbMhCSAJsIC0YBBH5DIIFiAEBPPvmGZcaJUA

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

- Old ASUS RTX2060 
- MSI GeForce RTX 5060 Ti 16G VENTUS 2X OC PLUS.  227 x 126 x 41 mm
- ASUS DUAL RTX 5060 Ti 16 GB. 229 x 120 x 50mm

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

### Passive style GPUs

What are typical dimensions?

The Intertech 4W2 has 328 mm space for the GPU.
267 mm seems standard for NVidia.
330 is E-ATX standard.


- Tesla P40
https://www.techpowerup.com/gpu-specs/tesla-p40.c2878
Length 267 mm

- AMD Instinct™ MI50
10.5" (267mm) 

- NVIDIA RTX PRO 6000 Blackwell Server
https://www.techpowerup.com/gpu-specs/rtx-pro-6000-blackwell-server.c4274
Length 267 mm

- NVIDIA RTX PRO 4500 Blackwell Server
https://www.techpowerup.com/gpu-specs/rtx-pro-4500-blackwell-server.c4387
Length 267 mm

Radeon 9700 XTX
https://www.asrock.com/Graphics-Card/AMD/Radeon%20RX%207900%20XTX%20Passive%2024GB/
- 261 x 111 x 40mm

- SPARKLE Intel® Arc™ Pro B70 Passive
289 x 120 x 42mm.

- Intel Arc Pro B70 Passive 32GB
https://www.asrock.com/Graphics-Card/Intel/Intel%20Arc%20Pro%20B70%20Passive%2032GB/
190* x 112 x 38 mm, 2-slot. + power cable

https://www.asrock.com/Graphics-Card/AMD/Radeon%20AI%20PRO%20R9700S%20Passive%2032GB/index.asp#Specification
- 190 x 112 x 38mm*, 2-slot. Extremely short !!




### Related work

Two people so far doing conversions of passive into a chassis
https://www.reddit.com/r/PcBuild/comments/1ubluto/how_much_airflow_is_needed_for_passive_cooled/
One added centrifugal fans to each GPU.
Other used one fan and pushed to two GPUs.

Radeon Instinct MI25, MI50, MI60 120mm Flat(ish) Cooling Shroud 
https://cults3d.com/en/3d-model/various/radeon-instinct-mi25-mi50-mi60-120mm-flat-ish-cooling-shroud?__cf_chl_f_tk=4t5TcsO5lDbUvDtH8QrjU6LTppLrs4kPUCCH4dT7SSg-1783279228-1.0.1.1-gHATrdyotEE3_HP.Pid7.ZzMwsOW9s_NEWB7VYH1iK0
Uses a large centrifugal 120mm fan


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

8x 4090/5090 servers. 300 watt TDP per each.
Used a 7U/10U rack, to have two stories of 4x GPUs.
https://www.youtube.com/watch?v=CgsDEFaGLJ0

