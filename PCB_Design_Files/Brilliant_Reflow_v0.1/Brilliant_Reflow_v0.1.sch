EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "Brilliant Reflow"
Date "2020-07-04"
Rev "01"
Comp ""
Comment1 "github.com/lkbrilliant"
Comment2 "@LKBrilliant"
Comment3 "Version: v0.1"
Comment4 "Project: Brilliant Reflow"
$EndDescr
$Comp
L MCU_ST_STM32F1:STM32F103C8Tx U3
U 1 1 5F00082E
P 4750 4100
F 0 "U3" H 4200 5575 50  0000 C CNN
F 1 "STM32F103C8T6" H 5200 2625 50  0000 C CNN
F 2 "Package_QFP:LQFP-48_7x7mm_P0.5mm" H 4150 2700 50  0001 R CNN
F 3 "http://www.st.com/st-web-ui/static/active/en/resource/technical/document/datasheet/CD00161566.pdf" H 4750 4100 50  0001 C CNN
	1    4750 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	6925 2975 6875 2975
Wire Wire Line
	6875 2975 6875 3075
Connection ~ 6875 3075
Wire Wire Line
	6875 3075 6925 3075
Wire Wire Line
	6875 3075 6875 3325
$Comp
L power:GND #PWR012
U 1 1 5F0065C7
P 6875 3325
F 0 "#PWR012" H 6875 3075 50  0001 C CNN
F 1 "GND" H 6875 3175 50  0000 C CNN
F 2 "" H 6875 3325 50  0001 C CNN
F 3 "" H 6875 3325 50  0001 C CNN
	1    6875 3325
	1    0    0    -1  
$EndComp
$Comp
L Brilliant_Reflow_Symbol:MAX6675 U2
U 1 1 5F0028A2
P 7225 3175
F 0 "U2" H 7075 3525 50  0000 C CNN
F 1 "MAX6675" H 7275 2925 50  0000 C CNN
F 2 "Package_SO:SO-8_3.9x4.9mm_P1.27mm" H 7225 2825 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/MAX6675.pdf" H 7225 3175 50  0001 C CNN
	1    7225 3175
	1    0    0    -1  
$EndComp
Text GLabel 7150 3900 2    50   Output ~ 0
BT1
Text GLabel 7150 4000 2    50   Output ~ 0
BT2
Text GLabel 7150 4100 2    50   Output ~ 0
BT3
Text GLabel 7150 4200 2    50   Output ~ 0
BT4
Text GLabel 7150 4300 2    50   Output ~ 0
BT5
Wire Wire Line
	7150 3900 7100 3900
Wire Wire Line
	7150 4000 7100 4000
Wire Wire Line
	7150 4100 7100 4100
Wire Wire Line
	7150 4200 7100 4200
Wire Wire Line
	7150 4300 7100 4300
Wire Wire Line
	6525 4150 6525 4100
$Comp
L power:GND #PWR016
U 1 1 5F007962
P 6525 4150
F 0 "#PWR016" H 6525 3900 50  0001 C CNN
F 1 "GND" H 6530 3977 50  0000 C CNN
F 2 "" H 6525 4150 50  0001 C CNN
F 3 "" H 6525 4150 50  0001 C CNN
	1    6525 4150
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR08
U 1 1 5F0063A8
P 4950 2500
F 0 "#PWR08" H 4950 2350 50  0001 C CNN
F 1 "+3V3" H 5075 2575 50  0000 C CNN
F 2 "" H 4950 2500 50  0001 C CNN
F 3 "" H 4950 2500 50  0001 C CNN
	1    4950 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	4950 2500 4950 2550
Wire Wire Line
	4950 2550 4850 2550
Wire Wire Line
	4550 2550 4550 2600
Wire Wire Line
	4650 2600 4650 2550
Connection ~ 4650 2550
Wire Wire Line
	4650 2550 4550 2550
Wire Wire Line
	4750 2600 4750 2550
Connection ~ 4750 2550
Wire Wire Line
	4750 2550 4650 2550
Wire Wire Line
	4850 2600 4850 2550
Connection ~ 4850 2550
Wire Wire Line
	4850 2550 4750 2550
Connection ~ 4950 2550
Wire Wire Line
	4950 2550 4950 2600
$Comp
L power:GND #PWR026
U 1 1 5F007FC4
P 4850 5725
F 0 "#PWR026" H 4850 5475 50  0001 C CNN
F 1 "GND" H 4700 5650 50  0000 C CNN
F 2 "" H 4850 5725 50  0001 C CNN
F 3 "" H 4850 5725 50  0001 C CNN
	1    4850 5725
	1    0    0    -1  
$EndComp
Wire Wire Line
	4850 5650 4750 5650
Wire Wire Line
	4550 5650 4550 5600
Connection ~ 4850 5650
Wire Wire Line
	4850 5650 4850 5600
Wire Wire Line
	4650 5600 4650 5650
Connection ~ 4650 5650
Wire Wire Line
	4650 5650 4550 5650
Wire Wire Line
	4750 5600 4750 5650
Connection ~ 4750 5650
Wire Wire Line
	4750 5650 4650 5650
Wire Wire Line
	4850 5650 4850 5725
$Comp
L Device:C_Small C3
U 1 1 5F00A89E
P 4425 2125
F 0 "C3" H 4517 2171 50  0000 L CNN
F 1 "100n" H 4517 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4425 2125 50  0001 C CNN
F 3 "~" H 4425 2125 50  0001 C CNN
	1    4425 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C4
U 1 1 5F00AFB1
P 4750 2125
F 0 "C4" H 4842 2171 50  0000 L CNN
F 1 "100n" H 4842 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4750 2125 50  0001 C CNN
F 3 "~" H 4750 2125 50  0001 C CNN
	1    4750 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C5
U 1 1 5F00B492
P 5075 2125
F 0 "C5" H 5167 2171 50  0000 L CNN
F 1 "100n" H 5167 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5075 2125 50  0001 C CNN
F 3 "~" H 5075 2125 50  0001 C CNN
	1    5075 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C1
U 1 1 5F00B7D0
P 3775 2125
F 0 "C1" H 3867 2171 50  0000 L CNN
F 1 "10u" H 3867 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3775 2125 50  0001 C CNN
F 3 "~" H 3775 2125 50  0001 C CNN
	1    3775 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C6
U 1 1 5F00C500
P 5400 2125
F 0 "C6" H 5492 2171 50  0000 L CNN
F 1 "100n" H 5492 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5400 2125 50  0001 C CNN
F 3 "~" H 5400 2125 50  0001 C CNN
	1    5400 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C2
U 1 1 5F00DAD2
P 4100 2125
F 0 "C2" H 4192 2171 50  0000 L CNN
F 1 "1u" H 4192 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 4100 2125 50  0001 C CNN
F 3 "~" H 4100 2125 50  0001 C CNN
	1    4100 2125
	1    0    0    -1  
$EndComp
$Comp
L Device:C_Small C7
U 1 1 5F00DFA4
P 5725 2125
F 0 "C7" H 5817 2171 50  0000 L CNN
F 1 "100n" H 5817 2080 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5725 2125 50  0001 C CNN
F 3 "~" H 5725 2125 50  0001 C CNN
	1    5725 2125
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR01
U 1 1 5F010FD1
P 3775 1925
F 0 "#PWR01" H 3775 1775 50  0001 C CNN
F 1 "+3V3" H 3900 2025 50  0000 C CNN
F 2 "" H 3775 1925 50  0001 C CNN
F 3 "" H 3775 1925 50  0001 C CNN
	1    3775 1925
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5F011780
P 3775 2325
F 0 "#PWR06" H 3775 2075 50  0001 C CNN
F 1 "GND" H 3925 2250 50  0000 C CNN
F 2 "" H 3775 2325 50  0001 C CNN
F 3 "" H 3775 2325 50  0001 C CNN
	1    3775 2325
	1    0    0    -1  
$EndComp
Wire Wire Line
	3775 1925 3775 1975
Wire Wire Line
	3775 1975 4100 1975
Wire Wire Line
	5725 1975 5725 2025
Connection ~ 3775 1975
Wire Wire Line
	3775 1975 3775 2025
Wire Wire Line
	5400 2025 5400 1975
Connection ~ 5400 1975
Wire Wire Line
	5400 1975 5725 1975
Wire Wire Line
	5075 2025 5075 1975
Connection ~ 5075 1975
Wire Wire Line
	5075 1975 5400 1975
Wire Wire Line
	4750 2025 4750 1975
Connection ~ 4750 1975
Wire Wire Line
	4750 1975 5075 1975
Wire Wire Line
	4425 2025 4425 1975
Connection ~ 4425 1975
Wire Wire Line
	4425 1975 4750 1975
Wire Wire Line
	4100 2025 4100 1975
Connection ~ 4100 1975
Wire Wire Line
	4100 1975 4425 1975
Wire Wire Line
	3775 2225 3775 2275
Wire Wire Line
	3775 2275 4100 2275
Wire Wire Line
	4100 2275 4100 2225
Connection ~ 3775 2275
Wire Wire Line
	3775 2275 3775 2325
Wire Wire Line
	4100 2275 4425 2275
Wire Wire Line
	4425 2275 4425 2225
Connection ~ 4100 2275
Wire Wire Line
	4750 2275 4750 2225
Wire Wire Line
	4425 2275 4750 2275
Connection ~ 4425 2275
Wire Wire Line
	4750 2275 5075 2275
Wire Wire Line
	5075 2275 5075 2225
Connection ~ 4750 2275
Wire Wire Line
	5075 2275 5400 2275
Wire Wire Line
	5400 2275 5400 2225
Connection ~ 5075 2275
Wire Wire Line
	5400 2275 5725 2275
Wire Wire Line
	5725 2275 5725 2225
Connection ~ 5400 2275
$Comp
L Device:C_Small C11
U 1 1 5F0218F0
P 5625 3250
F 0 "C11" H 5775 3200 50  0000 C CNN
F 1 "100n" H 5800 3275 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 5625 3250 50  0001 C CNN
F 3 "~" H 5625 3250 50  0001 C CNN
	1    5625 3250
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR013
U 1 1 5F0228B0
P 5625 3400
F 0 "#PWR013" H 5625 3150 50  0001 C CNN
F 1 "GND" H 5625 3250 50  0000 C CNN
F 2 "" H 5625 3400 50  0001 C CNN
F 3 "" H 5625 3400 50  0001 C CNN
	1    5625 3400
	1    0    0    -1  
$EndComp
$Comp
L Device:Crystal_Small Y1
U 1 1 5F028CB0
P 3925 3250
F 0 "Y1" V 3875 3100 50  0000 L CNN
F 1 "8M" V 3950 3075 50  0000 L CNN
F 2 "Crystal:Crystal_SMD_HC49-SD" H 3925 3250 50  0001 C CNN
F 3 "~" H 3925 3250 50  0001 C CNN
	1    3925 3250
	0    1    1    0   
$EndComp
$Comp
L Device:C_Small C10
U 1 1 5F02A4E9
P 3675 3125
F 0 "C10" V 3725 3250 50  0000 C CNN
F 1 "22n" V 3575 3125 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3675 3125 50  0001 C CNN
F 3 "~" H 3675 3125 50  0001 C CNN
	1    3675 3125
	0    -1   -1   0   
$EndComp
$Comp
L Device:C_Small C13
U 1 1 5F02A963
P 3675 3375
F 0 "C13" V 3725 3500 50  0000 C CNN
F 1 "22n" V 3575 3375 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 3675 3375 50  0001 C CNN
F 3 "~" H 3675 3375 50  0001 C CNN
	1    3675 3375
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3775 3125 3925 3125
Wire Wire Line
	3925 3125 3925 3150
Wire Wire Line
	3925 3125 4000 3125
Wire Wire Line
	4000 3125 4000 3200
Wire Wire Line
	4000 3200 4050 3200
Connection ~ 3925 3125
Wire Wire Line
	3775 3375 3925 3375
Wire Wire Line
	4000 3375 4000 3300
Wire Wire Line
	4000 3300 4050 3300
Wire Wire Line
	3925 3350 3925 3375
Connection ~ 3925 3375
Wire Wire Line
	3925 3375 4000 3375
Wire Wire Line
	3575 3125 3475 3125
Wire Wire Line
	3475 3375 3575 3375
$Comp
L Device:R_Small_US R1
U 1 1 5F047893
P 5900 3250
F 0 "R1" H 5775 3300 50  0000 C CNN
F 1 "10k" H 5775 3225 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 5900 3250 50  0001 C CNN
F 3 "~" H 5900 3250 50  0001 C CNN
	1    5900 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	5900 3400 5900 3350
Wire Wire Line
	5625 3350 5625 3400
$Comp
L power:GND #PWR014
U 1 1 5F0610C1
P 5900 3400
F 0 "#PWR014" H 5900 3150 50  0001 C CNN
F 1 "GND" H 5900 3250 50  0000 C CNN
F 2 "" H 5900 3400 50  0001 C CNN
F 3 "" H 5900 3400 50  0001 C CNN
	1    5900 3400
	1    0    0    -1  
$EndComp
Text GLabel 4000 2800 0    50   Input ~ 0
NRST
Text GLabel 4000 3000 0    50   Input ~ 0
BOOT0
Text GLabel 5625 3100 1    50   Input ~ 0
NRST
Text GLabel 5900 3100 1    50   Input ~ 0
BOOT0
Wire Wire Line
	5625 3100 5625 3150
Wire Wire Line
	5900 3100 5900 3150
NoConn ~ 4050 3500
NoConn ~ 4050 3600
NoConn ~ 4050 3700
Text GLabel 6150 3100 1    50   Input ~ 0
BOOT1
$Comp
L Device:R_Small_US R2
U 1 1 5F082C3D
P 6150 3250
F 0 "R2" H 6025 3300 50  0000 C CNN
F 1 "10k" H 6025 3225 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 6150 3250 50  0001 C CNN
F 3 "~" H 6150 3250 50  0001 C CNN
	1    6150 3250
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3400 6150 3350
$Comp
L power:GND #PWR015
U 1 1 5F082C44
P 6150 3400
F 0 "#PWR015" H 6150 3150 50  0001 C CNN
F 1 "GND" H 6150 3250 50  0000 C CNN
F 2 "" H 6150 3400 50  0001 C CNN
F 3 "" H 6150 3400 50  0001 C CNN
	1    6150 3400
	1    0    0    -1  
$EndComp
Wire Wire Line
	6150 3100 6150 3150
Text GLabel 5400 5200 2    50   BiDi ~ 0
SWDIO
Text GLabel 5400 5300 2    50   Input ~ 0
SWCLK
Wire Wire Line
	5400 5300 5350 5300
Wire Wire Line
	5400 5200 5350 5200
Text GLabel 7575 3275 2    50   Input ~ 0
SCK_T
Wire Wire Line
	7575 3175 7525 3175
Text GLabel 7575 3175 2    50   Input ~ 0
CS_T
Wire Wire Line
	7575 3275 7525 3275
Wire Wire Line
	5400 4600 5350 4600
Text GLabel 5400 4600 2    50   Output ~ 0
SDO
Wire Wire Line
	5400 4400 5350 4400
Text GLabel 5400 4400 2    50   Output ~ 0
SCK
Wire Wire Line
	5400 4200 5350 4200
Text GLabel 5400 4300 2    50   Output ~ 0
CS_D
Wire Wire Line
	4000 4100 4050 4100
Text GLabel 4000 4100 0    50   Input ~ 0
BOOT1
Wire Wire Line
	4000 2800 4050 2800
Wire Wire Line
	4000 3000 4050 3000
$Comp
L power:GND #PWR010
U 1 1 5F03ABCA
P 3400 3275
F 0 "#PWR010" H 3400 3025 50  0001 C CNN
F 1 "GND" H 3405 3102 50  0000 C CNN
F 2 "" H 3400 3275 50  0001 C CNN
F 3 "" H 3400 3275 50  0001 C CNN
	1    3400 3275
	1    0    0    -1  
$EndComp
Wire Wire Line
	3475 3125 3475 3250
Wire Wire Line
	3400 3250 3475 3250
Connection ~ 3475 3250
Wire Wire Line
	3475 3250 3475 3375
$Comp
L Connector_Generic:Conn_01x08 J4
U 1 1 5F0F2CFB
P 7000 5200
F 0 "J4" H 6950 5625 50  0000 L CNN
F 1 "Display" H 6875 4700 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x08_P2.54mm_Vertical" H 7000 5200 50  0001 C CNN
F 3 "~" H 7000 5200 50  0001 C CNN
	1    7000 5200
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:AMS1117-3.3 U1
U 1 1 5F0F49E5
P 6900 2025
F 0 "U1" H 6750 2150 50  0000 C CNN
F 1 "AMS1117" H 7075 1775 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223-3_TabPin2" H 6900 2225 50  0001 C CNN
F 3 "http://www.advanced-monolithic.com/pdf/ds1117.pdf" H 7000 1775 50  0001 C CNN
	1    6900 2025
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5F0F836F
P 7725 5000
F 0 "J3" H 7675 5225 50  0000 L CNN
F 1 "ST-Link" H 7575 4700 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7725 5000 50  0001 C CNN
F 3 "~" H 7725 5000 50  0001 C CNN
	1    7725 5000
	1    0    0    -1  
$EndComp
Text GLabel 7425 5200 0    50   BiDi ~ 0
SWDIO
Text GLabel 7425 5000 0    50   Output ~ 0
SWCLK
Wire Wire Line
	7425 5200 7525 5200
$Comp
L power:GND #PWR023
U 1 1 5F0FBA24
P 7475 5250
F 0 "#PWR023" H 7475 5000 50  0001 C CNN
F 1 "GND" H 7480 5077 50  0000 C CNN
F 2 "" H 7475 5250 50  0001 C CNN
F 3 "" H 7475 5250 50  0001 C CNN
	1    7475 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 5250 7475 5100
Wire Wire Line
	7475 5100 7525 5100
Wire Wire Line
	7525 5000 7425 5000
Wire Wire Line
	7475 4850 7475 4900
Wire Wire Line
	7475 4900 7525 4900
$Comp
L power:GND #PWR024
U 1 1 5F115D51
P 6675 5525
F 0 "#PWR024" H 6675 5275 50  0001 C CNN
F 1 "GND" H 6675 5375 50  0000 C CNN
F 2 "" H 6675 5525 50  0001 C CNN
F 3 "" H 6675 5525 50  0001 C CNN
	1    6675 5525
	1    0    0    -1  
$EndComp
Wire Wire Line
	6675 5500 6675 5525
Text GLabel 6700 5400 0    50   Input ~ 0
CS_D
Wire Wire Line
	6700 5400 6800 5400
Text GLabel 5400 4200 2    50   Output ~ 0
RST
Wire Wire Line
	5400 4100 5350 4100
Text GLabel 6700 5300 0    50   Input ~ 0
RST
Wire Wire Line
	6700 5300 6800 5300
Text GLabel 5400 4100 2    50   Output ~ 0
A0
Text GLabel 6700 5200 0    50   Input ~ 0
A0
Wire Wire Line
	6700 5200 6800 5200
Text GLabel 6700 5100 0    50   Input ~ 0
SDO
Text GLabel 6700 5000 0    50   Input ~ 0
SCK
Wire Wire Line
	6750 4850 6750 4900
Wire Wire Line
	6750 4900 6800 4900
Wire Wire Line
	6700 5000 6800 5000
Wire Wire Line
	6700 5100 6800 5100
$Comp
L power:+3V3 #PWR09
U 1 1 5F187669
P 6825 3025
F 0 "#PWR09" H 6825 2875 50  0001 C CNN
F 1 "+3V3" H 6800 3175 50  0000 C CNN
F 2 "" H 6825 3025 50  0001 C CNN
F 3 "" H 6825 3025 50  0001 C CNN
	1    6825 3025
	1    0    0    -1  
$EndComp
Wire Wire Line
	6825 3275 6925 3275
Wire Wire Line
	6825 3275 6825 3025
Text GLabel 4000 4300 0    50   Input ~ 0
BT2
Text GLabel 4000 4400 0    50   Input ~ 0
BT3
Text GLabel 4000 4500 0    50   Input ~ 0
BT4
Text GLabel 4000 4600 0    50   Input ~ 0
BT5
Text GLabel 4000 4200 0    50   Input ~ 0
BT1
Wire Wire Line
	4000 4300 4050 4300
Wire Wire Line
	4000 4400 4050 4400
Wire Wire Line
	4000 4500 4050 4500
Wire Wire Line
	4000 4600 4050 4600
Wire Wire Line
	3400 3275 3400 3250
$Comp
L Device:C_Small C12
U 1 1 5F238149
P 6675 3275
F 0 "C12" V 6725 3375 50  0000 C CNN
F 1 "100n" V 6800 3300 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6675 3275 50  0001 C CNN
F 3 "~" H 6675 3275 50  0001 C CNN
	1    6675 3275
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR011
U 1 1 5F2411C0
P 6525 3325
F 0 "#PWR011" H 6525 3075 50  0001 C CNN
F 1 "GND" H 6525 3175 50  0000 C CNN
F 2 "" H 6525 3325 50  0001 C CNN
F 3 "" H 6525 3325 50  0001 C CNN
	1    6525 3325
	1    0    0    -1  
$EndComp
Wire Wire Line
	6525 3325 6525 3275
Wire Wire Line
	6525 3275 6575 3275
Wire Wire Line
	6775 3275 6825 3275
Connection ~ 6825 3275
$Comp
L Device:C_Small C8
U 1 1 5F24ED00
P 6550 2175
F 0 "C8" H 6475 2250 50  0000 C CNN
F 1 "10u" H 6450 2325 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 6550 2175 50  0001 C CNN
F 3 "~" H 6550 2175 50  0001 C CNN
	1    6550 2175
	-1   0    0    1   
$EndComp
Wire Wire Line
	6550 2075 6550 2025
Wire Wire Line
	6550 2025 6600 2025
Wire Wire Line
	7250 2025 7250 2075
Wire Wire Line
	7200 2025 7250 2025
Wire Wire Line
	6550 2275 6550 2375
Wire Wire Line
	6550 2375 6900 2375
Wire Wire Line
	7250 2375 7250 2275
Wire Wire Line
	6900 2325 6900 2375
Connection ~ 6900 2375
Wire Wire Line
	6900 2375 7250 2375
$Comp
L power:GND #PWR07
U 1 1 5F268649
P 6900 2425
F 0 "#PWR07" H 6900 2175 50  0001 C CNN
F 1 "GND" H 6750 2350 50  0000 C CNN
F 2 "" H 6900 2425 50  0001 C CNN
F 3 "" H 6900 2425 50  0001 C CNN
	1    6900 2425
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 2425 6900 2375
$Comp
L power:+3V3 #PWR03
U 1 1 5F26DF3A
P 7250 1975
F 0 "#PWR03" H 7250 1825 50  0001 C CNN
F 1 "+3V3" H 7250 2125 50  0000 C CNN
F 2 "" H 7250 1975 50  0001 C CNN
F 3 "" H 7250 1975 50  0001 C CNN
	1    7250 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 1975 7250 2025
Connection ~ 7250 2025
$Comp
L Connector_Generic:Conn_01x02 J2
U 1 1 5F27377C
P 8825 5000
F 0 "J2" H 8875 4800 50  0000 R CNN
F 1 "POWER" H 8950 5100 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 8825 5000 50  0001 C CNN
F 3 "~" H 8825 5000 50  0001 C CNN
	1    8825 5000
	1    0    0    1   
$EndComp
Connection ~ 6550 2025
$Comp
L power:+5V #PWR02
U 1 1 5F280542
P 6550 1975
F 0 "#PWR02" H 6550 1825 50  0001 C CNN
F 1 "+5V" H 6550 2125 50  0000 C CNN
F 2 "" H 6550 1975 50  0001 C CNN
F 3 "" H 6550 1975 50  0001 C CNN
	1    6550 1975
	1    0    0    -1  
$EndComp
Wire Wire Line
	6550 1975 6550 2025
Wire Wire Line
	4000 4200 4050 4200
NoConn ~ 4050 3900
NoConn ~ 4050 4000
$Comp
L Device:C_Small C9
U 1 1 5F24F68C
P 7250 2175
F 0 "C9" H 7125 2150 50  0000 C CNN
F 1 "10u" H 7100 2225 50  0000 C CNN
F 2 "Capacitor_SMD:C_0603_1608Metric" H 7250 2175 50  0001 C CNN
F 3 "~" H 7250 2175 50  0001 C CNN
	1    7250 2175
	-1   0    0    1   
$EndComp
NoConn ~ 4050 4800
NoConn ~ 4050 4900
NoConn ~ 4050 5000
NoConn ~ 4050 5100
NoConn ~ 4050 5200
NoConn ~ 4050 5300
NoConn ~ 4050 5400
NoConn ~ 5350 5400
NoConn ~ 5350 5100
NoConn ~ 5350 5000
NoConn ~ 5350 3900
Wire Notes Line
	3300 1725 6275 1725
Wire Notes Line
	6275 1725 6275 5875
Wire Notes Line
	6275 5875 3300 5875
Wire Notes Line
	3300 5875 3300 1725
Wire Notes Line
	8075 1725 8075 2575
Wire Notes Line
	8075 2575 6425 2575
Wire Notes Line
	6425 2575 6425 1725
Wire Notes Line
	6425 4650 8975 4650
Wire Notes Line
	8975 4650 8975 5875
Wire Notes Line
	8975 5875 6425 5875
Wire Notes Line
	6425 5875 6425 4650
Wire Wire Line
	6525 4100 6575 4100
Wire Notes Line
	6425 3725 7525 3725
Wire Notes Line
	7525 3725 7525 4475
Wire Notes Line
	7525 4475 6425 4475
Wire Notes Line
	6425 4475 6425 3725
Wire Notes Line
	6425 1725 8075 1725
Wire Notes Line
	6425 2750 7875 2750
Wire Notes Line
	7875 2750 7875 3550
Wire Notes Line
	7875 3550 6425 3550
Wire Notes Line
	6425 3550 6425 2750
Text Notes 5400 1700 0    79   ~ 0
Microcontroller
Text Notes 6400 2725 0    79   ~ 0
Themocouple to Digital Converter
Text Notes 6400 1700 0    79   ~ 0
Voltage Regulator
Text Notes 6400 3700 0    79   ~ 0
Navigation Switch
Text Notes 6400 4625 0    79   ~ 0
Connectors
Text GLabel 4000 4700 0    50   Output ~ 0
SSR_T
Wire Wire Line
	4000 4700 4050 4700
$Comp
L Connector:Screw_Terminal_01x02 J1
U 1 1 5F5D2811
P 8350 4900
F 0 "J1" H 8300 5000 50  0000 L CNN
F 1 "Relay" H 8250 4700 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-2_P5.08mm" H 8350 4900 50  0001 C CNN
F 3 "~" H 8350 4900 50  0001 C CNN
	1    8350 4900
	1    0    0    -1  
$EndComp
Text GLabel 8100 5000 0    50   Output ~ 0
SSR
Wire Wire Line
	8100 4900 8150 4900
$Comp
L power:GND #PWR017
U 1 1 5F5DE894
P 8575 4325
F 0 "#PWR017" H 8575 4075 50  0001 C CNN
F 1 "GND" H 8450 4225 50  0000 C CNN
F 2 "" H 8575 4325 50  0001 C CNN
F 3 "" H 8575 4325 50  0001 C CNN
	1    8575 4325
	1    0    0    -1  
$EndComp
Text GLabel 6650 3175 0    50   Input ~ 0
T+
Wire Wire Line
	6650 3175 6925 3175
NoConn ~ 5350 4000
Wire Wire Line
	5400 4300 5350 4300
NoConn ~ 5350 4500
Text GLabel 5400 4700 2    50   Output ~ 0
CS_T
Text GLabel 5400 4800 2    50   Output ~ 0
SCK_T
Wire Wire Line
	5400 4700 5350 4700
Wire Wire Line
	5400 4800 5350 4800
Wire Wire Line
	5400 4900 5350 4900
Text GLabel 5400 4900 2    50   Input ~ 0
SDI
Text GLabel 7575 3075 2    50   Output ~ 0
SDI
Wire Wire Line
	7575 3075 7525 3075
Wire Wire Line
	6800 5600 6750 5600
Wire Wire Line
	6750 5600 6750 4900
Connection ~ 6750 4900
Wire Wire Line
	6675 5500 6800 5500
NoConn ~ 8225 5350
NoConn ~ 8225 5450
NoConn ~ 8225 5550
NoConn ~ 8225 5650
$Comp
L Brilliant_Reflow_Symbol:5_Way_Switch SW1
U 1 1 5F03B99C
P 6850 4100
F 0 "SW1" H 6750 4400 50  0000 C CNN
F 1 "5_Way_Switch" H 6875 3800 50  0000 C CNN
F 2 "Brilliant_Reflow:5_Way_Switch" H 7050 4100 50  0001 C CNN
F 3 "" H 7050 4100 50  0001 C CNN
	1    6850 4100
	1    0    0    -1  
$EndComp
$Comp
L Transistor_BJT:MMBTA42 Q1
U 1 1 5F07D54B
P 8475 4075
F 0 "Q1" H 8665 4121 50  0000 L CNN
F 1 "MMBT2222A" H 8665 4030 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-23" H 8675 4000 50  0001 L CIN
F 3 "" H 8475 4075 50  0001 L CNN
	1    8475 4075
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small_US R3
U 1 1 5F07E6C5
P 8125 4075
F 0 "R3" V 8050 4075 50  0000 C CNN
F 1 "10k" V 8200 4075 50  0000 C CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 8125 4075 50  0001 C CNN
F 3 "~" H 8125 4075 50  0001 C CNN
	1    8125 4075
	0    1    1    0   
$EndComp
Wire Wire Line
	8225 4075 8275 4075
Text GLabel 7975 4075 0    50   Input ~ 0
SSR_T
Wire Wire Line
	7975 4075 8025 4075
Wire Wire Line
	8575 4275 8575 4325
Wire Wire Line
	8100 5000 8150 5000
Text GLabel 8525 3825 0    50   Input ~ 0
SSR
Wire Wire Line
	8100 4850 8100 4900
$Comp
L power:+5V #PWR020
U 1 1 5F0C1D07
P 8100 4850
F 0 "#PWR020" H 8100 4700 50  0001 C CNN
F 1 "+5V" H 8025 4975 50  0000 C CNN
F 2 "" H 8100 4850 50  0001 C CNN
F 3 "" H 8100 4850 50  0001 C CNN
	1    8100 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR019
U 1 1 5F104C54
P 7475 4850
F 0 "#PWR019" H 7475 4700 50  0001 C CNN
F 1 "+3V3" H 7375 4975 50  0000 C CNN
F 2 "" H 7475 4850 50  0001 C CNN
F 3 "" H 7475 4850 50  0001 C CNN
	1    7475 4850
	1    0    0    -1  
$EndComp
$Comp
L power:+3V3 #PWR018
U 1 1 5F1426B7
P 6750 4850
F 0 "#PWR018" H 6750 4700 50  0001 C CNN
F 1 "+3V3" H 6650 4975 50  0000 C CNN
F 2 "" H 6750 4850 50  0001 C CNN
F 3 "" H 6750 4850 50  0001 C CNN
	1    6750 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8525 3825 8575 3825
Wire Wire Line
	8575 3825 8575 3875
Wire Notes Line
	7675 3725 7675 4475
Wire Notes Line
	7675 4475 9125 4475
Wire Notes Line
	9125 4475 9125 3725
Wire Notes Line
	9125 3725 7675 3725
Text Notes 7675 3700 0    79   ~ 0
SSR Switching Trans.
Wire Wire Line
	7800 2175 7800 2125
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5F369AC5
P 7800 2125
F 0 "#FLG01" H 7800 2200 50  0001 C CNN
F 1 "PWR_FLAG" H 7825 2275 50  0000 C CNN
F 2 "" H 7800 2125 50  0001 C CNN
F 3 "~" H 7800 2125 50  0001 C CNN
	1    7800 2125
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR05
U 1 1 5F369ABF
P 7800 2175
F 0 "#PWR05" H 7800 1925 50  0001 C CNN
F 1 "GND" H 7925 2100 50  0000 C CNN
F 2 "" H 7800 2175 50  0001 C CNN
F 3 "" H 7800 2175 50  0001 C CNN
	1    7800 2175
	1    0    0    -1  
$EndComp
Wire Wire Line
	7675 2150 7675 2200
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5F33C4EF
P 7675 2200
F 0 "#FLG02" H 7675 2275 50  0001 C CNN
F 1 "PWR_FLAG" H 7675 2350 50  0000 C CNN
F 2 "" H 7675 2200 50  0001 C CNN
F 3 "~" H 7675 2200 50  0001 C CNN
	1    7675 2200
	-1   0    0    1   
$EndComp
$Comp
L power:+5V #PWR04
U 1 1 5F33B852
P 7675 2150
F 0 "#PWR04" H 7675 2000 50  0001 C CNN
F 1 "+5V" H 7550 2225 50  0000 C CNN
F 2 "" H 7675 2150 50  0001 C CNN
F 3 "" H 7675 2150 50  0001 C CNN
	1    7675 2150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR021
U 1 1 5F05106A
P 8575 4850
F 0 "#PWR021" H 8575 4700 50  0001 C CNN
F 1 "+5V" H 8500 4975 50  0000 C CNN
F 2 "" H 8575 4850 50  0001 C CNN
F 3 "" H 8575 4850 50  0001 C CNN
	1    8575 4850
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR022
U 1 1 5F051472
P 8575 5050
F 0 "#PWR022" H 8575 4800 50  0001 C CNN
F 1 "GND" H 8575 4900 50  0000 C CNN
F 2 "" H 8575 5050 50  0001 C CNN
F 3 "" H 8575 5050 50  0001 C CNN
	1    8575 5050
	1    0    0    -1  
$EndComp
Wire Wire Line
	8575 4850 8575 4900
Wire Wire Line
	8575 4900 8625 4900
Wire Wire Line
	8625 5000 8575 5000
Wire Wire Line
	8575 5000 8575 5050
Wire Wire Line
	7475 5650 7525 5650
Wire Wire Line
	7475 5675 7475 5650
$Comp
L power:GND #PWR025
U 1 1 5F062587
P 7475 5675
F 0 "#PWR025" H 7475 5425 50  0001 C CNN
F 1 "GND" H 7475 5525 50  0000 C CNN
F 2 "" H 7475 5675 50  0001 C CNN
F 3 "" H 7475 5675 50  0001 C CNN
	1    7475 5675
	1    0    0    -1  
$EndComp
Wire Wire Line
	7475 5550 7525 5550
$Comp
L Connector:Screw_Terminal_01x02 J6
U 1 1 5F004935
P 7725 5550
F 0 "J6" H 7725 5650 50  0000 C CNN
F 1 "Thermocouple" H 7800 5350 50  0000 C CNN
F 2 "Brilliant_Reflow:TerminalBlock_7.62mm_2p" H 7725 5550 50  0001 C CNN
F 3 "~" H 7725 5550 50  0001 C CNN
	1    7725 5550
	1    0    0    -1  
$EndComp
Text GLabel 7475 5550 0    50   Output ~ 0
T+
$Comp
L Connector_Generic:Conn_01x04 J5
U 1 1 5F0C8C30
P 8425 5450
F 0 "J5" H 8375 5650 50  0000 L CNN
F 1 "DisplayMount" H 8125 5150 50  0000 L CNN
F 2 "Connector_PinSocket_2.54mm:PinSocket_1x04_P2.54mm_Vertical" H 8425 5450 50  0001 C CNN
F 3 "~" H 8425 5450 50  0001 C CNN
	1    8425 5450
	1    0    0    -1  
$EndComp
$EndSCHEMATC
