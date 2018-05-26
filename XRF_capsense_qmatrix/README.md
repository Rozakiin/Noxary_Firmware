Using Hasu's Code as a base for XRF firmware, not in any real working order.

![XRF](https://i.imgur.com/ziqGxpA.png)

A fully customizable Topre TKL keyboard.

* Keyboard Maintainer: [Rozakiin](https://github.com/rozakiin)
* Hardware Supported: XRF PCB
  * rev0.1 
* Hardware Availability: [Noxary](https://www.instagram.com/noxaryco/)

Make example for this keyboard (after setting up your build environment):

    make -f Makefile.XRF clean
    make -f Makefile.XRF

See [build environment setup](https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/doc/build.md) then the [make instructions]
(https://github.com/tmk/tmk_keyboard/blob/master/tmk_core/doc/build.md#build-firmware) for more information.



Capacitive Sense - DIY Realforce 106s controller
================================================
This scans capacitive switch matrix using Atmel QMatrix method.


TODO
====
- Calibration
- Threshold
- Use sense value for analog input
- Test: voltage change, temperature change
- Low voltage power supply
- look into Topre capsense chip


Realforce 106s Matrix
=====================

My controller scans matrix with 16 drive lines and 8 sense lines.
Sense lines are multiplexed by ADC MUX of AT90USB1286.

Row: Burst(X)*16
Col: Sense(Y)*8
      0   1   2   3   4   5   6   7
      R14 R15 R16 R17 R18 R19 R20 R21
0 R22 58  44  30  16  1   2   90A 110
1 R23 60  46  31  17  3   4   112 113
2 R24 47  33  32  18  19  5   -   114
3 R25 49  48  34  20  21  6   131 115
4 R26 50  35  36  22  7   0B  0A  -
5 R27 61  51  37  23  8   9   117 116
6 R28 52  38  24  25  10  -   132 118
7 R29 54  53  39  26  11  -   133 119

8 R33 62  55  40  27  12  -   120 121
9 R34 57  56  41  28  13  -   122 123
A R35 64  42  43  -   15  14  90B -
B R36 79  83  81  76  75  -   -   -
C R37 84  89  -   86  85  80  -   -
D R38 99  93  92  91  90  -   -   -
E R39 104 98  97  96  100 95  125 124
F R40 108 103 102 106 101 105 -   126


Meanwhile original Topre controller scans with 8 drive lines and 16 sense lines.
Sense lines are multiplexed by two 74HC4051 analog multiplexers.

Row: Burst(X)*8
Col: Sense(Y)*16
    R22 R23 R24 R25 R26 R27 R28 R29     R33 R34 R35 R36 R37 R38 R39 R40
R14 58  60  47  49  50  61  52  54      62  57  64  79  84  99  104 108
R15 44  46  33  48  35  51  38  53      55  56  42  83  89  93  98  103
R16 30  31  32  34  36  37  24  39      40  41  43  81  -   92  97  102
R17 16  17  18  20  22  23  25  26      27  28  -   76  86  91  96  106
R18 1   3   19  21  7   8   10  11      12  13  15  75  85  90  100 101
R19 2   4   5   6   0B  9   -   -       -   -   14  -   80  -   95  105
R20 90A 112 -   131 0A  117 132 133     120 122 90B -   -   -   125 -
R21 110 113 114 115 -   116 118 119     121 123 -   -   -   -   124 126

Where Rxx means marking of resiter on PCB.



Memo
====
- Other drive lines than bursted one should be grounded to remove influence of capacitances not under test.
- Drive lines with resistor in series avoid divergence of sensing values. R=1KOhm
- Measured value of sense lines(Y) are electromagnetically infuenced depending on physical distance from drive lines(X)
    I had to place sensing compoenets(Csample and Rs) apart from drive lines(PC0-7) to remove EMS influence.
- Vaule changes
    - at startup: calculate threshold value of each node
        Boot magic - keys can be holded while keyboard is starting up
            - how holded keys are determined?
                - use average of all nodes as threashold
                - use last threashold valued stored in eeprom
                - error when many keys are stacked
    - long time change: >10s? tune threshold values (runtime recalibration)
    - short time change: recognized as human operation
    - key press - change in short time
        - threashold
            average(from long time data except for values while pressed)
        - hysteresis - threshold is changed when key is pressed
    - cross-talk on both adjacent X and Y line
        - cross-talk between adjacent X lines
            - removed by pulling other X lines down to *LOW* while the burst
            - HIZ causes cross-talk severely between adjacent X lines
        - cross-talk between adjacent Y lines
            - reduced much by sensing one of even/odd Y line group(0,2,4,6/1,3,5,7) at a time
            - both Ya and Yb are LOW when other line is measured
- Slow Scan
    - burst: 64 cycles, 6us per cycle = 380us/line (3us/200us with inline optimisation)
    - 16ms for 16X*8Y, 2 burst/sense cycles per line 09/21
    - if keys are pressed sense time becomes longer hence scan takes longer
    - how improve: fast burst pulse, short burst length, small Rsmp




Resources
=========
Burst length
    number of charge pulses in a burst measurement
    Increasing BL increases signal resolution and sensitivity.
Sampling Resistor
    discharges Sampling Capacitor(Cs) and controls discharge slope.
    Increasing Rsmp increases sensitivity.
X-Y
    X transmitter, burst, drive line
    Y receiver, sense line
    YA port: charge transfer control(top)
    YB port: ADC mux input(bottom)
self/mutual capacitance sense
    self
    mutual
ATMEL QTouch Library 
    supports GCC tool chain
    works with AVR with 2K flash(QTouch only)
QTouch
    self
    a button per two pins
QMatrix
    mutual
    http://www.atmel.com/products/TouchSolutions/bsw/qmatrix.aspx
QTouchADC
    QTouchADC only requires 1-series resistor and 1-pin per channel. No other external components are required.
    QTouchADC offers faster acquisition times with shorter burst lengths, resulting in lower power consumption.
    Also can be used promixity sensing.
    http://www.atmel.com/products/TouchSolutions/bsw/qtouchadc.aspx
Charge transfer
QTouch Composer
    extension for Atmel Studio 6


3.3 Tracking Base Capacitance Value
http://www.ti.com/lit/an/slaa379/slaa379.pdf
TI explains a patent expired method here. (not mutual sensing)

Calibrating
    compensate capacitance drift
http://www.embedded.com/design/prototyping-and-development/4008781/Getting-in-touch-with-capacitance-sensor-algorithms



Voltage of Cs
    http://forum.atmel.com/showthread.php?t=2023
    The terminal voltage that appears across the Cs capacitor has to be in the range of -50mV to -150mV. The terminal voltage should not exceed -250mV due to diode i/o conduction.



QTouch and QMatrix Sesitivity Tuning: http://www.atmel.com/images/qtan0062.pdf
    X-Y electrode design(capacitance)
    Bust length
    Sampling Capacitor Cs = 4.7-10nF
    Sampling Resistor Rsmp = 470K(220K-1M)Ohm
Sensor Design Guide
    http://www.atmel.com/images/doc10752.pdf
Promixity sensing
    http://www.atmel.com/Images/doc10760.pdf
    QTouch 180mm
    QTouchADC 250mm
    QMatrix 50mm

mTouch Theory
    http://ww1.microchip.com/downloads/en/DeviceDoc/93064A.pdf
Capacitive sensing library for Arduino
    http://playground.arduino.cc/Main/CapacitiveSensor?from=Main.CapSense

How Oscilloscope Probes Affect Your Measurement
    Input capacitance of Probes really affect circuit of capacitive sensor.
    http://www.tek.com/dl/51W_30013_0_MR_Letter_0.pdf


Analog Devices CapTouch
    http://www.analog.com/media/en/technical-documentation/data-sheets/AD7147.pdf

IBM patent: Keyboard multiple switch assembly 
    http://www.google.co.ug/patents/US4274752
    http://deskthority.net/f-o-r-s-a-l-e-f58/xwhatsit-s-grand-unified-ibm-capsense-usb-controller-thread-t7993-120.html#p165846


QMatrix API Flow -  QTouch Library
==================================
    qm_burst_length[]:  retains burst length for all channels
    measurement_period_ms

    touch_qm_sensor_init()
    touch_qm_sensor_config()
    touch_qm_sensor_calibrate()
    loop:
        touch_qm_sensor_dispatcher():   dispatches measure_complete_callback()
        touch_qm_sensor_start_aquisition()
        ... host app ...
