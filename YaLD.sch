EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
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
LIBS:7805_f
LIBS:YaLD-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 3
Title ""
Date "23 oct 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L VCC #PWR01
U 1 1 544999B0
P 1750 6450
F 0 "#PWR01" H 1750 6550 30  0001 C CNN
F 1 "VCC" H 1750 6550 30  0000 C CNN
F 2 "" H 1750 6450 60  0001 C CNN
F 3 "" H 1750 6450 60  0001 C CNN
	1    1750 6450
	1    0    0    -1  
$EndComp
$Comp
L 75LBC176 U1
U 1 1 544999B6
P 1950 6950
F 0 "U1" H 2300 7400 70  0000 C CNN
F 1 "75LBC176" H 2300 7300 60  0000 C CNN
F 2 "SMD_Packages:SOIC-8-W" H 1950 6950 60  0001 C CNN
F 3 "" H 1950 6950 60  0001 C CNN
	1    1950 6950
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR02
U 1 1 544999BC
P 1750 7600
F 0 "#PWR02" H 1750 7600 30  0001 C CNN
F 1 "GND" H 1750 7530 30  0001 C CNN
F 2 "" H 1750 7600 60  0001 C CNN
F 3 "" H 1750 7600 60  0001 C CNN
	1    1750 7600
	1    0    0    -1  
$EndComp
$Comp
L CP1 C3
U 1 1 544999C8
P 6900 4750
F 0 "C3" H 6950 4850 50  0000 L CNN
F 1 "4µ7" H 6950 4650 50  0000 L CNN
F 2 "Capacitors_SMD:c_elec_4x5.7" H 6900 4750 60  0001 C CNN
F 3 "" H 6900 4750 60  0001 C CNN
	1    6900 4750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR03
U 1 1 544999CE
P 6600 4800
F 0 "#PWR03" H 6600 4800 30  0001 C CNN
F 1 "GND" H 6600 4730 30  0001 C CNN
F 2 "" H 6600 4800 60  0001 C CNN
F 3 "" H 6600 4800 60  0001 C CNN
	1    6600 4800
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR04
U 1 1 544999D4
P 6900 3800
F 0 "#PWR04" H 6900 3900 30  0001 C CNN
F 1 "VCC" H 6900 3900 30  0000 C CNN
F 2 "" H 6900 3800 60  0001 C CNN
F 3 "" H 6900 3800 60  0001 C CNN
	1    6900 3800
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 544999DA
P 6900 4050
F 0 "R3" V 6980 4050 50  0000 C CNN
F 1 "100" V 6900 4050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6900 4050 60  0001 C CNN
F 3 "" H 6900 4050 60  0001 C CNN
	1    6900 4050
	-1   0    0    1   
$EndComp
$Comp
L CONN_3 K1
U 1 1 544999E0
P 6250 4550
F 0 "K1" V 6200 4550 50  0000 C CNN
F 1 "IR_RCV" V 6300 4550 40  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 6250 4550 60  0001 C CNN
F 3 "" H 6250 4550 60  0001 C CNN
	1    6250 4550
	-1   0    0    1   
$EndComp
$Comp
L CRYSTAL X1
U 1 1 544999F2
P 1950 2350
F 0 "X1" H 1950 2500 60  0000 C CNN
F 1 "16MHz" H 1950 2200 60  0000 C CNN
F 2 "Crystals:Crystal_HC49-SD_SMD" H 1950 2350 60  0001 C CNN
F 3 "" H 1950 2350 60  0001 C CNN
	1    1950 2350
	0    1    1    0   
$EndComp
$Comp
L R R1
U 1 1 54499A28
P 6150 6750
F 0 "R1" V 6230 6750 50  0000 C CNN
F 1 "1k5" V 6150 6750 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6150 6750 60  0001 C CNN
F 3 "" H 6150 6750 60  0001 C CNN
	1    6150 6750
	0    1    1    0   
$EndComp
$Comp
L R R2
U 1 1 54499A2E
P 6150 7050
F 0 "R2" V 6230 7050 50  0000 C CNN
F 1 "1k5" V 6150 7050 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 6150 7050 60  0001 C CNN
F 3 "" H 6150 7050 60  0001 C CNN
	1    6150 7050
	0    1    1    0   
$EndComp
$Comp
L LED D2
U 1 1 54499A34
P 5650 7050
F 0 "D2" H 5650 7150 50  0000 C CNN
F 1 "rot" H 5650 6950 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 5650 7050 60  0001 C CNN
F 3 "" H 5650 7050 60  0001 C CNN
	1    5650 7050
	-1   0    0    1   
$EndComp
$Comp
L LED D1
U 1 1 54499A3A
P 5650 6750
F 0 "D1" H 5650 6850 50  0000 C CNN
F 1 "grün" H 5650 6650 50  0000 C CNN
F 2 "LEDs:LED-3MM" H 5650 6750 60  0001 C CNN
F 3 "" H 5650 6750 60  0001 C CNN
	1    5650 6750
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR05
U 1 1 54499A46
P 6100 2300
F 0 "#PWR05" H 6100 2300 30  0001 C CNN
F 1 "GND" H 6100 2230 30  0001 C CNN
F 2 "" H 6100 2300 60  0001 C CNN
F 3 "" H 6100 2300 60  0001 C CNN
	1    6100 2300
	1    0    0    -1  
$EndComp
$Comp
L DIPS_10 SW1
U 1 1 54499A4C
P 5700 2200
F 0 "SW1" V 5150 2200 60  0000 C CNN
F 1 "DIPS_10" V 6250 2200 60  0000 C CNN
F 2 "Sockets_DIP:DIP-20__300_ELL" H 5700 2200 60  0001 C CNN
F 3 "" H 5700 2200 60  0001 C CNN
	1    5700 2200
	0    -1   -1   0   
$EndComp
$Comp
L R R5
U 1 1 54499A58
P 9200 2900
F 0 "R5" V 9280 2900 50  0000 C CNN
F 1 "1k8" V 9200 2900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9200 2900 60  0001 C CNN
F 3 "" H 9200 2900 60  0001 C CNN
	1    9200 2900
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 54499A5E
P 9000 2900
F 0 "R4" V 9080 2900 50  0000 C CNN
F 1 "1k8" V 9000 2900 50  0000 C CNN
F 2 "Resistors_SMD:R_0805_HandSoldering" H 9000 2900 60  0001 C CNN
F 3 "" H 9000 2900 60  0001 C CNN
	1    9000 2900
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR06
U 1 1 54499A64
P 10200 3650
F 0 "#PWR06" H 10200 3650 30  0001 C CNN
F 1 "GND" H 10200 3580 30  0001 C CNN
F 2 "" H 10200 3650 60  0001 C CNN
F 3 "" H 10200 3650 60  0001 C CNN
	1    10200 3650
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 54499A6A
P 10150 900
F 0 "#PWR07" H 10150 900 30  0001 C CNN
F 1 "GND" H 10150 830 30  0001 C CNN
F 2 "" H 10150 900 60  0001 C CNN
F 3 "" H 10150 900 60  0001 C CNN
	1    10150 900 
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR08
U 1 1 54499A76
P 10200 4550
F 0 "#PWR08" H 10200 4650 30  0001 C CNN
F 1 "VCC" H 10200 4650 30  0000 C CNN
F 2 "" H 10200 4550 60  0001 C CNN
F 3 "" H 10200 4550 60  0001 C CNN
	1    10200 4550
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR09
U 1 1 54499A7C
P 10150 1700
F 0 "#PWR09" H 10150 1800 30  0001 C CNN
F 1 "VCC" H 10150 1800 30  0000 C CNN
F 2 "" H 10150 1700 60  0001 C CNN
F 3 "" H 10150 1700 60  0001 C CNN
	1    10150 1700
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR010
U 1 1 54499A82
P 10000 4850
F 0 "#PWR010" H 10000 4850 30  0001 C CNN
F 1 "GND" H 10000 4780 30  0001 C CNN
F 2 "" H 10000 4850 60  0001 C CNN
F 3 "" H 10000 4850 60  0001 C CNN
	1    10000 4850
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR011
U 1 1 54499A88
P 9900 2200
F 0 "#PWR011" H 9900 2200 30  0001 C CNN
F 1 "GND" H 9900 2130 30  0001 C CNN
F 2 "" H 9900 2200 60  0001 C CNN
F 3 "" H 9900 2200 60  0001 C CNN
	1    9900 2200
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR012
U 1 1 54499A8E
P 8400 1850
F 0 "#PWR012" H 8400 1850 30  0001 C CNN
F 1 "GND" H 8400 1780 30  0001 C CNN
F 2 "" H 8400 1850 60  0001 C CNN
F 3 "" H 8400 1850 60  0001 C CNN
	1    8400 1850
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR013
U 1 1 54499AA6
P 8350 4950
F 0 "#PWR013" H 8350 5050 30  0001 C CNN
F 1 "VCC" H 8350 5050 30  0000 C CNN
F 2 "" H 8350 4950 60  0001 C CNN
F 3 "" H 8350 4950 60  0001 C CNN
	1    8350 4950
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR014
U 1 1 54499AAC
P 8400 2200
F 0 "#PWR014" H 8400 2300 30  0001 C CNN
F 1 "VCC" H 8400 2300 30  0000 C CNN
F 2 "" H 8400 2200 60  0001 C CNN
F 3 "" H 8400 2200 60  0001 C CNN
	1    8400 2200
	1    0    0    -1  
$EndComp
$Comp
L PCA9685 IC3
U 1 1 54499AB2
P 9200 4250
F 0 "IC3" H 8700 5050 60  0000 C CNN
F 1 "PCA9685" H 9550 3500 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-28_4.4x9.7mm_Pitch0.65mm" H 9200 4250 60  0001 C CNN
F 3 "" H 9200 4250 60  0001 C CNN
	1    9200 4250
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR015
U 1 1 54499ADC
P 900 2350
F 0 "#PWR015" H 900 2350 30  0001 C CNN
F 1 "GND" H 900 2280 30  0001 C CNN
F 2 "" H 900 2350 60  0001 C CNN
F 3 "" H 900 2350 60  0001 C CNN
	1    900  2350
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 54499AE2
P 1400 2650
F 0 "C2" H 1450 2750 50  0000 L CNN
F 1 "22p" H 1450 2550 50  0000 L CNN
F 2 "SMD_Packages:SMD-0805" H 1400 2650 60  0001 C CNN
F 3 "" H 1400 2650 60  0001 C CNN
	1    1400 2650
	0    -1   -1   0   
$EndComp
$Comp
L C C1
U 1 1 54499AE8
P 1400 2050
F 0 "C1" H 1450 2150 50  0000 L CNN
F 1 "22p" H 1450 1950 50  0000 L CNN
F 2 "SMD_Packages:SMD-0805" H 1400 2050 60  0001 C CNN
F 3 "" H 1400 2050 60  0001 C CNN
	1    1400 2050
	0    -1   -1   0   
$EndComp
$Sheet
S 10100 6100 700  950 
U 54499BE5
F0 "YalD_Connectors" 50
F1 "YalD_Connectors.sch" 50
$EndSheet
Text GLabel 3050 7200 2    60   Input ~ 0
DMXplus
Text GLabel 3050 7400 2    60   Input ~ 0
DMXminus
$Comp
L PCA9685 IC2
U 1 1 54497EA2
P 9200 1500
F 0 "IC2" H 8700 2300 60  0000 C CNN
F 1 "PCA9685" H 9550 750 60  0000 C CNN
F 2 "Housings_SSOP:TSSOP-28_4.4x9.7mm_Pitch0.65mm" H 9200 1500 60  0001 C CNN
F 3 "" H 9200 1500 60  0001 C CNN
	1    9200 1500
	-1   0    0    1   
$EndComp
Text GLabel 9850 1650 2    36   Input ~ 0
PWM0
Text GLabel 9850 1550 2    36   Input ~ 0
PWM1
Text GLabel 9850 1450 2    36   Input ~ 0
PWM2
Text GLabel 9850 1350 2    36   Input ~ 0
PWM3
Text GLabel 9850 1250 2    36   Input ~ 0
PWM4
Text GLabel 9850 1150 2    36   Input ~ 0
PWM5
Text GLabel 9850 1050 2    36   Input ~ 0
PWM6
Text GLabel 9850 950  2    36   Input ~ 0
PWM7
Text GLabel 8600 850  0    36   Input ~ 0
PWM8
Text GLabel 8600 950  0    36   Input ~ 0
PWM9
Text GLabel 8600 1050 0    36   Input ~ 0
PWM10
Text GLabel 8600 1150 0    36   Input ~ 0
PWM11
Text GLabel 8600 1250 0    36   Input ~ 0
PWM12
Text GLabel 8600 1350 0    36   Input ~ 0
PWM13
Text GLabel 8600 1450 0    36   Input ~ 0
PWM14
Text GLabel 8600 1550 0    36   Input ~ 0
PWM15
Text GLabel 9850 4100 2    36   Input ~ 0
PWM19
Text GLabel 9850 4000 2    36   Input ~ 0
PWM20
Text GLabel 9850 3900 2    36   Input ~ 0
PWM21
Text GLabel 9850 4400 2    36   Input ~ 0
PWM16
Text GLabel 9850 4300 2    36   Input ~ 0
PWM17
Text GLabel 9850 4200 2    36   Input ~ 0
PWM18
Text GLabel 9850 3800 2    36   Input ~ 0
PWM22
Text GLabel 9850 3700 2    36   Input ~ 0
PWM23
Text GLabel 8600 3900 0    36   Input ~ 0
PWM27
Text GLabel 8600 4000 0    36   Input ~ 0
PWM28
Text GLabel 8600 4100 0    36   Input ~ 0
PWM29
Text GLabel 8600 3600 0    36   Input ~ 0
PWM24
Text GLabel 8600 3700 0    36   Input ~ 0
PWM25
Text GLabel 8600 3800 0    36   Input ~ 0
PWM26
Text GLabel 8600 4200 0    36   Input ~ 0
PWM30
Text GLabel 8600 4300 0    36   Input ~ 0
PWM31
$Comp
L GND #PWR016
U 1 1 5449968A
P 8450 4550
F 0 "#PWR016" H 8450 4550 30  0001 C CNN
F 1 "GND" H 8450 4480 30  0001 C CNN
F 2 "" H 8450 4550 60  0001 C CNN
F 3 "" H 8450 4550 60  0001 C CNN
	1    8450 4550
	1    0    0    -1  
$EndComp
Text GLabel 4450 3650 2    43   Input ~ 0
SDA
Text GLabel 4450 3550 2    43   Input ~ 0
SCL
$Comp
L VCC #PWR017
U 1 1 5449B80A
P 9100 2550
F 0 "#PWR017" H 9100 2650 30  0001 C CNN
F 1 "VCC" H 9100 2650 30  0000 C CNN
F 2 "" H 9100 2550 60  0001 C CNN
F 3 "" H 9100 2550 60  0001 C CNN
	1    9100 2550
	1    0    0    -1  
$EndComp
Text GLabel 9450 3200 2    43   Input ~ 0
SDA
Text GLabel 9450 3300 2    43   Input ~ 0
SCL
$Comp
L ATMEGA32-A IC1
U 1 1 5449C335
P 3450 3450
F 0 "IC1" H 2650 5280 50  0000 L BNN
F 1 "ATMEGA32-A" H 3750 1550 50  0000 L BNN
F 2 "SMD_Packages:TQFP-44" H 2800 1600 50  0001 C CNN
F 3 "" H 3450 3450 60  0000 C CNN
	1    3450 3450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR018
U 1 1 5449CA7E
P 3300 1300
F 0 "#PWR018" H 3300 1400 30  0001 C CNN
F 1 "VCC" H 3300 1400 30  0000 C CNN
F 2 "" H 3300 1300 60  0001 C CNN
F 3 "" H 3300 1300 60  0001 C CNN
	1    3300 1300
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR019
U 1 1 5449CE5A
P 3450 5600
F 0 "#PWR019" H 3450 5600 30  0001 C CNN
F 1 "GND" H 3450 5530 30  0001 C CNN
F 2 "" H 3450 5600 60  0001 C CNN
F 3 "" H 3450 5600 60  0001 C CNN
	1    3450 5600
	1    0    0    -1  
$EndComp
Text GLabel 4500 3150 2    43   Input ~ 0
MOSI
Text GLabel 4500 3250 2    43   Input ~ 0
MISO
Text GLabel 4500 3350 2    43   Input ~ 0
SCK
Text GLabel 4450 4650 2    43   Input ~ 0
INT0
Text GLabel 4450 4750 2    43   Input ~ 0
INT1
Text GLabel 4450 4450 2    43   Input ~ 0
RXD
Text GLabel 4450 4550 2    43   Input ~ 0
TXD
Text GLabel 5400 6750 0    47   Input ~ 0
LEDgreen
Text GLabel 5400 7050 0    47   Input ~ 0
LEDred
$Comp
L VCC #PWR020
U 1 1 5449E7DB
P 6550 6900
F 0 "#PWR020" H 6550 7000 30  0001 C CNN
F 1 "VCC" H 6550 7000 30  0000 C CNN
F 2 "" H 6550 6900 60  0001 C CNN
F 3 "" H 6550 6900 60  0001 C CNN
	1    6550 6900
	1    0    0    -1  
$EndComp
Text GLabel 4450 2850 2    43   Input ~ 0
LEDgreen
Text GLabel 4450 2950 2    43   Input ~ 0
LEDred
Text GLabel 6650 4550 2    43   Input ~ 0
INT1
Text GLabel 1150 7300 0    43   Input ~ 0
RXD
Text GLabel 850  6900 0    43   Input ~ 0
INT0
Wire Wire Line
	7100 4750 7100 4450
Wire Wire Line
	7100 4450 6600 4450
Connection ~ 6600 4750
Wire Wire Line
	6600 4750 6700 4750
Wire Wire Line
	6600 4800 6600 4650
Connection ~ 1950 2650
Wire Wire Line
	1600 2650 2350 2650
Connection ~ 1950 2050
Wire Wire Line
	1600 2050 2350 2050
Wire Wire Line
	1200 2350 900  2350
Connection ~ 900  6900
Connection ~ 1200 2350
Wire Wire Line
	1200 2650 1200 2050
Wire Wire Line
	900  6500 900  7100
Wire Wire Line
	6650 4550 6600 4550
Wire Wire Line
	6900 4300 6900 4450
Connection ~ 6900 4450
Wire Wire Line
	8400 1750 8400 1850
Wire Wire Line
	2750 7400 3050 7400
Wire Wire Line
	10150 850  10150 900 
Wire Wire Line
	9850 850  10150 850 
Wire Wire Line
	9850 1850 9900 1850
Wire Wire Line
	9900 1850 9900 2200
Wire Wire Line
	9900 1950 9850 1950
Connection ~ 9900 1950
Wire Wire Line
	9900 2050 9850 2050
Connection ~ 9900 2050
Wire Wire Line
	9900 2150 9850 2150
Connection ~ 9900 2150
Wire Wire Line
	8400 1750 8600 1750
Wire Wire Line
	8550 1850 8600 1850
Wire Wire Line
	8550 1650 8550 1850
Connection ~ 8550 1750
Wire Wire Line
	8550 1650 8600 1650
Wire Wire Line
	10000 4850 10000 4800
Wire Wire Line
	10000 4800 9850 4800
Wire Wire Line
	9900 4700 9900 4900
Wire Wire Line
	9900 4700 9850 4700
Connection ~ 9900 4800
Wire Wire Line
	9900 4900 9850 4900
Wire Wire Line
	8450 4550 8450 4500
Wire Wire Line
	8450 4500 8600 4500
Wire Wire Line
	8600 4400 8550 4400
Wire Wire Line
	8550 4400 8550 4600
Connection ~ 8550 4500
Wire Wire Line
	8550 4600 8600 4600
Wire Wire Line
	9850 4500 9900 4500
Wire Wire Line
	9900 4500 9900 4600
Wire Wire Line
	9850 4600 10200 4600
Wire Wire Line
	10200 4600 10200 4550
Connection ~ 9900 4600
Wire Wire Line
	8600 4900 8550 4900
Wire Wire Line
	8550 4900 8550 5000
Wire Wire Line
	8550 5000 8350 5000
Wire Wire Line
	8350 5000 8350 4950
Wire Wire Line
	9850 3600 10200 3600
Wire Wire Line
	10200 3600 10200 3650
Wire Wire Line
	5900 1750 5950 1750
Wire Wire Line
	5950 1750 5950 2650
Wire Wire Line
	5950 2650 5900 2650
Wire Wire Line
	5950 1850 5900 1850
Connection ~ 5950 1850
Wire Wire Line
	5900 1950 5950 1950
Connection ~ 5950 1950
Wire Wire Line
	5950 2050 5900 2050
Connection ~ 5950 2050
Wire Wire Line
	5900 2150 6100 2150
Connection ~ 5950 2150
Wire Wire Line
	5900 2250 5950 2250
Connection ~ 5950 2250
Wire Wire Line
	5900 2350 5950 2350
Connection ~ 5950 2350
Wire Wire Line
	5900 2450 5950 2450
Connection ~ 5950 2450
Wire Wire Line
	5900 2550 5950 2550
Connection ~ 5950 2550
Wire Wire Line
	6100 2150 6100 2300
Wire Wire Line
	9850 1750 10150 1750
Wire Wire Line
	10150 1750 10150 1700
Wire Wire Line
	8400 2200 8400 2250
Wire Wire Line
	8400 2250 8550 2250
Wire Wire Line
	8550 2250 8550 2150
Wire Wire Line
	8550 2150 8600 2150
Wire Wire Line
	8600 1950 8300 1950
Wire Wire Line
	8300 1950 8300 4700
Wire Wire Line
	8300 4700 8600 4700
Wire Wire Line
	8600 4800 8250 4800
Wire Wire Line
	8250 4800 8250 2050
Wire Wire Line
	8250 2050 8600 2050
Wire Wire Line
	9000 2650 9000 2600
Wire Wire Line
	9000 2600 9200 2600
Wire Wire Line
	9200 2600 9200 2650
Wire Wire Line
	9100 2550 9100 2600
Connection ~ 9100 2600
Wire Wire Line
	9000 3150 9000 3200
Wire Wire Line
	8250 3200 9450 3200
Connection ~ 8250 3200
Connection ~ 9000 3200
Wire Wire Line
	9200 3150 9200 3300
Wire Wire Line
	8300 3300 9450 3300
Connection ~ 8300 3300
Connection ~ 9200 3300
Wire Wire Line
	2350 2050 2350 2150
Wire Wire Line
	2350 2150 2450 2150
Wire Wire Line
	2350 2650 2350 2550
Wire Wire Line
	2350 2550 2450 2550
Wire Wire Line
	3150 1450 3150 1400
Wire Wire Line
	3150 1400 3550 1400
Wire Wire Line
	3550 1400 3550 1450
Wire Wire Line
	3350 1450 3350 1400
Connection ~ 3350 1400
Wire Wire Line
	3250 1450 3250 1400
Connection ~ 3250 1400
Wire Wire Line
	3300 1400 3300 1300
Connection ~ 3300 1400
Wire Wire Line
	3300 5450 3300 5500
Wire Wire Line
	3300 5500 3600 5500
Wire Wire Line
	3600 5500 3600 5450
Wire Wire Line
	3500 5500 3500 5450
Connection ~ 3500 5500
Wire Wire Line
	3400 5500 3400 5450
Connection ~ 3400 5500
Wire Wire Line
	3450 5500 3450 5600
Connection ~ 3450 5500
Wire Wire Line
	4450 3150 4500 3150
Wire Wire Line
	4450 3250 4500 3250
Wire Wire Line
	4450 3350 4500 3350
Wire Wire Line
	5450 6750 5400 6750
Wire Wire Line
	5450 7050 5400 7050
Wire Wire Line
	5850 6750 5900 6750
Wire Wire Line
	5850 7050 5900 7050
Wire Wire Line
	6400 6750 6450 6750
Wire Wire Line
	6450 6750 6450 7050
Wire Wire Line
	6450 7050 6400 7050
Wire Wire Line
	6550 6900 6550 6950
Wire Wire Line
	6550 6950 6450 6950
Connection ~ 6450 6950
Wire Wire Line
	850  6900 900  6900
Wire Wire Line
	1150 6500 900  6500
Wire Wire Line
	900  7100 1150 7100
Text GLabel 1150 6800 0    43   Input ~ 0
TXD
$Sheet
S 9200 6100 700  950 
U 5449FCFE
F0 "YaLD_amp" 50
F1 "YaLD_amp.sch" 50
$EndSheet
Wire Wire Line
	1750 7550 1750 7600
Text GLabel 2450 1750 0    43   Input ~ 0
RESET
NoConn ~ 4450 3750
NoConn ~ 4450 3950
NoConn ~ 4450 4050
NoConn ~ 4450 4150
NoConn ~ 4450 4250
NoConn ~ 2450 2950
Wire Wire Line
	2750 7200 3050 7200
Text GLabel 5500 1750 0    47   Input ~ 0
DIP1
Text GLabel 5500 1850 0    47   Input ~ 0
DIP2
Text GLabel 5500 1950 0    47   Input ~ 0
DIP3
Text GLabel 5500 2050 0    47   Input ~ 0
DIP4
Text GLabel 5500 2150 0    47   Input ~ 0
DIP5
Text GLabel 5500 2250 0    47   Input ~ 0
DIP6
Text GLabel 5500 2350 0    47   Input ~ 0
DIP7
Text GLabel 5500 2450 0    47   Input ~ 0
DIP8
Text GLabel 5500 2550 0    47   Input ~ 0
DIP9
Text GLabel 5500 2650 0    47   Input ~ 0
DIP10
Text GLabel 4450 2450 2    47   Input ~ 0
DIP1
Text GLabel 4450 2350 2    47   Input ~ 0
DIP2
Text GLabel 4450 2250 2    47   Input ~ 0
DIP3
Text GLabel 4450 2150 2    47   Input ~ 0
DIP4
Text GLabel 4450 2050 2    47   Input ~ 0
DIP5
Text GLabel 4450 1950 2    47   Input ~ 0
DIP6
Text GLabel 4450 1850 2    47   Input ~ 0
DIP7
Text GLabel 4450 1750 2    47   Input ~ 0
DIP8
Text GLabel 4450 2650 2    47   Input ~ 0
DIP9
Text GLabel 4450 2750 2    47   Input ~ 0
DIP10
NoConn ~ 4450 5050
NoConn ~ 4450 5150
NoConn ~ 4450 4850
Wire Wire Line
	4450 4950 4650 4950
Wire Wire Line
	4650 4950 4650 5000
$Comp
L GND #PWR021
U 1 1 544EB0EF
P 4650 5000
F 0 "#PWR021" H 4650 5000 30  0001 C CNN
F 1 "GND" H 4650 4930 30  0001 C CNN
F 2 "" H 4650 5000 60  0000 C CNN
F 3 "" H 4650 5000 60  0000 C CNN
	1    4650 5000
	1    0    0    -1  
$EndComp
NoConn ~ 4450 3050
Text GLabel 4450 3850 2    43   Input ~ 0
DEBUG_TXD
$EndSCHEMATC
