EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:switches
LIBS:relays
LIBS:motors
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L LED D1
U 1 1 5A89BBBF
P 3450 1850
F 0 "D1" H 3450 1950 50  0000 C CNN
F 1 "LED" H 3450 1750 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 3450 1850 50  0001 C CNN
F 3 "" H 3450 1850 50  0001 C CNN
	1    3450 1850
	-1   0    0    1   
$EndComp
$Comp
L LED D2
U 1 1 5A89BC5A
P 3450 2200
F 0 "D2" H 3450 2300 50  0000 C CNN
F 1 "LED" H 3450 2100 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 3450 2200 50  0001 C CNN
F 3 "" H 3450 2200 50  0001 C CNN
	1    3450 2200
	-1   0    0    1   
$EndComp
$Comp
L LED D3
U 1 1 5A89BD04
P 3450 2500
F 0 "D3" H 3450 2600 50  0000 C CNN
F 1 "LED" H 3450 2400 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 3450 2500 50  0001 C CNN
F 3 "" H 3450 2500 50  0001 C CNN
	1    3450 2500
	-1   0    0    1   
$EndComp
Wire Wire Line
	3300 1850 3150 1850
Wire Wire Line
	3150 2200 3300 2200
Wire Wire Line
	3150 2500 3300 2500
Connection ~ 3150 2200
Connection ~ 3150 2500
$Comp
L Conn_01x01 J1
U 1 1 5A89BD63
P 4000 1850
F 0 "J1" H 4000 1950 50  0000 C CNN
F 1 "Conn_01x01" H 4000 1750 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4000 1850 50  0001 C CNN
F 3 "" H 4000 1850 50  0001 C CNN
	1    4000 1850
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 J2
U 1 1 5A89BD8B
P 4000 2200
F 0 "J2" H 4000 2300 50  0000 C CNN
F 1 "Conn_01x01" H 4000 2100 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4000 2200 50  0001 C CNN
F 3 "" H 4000 2200 50  0001 C CNN
	1    4000 2200
	1    0    0    -1  
$EndComp
$Comp
L Conn_01x01 J3
U 1 1 5A89BDBD
P 4000 2500
F 0 "J3" H 4000 2600 50  0000 C CNN
F 1 "Conn_01x01" H 4000 2400 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4000 2500 50  0001 C CNN
F 3 "" H 4000 2500 50  0001 C CNN
	1    4000 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 2500 3800 2500
Wire Wire Line
	3800 2200 3600 2200
Wire Wire Line
	3800 1850 3600 1850
Wire Wire Line
	3150 1850 3150 2850
$Comp
L Conn_01x01 J?
U 1 1 5A89BF4B
P 4000 2850
F 0 "J?" H 4000 2950 50  0000 C CNN
F 1 "Conn_01x01" H 4000 2750 50  0000 C CNN
F 2 "Wire_Pads:SolderWirePad_single_0-8mmDrill" H 4000 2850 50  0001 C CNN
F 3 "" H 4000 2850 50  0001 C CNN
	1    4000 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2850 3800 2850
$EndSCHEMATC
