EESchema Schematic File Version 4
LIBS:touchflower-cache
EELAYER 26 0
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
L touch:TPP223-BA6 U1
U 1 1 5B1035E1
P 5500 1550
F 0 "U1" H 5500 2100 50  0000 C CNN
F 1 "TPP223-BA6" H 5700 2000 50  0000 C CNN
F 2 "touchflower:SOT-223-6-extraspace" H 5200 1650 50  0001 C CNN
F 3 "" H 5200 1650 50  0001 C CNN
	1    5500 1550
	1    0    0    -1  
$EndComp
$Comp
L device:C C1
U 1 1 5B1039DE
P 4800 1800
F 0 "C1" H 4915 1846 50  0000 L CNN
F 1 "C" H 4915 1755 50  0000 L CNN
F 2 "Capacitors_SMD:C_0805_HandSoldering" H 4838 1650 50  0001 C CNN
F 3 "" H 4800 1800 50  0001 C CNN
	1    4800 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 1550 4800 1550
Wire Wire Line
	4800 1550 4800 1650
$Comp
L power:GND #PWR0101
U 1 1 5B103A78
P 4800 2150
F 0 "#PWR0101" H 4800 1900 50  0001 C CNN
F 1 "GND" H 4805 1977 50  0000 C CNN
F 2 "" H 4800 2150 50  0001 C CNN
F 3 "" H 4800 2150 50  0001 C CNN
	1    4800 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4800 2150 4800 2050
Wire Wire Line
	5400 1950 5400 2050
Wire Wire Line
	5400 2050 4800 2050
Connection ~ 4800 2050
Wire Wire Line
	4800 2050 4800 1950
$Comp
L power:VDD #PWR0102
U 1 1 5B103B7B
P 5400 900
F 0 "#PWR0102" H 5400 750 50  0001 C CNN
F 1 "VDD" H 5417 1073 50  0000 C CNN
F 2 "" H 5400 900 50  0001 C CNN
F 3 "" H 5400 900 50  0001 C CNN
	1    5400 900 
	1    0    0    -1  
$EndComp
Wire Wire Line
	5400 900  5400 1000
$Comp
L device:LED D1
U 1 1 5B1067AB
P 6950 1400
F 0 "D1" H 6942 1145 50  0000 C CNN
F 1 "LED" H 6942 1236 50  0000 C CNN
F 2 "LEDs:LED_1206_HandSoldering" H 6950 1400 50  0001 C CNN
F 3 "" H 6950 1400 50  0001 C CNN
	1    6950 1400
	-1   0    0    1   
$EndComp
$Comp
L device:R R1
U 1 1 5B10686B
P 6450 1400
F 0 "R1" H 6520 1446 50  0000 L CNN
F 1 "R" H 6520 1355 50  0000 L CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" V 6380 1400 50  0001 C CNN
F 3 "" H 6450 1400 50  0001 C CNN
	1    6450 1400
	0    1    1    0   
$EndComp
Connection ~ 5400 2050
Wire Wire Line
	5800 1600 6000 1600
Wire Wire Line
	6000 1600 6000 1000
Wire Wire Line
	6000 1000 5400 1000
Connection ~ 5400 1000
Wire Wire Line
	5400 1000 5400 1100
Connection ~ 4800 1550
Text Notes 3400 1850 0    50   ~ 0
0-50 pF recommended\n200 pF tested
$Comp
L conn:Conn_01x01 J3
U 1 1 5B12E8EB
P 4400 1550
F 0 "J3" H 4320 1325 50  0000 C CNN
F 1 "Conn_01x01" H 4320 1416 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch1.27mm" H 4400 1550 50  0001 C CNN
F 3 "~" H 4400 1550 50  0001 C CNN
	1    4400 1550
	-1   0    0    1   
$EndComp
$Comp
L conn:Conn_01x01 J2
U 1 1 5B12F106
P 4450 2050
F 0 "J2" H 4370 1825 50  0000 C CNN
F 1 "Conn_01x01" H 4370 1916 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch1.27mm" H 4450 2050 50  0001 C CNN
F 3 "~" H 4450 2050 50  0001 C CNN
	1    4450 2050
	-1   0    0    1   
$EndComp
$Comp
L conn:Conn_01x01 J1
U 1 1 5B12F198
P 4400 1000
F 0 "J1" H 4320 775 50  0000 C CNN
F 1 "Conn_01x01" H 4320 866 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch1.27mm" H 4400 1000 50  0001 C CNN
F 3 "~" H 4400 1000 50  0001 C CNN
	1    4400 1000
	-1   0    0    1   
$EndComp
Wire Wire Line
	4600 1550 4800 1550
Text Notes 6000 850  0    50   ~ 0
For instantious, cut trace\n
Text Label 4850 1550 0    50   ~ 0
sensor
Wire Wire Line
	4650 2050 4800 2050
Wire Wire Line
	4600 1000 5400 1000
Text Label 6100 1400 0    50   ~ 0
out
Wire Wire Line
	6600 1400 6800 1400
Wire Wire Line
	7100 1400 7250 1400
Wire Wire Line
	7250 1400 7250 2050
Wire Wire Line
	5400 2050 7250 2050
Wire Wire Line
	5800 1400 6300 1400
$EndSCHEMATC
