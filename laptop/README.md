
## Requirements

Must-have

* Approx A4 size, 14"
* Thickness: under 25mm total (screen+base)
* Weight: below 2kg
* Battery life: around 10 hours programming
* x86_64 dual/quad-core
* Linux-friendly

Maybe: Tablet mode

* Touchscreen
* Battery in screen part
* Tabled can dock into base w/keyboard
* Separatable keyboard. Bluetooth?

Maybe: Stand mode

* Lift screen up to be parallel to line-of-sight
* Needs around 25 cm lift
* Keyboard+touchpad deattaches
* Integrated stand.
* Ex: Base pivots as 2 parts at hinges. One part becomes front foot, other becomes rear foot

## Parts

* Motherboard: Intel NUC7i3DN (CPU,WiFi/BT included)
* RAM: DDR3 SODIMM, 8GB
* SSD: M.2, 256GB
* Display: eDP. 13" IPS panel, FullHD
* Keyboard. Bluetooth touchpad integrated. [1by1](https://www.amazon.com/dp/B00VRC6U2C)
* Battery. Custom LiPo pack?

## Battery

Typical consumption: 5W. Need around 50Wh capacity.
4 cell needed to be able to use a DC/DC dropdown to 12V.
Would use a DC charger of 18-20V.

`parallel=6; cells=4; voltage=3.7; capacity=550e-3; watts=parallel*capacity*voltage*cells; print(watts)`

### Circular cells

* 18650 batteries are 18.6mm standard. Capacity around 3000mAh.
Too thick to be underneath the screen and limits total thickness of screen part to 20mm.
1p*4s=4batteries @ 3000mAh = 44Wh. 2p=88Wh.
* 14500 are 14×53mm (AA size). Capacity around 1000mAh.
3p*4s=12batteries @ 1000mAh = 44Wh. 4p=60Wh.
[1](https://www.banggood.com/4Pcs-GTL-3_7V-2300mAh-14500-Rechargeable-Li-ion-Battery-p-1029880.html?rmmds=search&cur_warehouse=CN)

### LiPo 1s pack

LiPo flatpacks. 1 cell approx 7mm thick. Can stack 2 in height under screen.
6p*4s=24batteries @ 550mAH = 48Wh.

* 1s, 550mAh. [1](https://www.banggood.com/ZOP-Power-3_7V-550mAh-45C-1S-Lipo-Battery-White-Plug-p-1152551.html?rmmds=search&cur_warehouse=CN)
* 4s charger board [1]((https://www.banggood.com/5Pcs-4S-30A-14_8V-Li-ion-Lithium-18650-Battery-BMS-Packs-PCB-Protection-Board-Balance-p-1191041.html?rmmds=detail-left-hotproducts__3&cur_warehouse=CN)
