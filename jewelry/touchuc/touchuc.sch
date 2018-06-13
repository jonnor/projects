EESchema Schematic File Version 4
LIBS:touchuc-cache
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
L power:GND #PWR0101
U 1 1 5B21241C
P 1600 2050
F 0 "#PWR0101" H 1600 1800 50  0001 C CNN
F 1 "GND" H 1605 1877 50  0000 C CNN
F 2 "" H 1600 2050 50  0001 C CNN
F 3 "" H 1600 2050 50  0001 C CNN
	1    1600 2050
	1    0    0    -1  
$EndComp
$Comp
L power:+BATT #PWR0102
U 1 1 5B21247D
P 1300 1350
F 0 "#PWR0102" H 1300 1200 50  0001 C CNN
F 1 "+BATT" H 1315 1523 50  0000 C CNN
F 2 "" H 1300 1350 50  0001 C CNN
F 3 "" H 1300 1350 50  0001 C CNN
	1    1300 1350
	1    0    0    -1  
$EndComp
$Comp
L power:-BATT #PWR0103
U 1 1 5B2124FF
P 1300 2050
F 0 "#PWR0103" H 1300 1900 50  0001 C CNN
F 1 "-BATT" H 1315 2223 50  0000 C CNN
F 2 "" H 1300 2050 50  0001 C CNN
F 3 "" H 1300 2050 50  0001 C CNN
	1    1300 2050
	-1   0    0    1   
$EndComp
$Comp
L device:Battery_Cell BT1
U 1 1 5B21268F
P 1300 1700
F 0 "BT1" H 1418 1796 50  0000 L CNN
F 1 "Battery_Cell" H 1418 1705 50  0000 L CNN
F 2 "touchflower:BK-913" V 1300 1760 50  0001 C CNN
F 3 "" V 1300 1760 50  0001 C CNN
	1    1300 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1800 1300 1950
Wire Wire Line
	1600 2050 1600 1950
Wire Wire Line
	1600 1950 1300 1950
Connection ~ 1300 1950
Wire Wire Line
	1300 1950 1300 2050
$Comp
L conn:Conn_01x01 J1
U 1 1 5B212916
P 900 1450
F 0 "J1" H 820 1667 50  0000 C CNN
F 1 "Conn_01x01" H 820 1576 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch1.27mm" H 900 1450 50  0001 C CNN
F 3 "~" H 900 1450 50  0001 C CNN
	1    900  1450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1300 1350 1300 1450
Wire Wire Line
	1100 1450 1300 1450
Connection ~ 1300 1450
Wire Wire Line
	1300 1450 1300 1500
$Comp
L conn:Conn_01x01 J2
U 1 1 5B212A72
P 900 1950
F 0 "J2" H 820 2167 50  0000 C CNN
F 1 "Conn_01x01" H 820 2076 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x01_Pitch1.27mm" H 900 1950 50  0001 C CNN
F 3 "~" H 900 1950 50  0001 C CNN
	1    900  1950
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1100 1950 1300 1950
$Comp
L atmel:ATTINY10-TS U1
U 1 1 5B212C24
P 6100 2050
F 0 "U1" H 6100 2567 50  0000 C CNN
F 1 "ATTINY10-TS" H 6100 2476 50  0000 C CNN
F 2 "TO_SOT_Packages_SMD:SOT-23-6" H 6100 2300 50  0001 C CIN
F 3 "http://www.atmel.com/images/atmel-8127-avr-8-bit-microcontroller-attiny4-attiny5-attiny9-attiny10_datasheet-summary.pdf" H 6100 2050 50  0001 C CNN
	1    6100 2050
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x01 J4
U 1 1 5B212E1B
P 3950 1900
F 0 "J4" H 4100 1900 50  0000 C CNN
F 1 "Conn_01x01" H 4400 1900 50  0000 C CNN
F 2 "touchuc:progpin" H 3950 1900 50  0001 C CNN
F 3 "~" H 3950 1900 50  0001 C CNN
	1    3950 1900
	-1   0    0    -1  
$EndComp
$Comp
L conn:Conn_01x01 J8
U 1 1 5B212EE0
P 7750 1800
F 0 "J8" H 7830 1842 50  0000 L CNN
F 1 "Conn_01x01" H 7830 1751 50  0000 L CNN
F 2 "touchuc:progpin" H 7750 1800 50  0001 C CNN
F 3 "~" H 7750 1800 50  0001 C CNN
	1    7750 1800
	1    0    0    -1  
$EndComp
$Comp
L conn:Conn_01x01 J9
U 1 1 5B212F06
P 7750 2300
F 0 "J9" H 7830 2342 50  0000 L CNN
F 1 "Conn_01x01" H 7830 2251 50  0000 L CNN
F 2 "touchuc:progpin" H 7750 2300 50  0001 C CNN
F 3 "~" H 7750 2300 50  0001 C CNN
	1    7750 2300
	1    0    0    -1  
$EndComp
Text Notes 4050 1050 0    118  ~ 0
Microcontroller\nincl programming header
Text Notes 800  850  0    118  ~ 0
Power
$Comp
L power:VCC #PWR0104
U 1 1 5B213638
P 1600 1350
F 0 "#PWR0104" H 1600 1200 50  0001 C CNN
F 1 "VCC" H 1617 1523 50  0000 C CNN
F 2 "" H 1600 1350 50  0001 C CNN
F 3 "" H 1600 1350 50  0001 C CNN
	1    1600 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 1450 1600 1450
Wire Wire Line
	1600 1450 1600 1350
$Comp
L power:VCC #PWR0105
U 1 1 5B213BB9
P 7350 1550
F 0 "#PWR0105" H 7350 1400 50  0001 C CNN
F 1 "VCC" H 7367 1723 50  0000 C CNN
F 2 "" H 7350 1550 50  0001 C CNN
F 3 "" H 7350 1550 50  0001 C CNN
	1    7350 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	7350 1550 7350 1800
Wire Wire Line
	7350 1800 7300 1800
Connection ~ 7350 1800
Wire Wire Line
	7550 2300 7400 2300
$Comp
L conn:Conn_01x01 J5
U 1 1 5B2145CD
P 3950 2000
F 0 "J5" H 4100 2000 50  0000 C CNN
F 1 "Conn_01x01" H 4400 2000 50  0000 C CNN
F 2 "touchuc:progpin" H 3950 2000 50  0001 C CNN
F 3 "~" H 3950 2000 50  0001 C CNN
	1    3950 2000
	-1   0    0    -1  
$EndComp
$Comp
L conn:Conn_01x01 J6
U 1 1 5B2146D1
P 3950 2100
F 0 "J6" H 4100 2100 50  0000 C CNN
F 1 "Conn_01x01" H 4400 2100 50  0000 C CNN
F 2 "touchuc:progpin" H 3950 2100 50  0001 C CNN
F 3 "~" H 3950 2100 50  0001 C CNN
	1    3950 2100
	-1   0    0    -1  
$EndComp
$Comp
L conn:Conn_01x01 J7
U 1 1 5B2146F5
P 3950 2200
F 0 "J7" H 4100 2200 50  0000 C CNN
F 1 "Conn_01x01" H 4400 2200 50  0000 C CNN
F 2 "touchuc:progpin" H 3950 2200 50  0001 C CNN
F 3 "~" H 3950 2200 50  0001 C CNN
	1    3950 2200
	-1   0    0    -1  
$EndComp
Text Label 4650 2200 0    47   ~ 0
reset
Text Label 4650 2000 0    47   ~ 0
tipclk
Text Label 4650 1900 0    47   ~ 0
tpidata
$Comp
L device:R R1
U 1 1 5B215B61
P 6250 4800
F 0 "R1" H 6320 4846 50  0000 L CNN
F 1 "R" H 6320 4755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6180 4800 50  0001 C CNN
F 3 "" H 6250 4800 50  0001 C CNN
	1    6250 4800
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5B215C2E
P 6250 5200
F 0 "#PWR0106" H 6250 4950 50  0001 C CNN
F 1 "GND" H 6255 5027 50  0000 C CNN
F 2 "" H 6250 5200 50  0001 C CNN
F 3 "" H 6250 5200 50  0001 C CNN
	1    6250 5200
	1    0    0    -1  
$EndComp
$Comp
L device:LED D1
U 1 1 5B215D66
P 6250 4450
F 0 "D1" V 6288 4333 50  0000 R CNN
F 1 "LED" V 6197 4333 50  0000 R CNN
F 2 "LEDs:LED_1206_HandSoldering" H 6250 4450 50  0001 C CNN
F 3 "" H 6250 4450 50  0001 C CNN
	1    6250 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6250 4600 6250 4650
Wire Wire Line
	6250 4950 6250 5150
$Comp
L device:R R2
U 1 1 5B2169F7
P 6650 4800
F 0 "R2" H 6720 4846 50  0000 L CNN
F 1 "R" H 6720 4755 50  0000 L CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 6580 4800 50  0001 C CNN
F 3 "" H 6650 4800 50  0001 C CNN
	1    6650 4800
	1    0    0    -1  
$EndComp
$Comp
L device:LED D2
U 1 1 5B2169FE
P 6650 4450
F 0 "D2" V 6688 4333 50  0000 R CNN
F 1 "LED" V 6597 4333 50  0000 R CNN
F 2 "LEDs:LED_1206_HandSoldering" H 6650 4450 50  0001 C CNN
F 3 "" H 6650 4450 50  0001 C CNN
	1    6650 4450
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6650 4600 6650 4650
Wire Wire Line
	6650 4950 6650 5150
Wire Wire Line
	6650 5150 6250 5150
Connection ~ 6250 5150
Wire Wire Line
	6250 5150 6250 5200
$Comp
L device:C C1
U 1 1 5B2176C8
P 1950 1700
F 0 "C1" H 2065 1746 50  0000 L CNN
F 1 "C" H 2065 1655 50  0000 L CNN
F 2 "Capacitors_SMD:C_0603_HandSoldering" H 1988 1550 50  0001 C CNN
F 3 "" H 1950 1700 50  0001 C CNN
	1    1950 1700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1950 1550 1950 1450
Wire Wire Line
	1950 1450 1600 1450
Connection ~ 1600 1450
Wire Wire Line
	1950 1850 1950 1950
Wire Wire Line
	1950 1950 1600 1950
Connection ~ 1600 1950
Wire Wire Line
	4150 2100 4250 2100
Wire Wire Line
	4150 2000 4500 2000
Wire Wire Line
	4150 1900 4400 1900
Text Notes 1550 3950 0    118  ~ 0
Touch sensor
Text Notes 6150 3600 0    118  ~ 0
LEDs
Text GLabel 2450 4500 2    39   Output ~ 0
TOUCH
Text GLabel 6250 4100 1    47   Input ~ 0
LED1
Wire Wire Line
	6250 4100 6250 4300
Text GLabel 6650 4100 1    47   Input ~ 0
LED2
Wire Wire Line
	6650 4100 6650 4300
Text GLabel 4400 2350 3    47   Output ~ 0
LED1
Wire Wire Line
	4400 2350 4400 1900
Connection ~ 4400 1900
Wire Wire Line
	4400 1900 4900 1900
Text GLabel 4500 2350 3    47   Output ~ 0
LED2
Wire Wire Line
	4500 2350 4500 2000
Connection ~ 4500 2000
Wire Wire Line
	4500 2000 4900 2000
Text GLabel 4250 1600 1    47   Input ~ 0
TOUCH
Wire Wire Line
	4250 1600 4250 2100
Connection ~ 4250 2100
Wire Wire Line
	4250 2100 4900 2100
$Comp
L device:R 1k1
U 1 1 5B223115
P 2000 4500
F 0 "1k1" V 1793 4500 50  0000 C CNN
F 1 "R" V 1884 4500 50  0000 C CNN
F 2 "Resistors_SMD:R_0603_HandSoldering" V 1930 4500 50  0001 C CNN
F 3 "" H 2000 4500 50  0001 C CNN
	1    2000 4500
	0    1    1    0   
$EndComp
Wire Wire Line
	2150 4500 2450 4500
Text Notes 1700 5050 0    47   ~ 0
Using QTouchADC method\nSingle pin for charge+detect
$Comp
L conn:Conn_01x01 J3
U 1 1 5B2261EA
P 1200 4500
F 0 "J3" H 1120 4717 50  0000 C CNN
F 1 "Conn_01x01" H 1120 4626 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Angled_1x01_Pitch1.27mm" H 1200 4500 50  0001 C CNN
F 3 "~" H 1200 4500 50  0001 C CNN
	1    1200 4500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1400 4500 1850 4500
Text Label 1450 4500 0    47   ~ 0
sense
Wire Wire Line
	7350 1800 7550 1800
Wire Wire Line
	4150 2200 4900 2200
$Comp
L power:GND #PWR?
U 1 1 5B23016C
P 7400 2350
F 0 "#PWR?" H 7400 2100 50  0001 C CNN
F 1 "GND" H 7405 2177 50  0000 C CNN
F 2 "" H 7400 2350 50  0001 C CNN
F 3 "" H 7400 2350 50  0001 C CNN
	1    7400 2350
	1    0    0    -1  
$EndComp
Wire Wire Line
	7400 2350 7400 2300
Connection ~ 7400 2300
Wire Wire Line
	7400 2300 7300 2300
$EndSCHEMATC
