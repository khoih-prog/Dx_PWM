# Dx_PWM Library

[![arduino-library-badge](https://www.ardu-badge.com/badge/Dx_PWM.svg?)](https://www.ardu-badge.com/Dx_PWM)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/Dx_PWM.svg)](https://github.com/khoih-prog/Dx_PWM/releases)
[![GitHub](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/khoih-prog/Dx_PWM/blob/main/LICENSE)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/Dx_PWM.svg)](http://github.com/khoih-prog/Dx_PWM/issues)

<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>
<a href="https://profile-counter.glitch.me/khoih-prog-dx-pwm/count.svg"  title="Visitor count"><img src="https://profile-counter.glitch.me/khoih-prog-dx-pwm/count.svg" style="height: 30px;width: 200px;"></a>

---
---

## Table of Contents

* [Important Note for Arduino IDE](#Important-Note-for-Arduino-IDE)
* [Why do we need this Dx_PWM library](#why-do-we-need-this-Dx_PWM-library)
  * [Features](#features)
  * [Why using hardware-based PWM is better](#why-using-hardware-based-pwm-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [More useful Information](#more-useful-information)
  * [1. Documents](#1-documents)
  * [2. Timer TCB0-TCB4](#2-timer-tcb0-tcb4)
* [Usage](#usage)
  * [1. Create PWM Instance with Pin, Frequency and dutycycle](#1-Create-PWM-Instance-with-Pin-Frequency-and-dutycycle)
  * [2. Initialize PWM Instance](#2-Initialize-PWM-Instance)
  * [3. Set or change PWM frequency or dutyCycle](#3-set-or-change-PWM-frequency-or-dutyCycle)
  * [4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation](#4-Set-or-change-PWM-frequency-and-dutyCycle-manually-and-efficiently-in-waveform-creation)
* [Examples](#examples)
  * [ 1. PWM_Basic](examples/PWM_Basic)
  * [ 2. PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle) 
  * [ 3. PWM_DynamicDutyCycle_Int](examples/PWM_DynamicDutyCycle_Int)
  * [ 4. PWM_DynamicFreq](examples/PWM_DynamicFreq)
  * [ 5. PWM_Multi](examples/PWM_Multi)
  * [ 6. PWM_MultiChannel](examples/PWM_MultiChannel)
  * [ 7. PWM_Waveform](examples/PWM_Waveform)
* [Example PWM_Multi](#example-PWM_Multi)
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. PWM_DynamicDutyCycle on AVR128DB](#1-PWM_DynamicDutyCycle-on-AVR128DB)
  * [2. PWM_Multi on AVR128DB](#2-PWM_Multi-on-AVR128DB)
  * [3. PWM_DynamicFreq on AVR128DB](#3-PWM_DynamicFreq-on-AVR128DB)
  * [4. PWM_Waveform on AVR128DB](#4-PWM_Waveform-on-AVR128DB)
  * [5. PWM_Waveform on AVR128DA](#5-PWM_Waveform-on-AVR128DA)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)


---
---

### Important Note for Arduino IDE

With some Arduino IDE versions, such as v1.8.19, upload directly via USB to some boards, such as `AVR_CuriosityNano3217` can't be done without `unknown-to-me` fix. We'll get the following error when uploading

```
avrdude: Version 6.3-20201216
         Copyright (c) 2000-2005 Brian Dean, http://www.bdmicro.com/
         Copyright (c) 2007-2014 Joerg Wunsch

         System wide configuration file is "/home/kh/.arduino15/packages/megaTinyCore/hardware/megaavr/2.5.11/avrdude.conf"
         User configuration file is "/home/kh/.avrduderc"
         User configuration file does not exist or is not a regular file, skipping

         Using Port                    : usb
         Using Programmer              : curiosity_updi
avrdude: usbdev_open(): Found nEDBG CMSIS-DAP, serno: MCHP3333021800000998
avrdude: usbdev_open(): WARNING: failed to set configuration 1: Device or resource busy
avrdude: Found CMSIS-DAP compliant device, using EDBG protocol
avrdude: usbdev_send(): wrote -5 out of 912 bytes, err = Input/output error
avrdude: jtag3_edbg_prepare(): failed to send command to serial port

avrdude done.  Thank you.

the selected serial port 
 does not exist or your board is not connected
```

We can use drag-and-drop method to `drag-and-drop` the compiled **hex** file to `CURIOSITY` virtual drive. 

If `success`, The LED blinks **slowly** for 2 sec, or **rapidly** for 2 sec if `failure`


For example, to run [Change_Interval example](https://github.com/khoih-prog/Dx_PWM/tree/main/examples/Change_Interval), use Arduino IDE to compile, and get the `Change_Interval.ino.hex` file. For Ubuntu Linux, the file is stored in directory `/tmp/arduino_build_xxxxxx`


<p align="center">
    <img src="https://github.com/khoih-prog/Dx_PWM/blob/main/pics/Change_Interval.png">
</p>


After drag-and-drop the `Change_Interval.ino.hex` into `CURIOSITY` virtual drive, the code will run immediately if successfully loaded (LED blinks **slowly**)


<p align="center">
    <img src="https://github.com/khoih-prog/Dx_PWM/blob/main/pics/CURIOSITY_drive.png">
</p>


---
---

### Why do we need this [Dx_PWM library](https://github.com/khoih-prog/Dx_PWM)

### Features

This hardware-based PWM library, a wrapper and enhancement around `DxCore analogWrite()` code, enables you to use Hardware-PWM on **AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore**, to create and output PWM. These purely hardware-based PWM channels can generate very high PWM frequencies, depending on CPU clock and acceptable accuracy, due to 8 or 16-bit PWM / Timer registers.

This library is using the **same or similar functions** as other FastPWM libraries, as follows, to enable you to **port your PWM code easily between platforms**

 1. [**RP2040_PWM**](https://github.com/khoih-prog/RP2040_PWM)
 2. [**AVR_PWM**](https://github.com/khoih-prog/AVR_PWM)
 3. [**megaAVR_PWM**](https://github.com/khoih-prog/megaAVR_PWM)
 4. [**ESP32_FastPWM**](https://github.com/khoih-prog/ESP32_FastPWM)
 5. [**SAMD_PWM**](https://github.com/khoih-prog/SAMD_PWM)
 6. [**SAMDUE_PWM**](https://github.com/khoih-prog/SAMDUE_PWM)
 7. [**nRF52_PWM**](https://github.com/khoih-prog/nRF52_PWM)
 8. [**Teensy_PWM**](https://github.com/khoih-prog/Teensy_PWM)
 9. [**ATtiny_PWM**](https://github.com/khoih-prog/ATtiny_PWM)
10. [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM)
11. [**Portenta_H7_PWM**](https://github.com/khoih-prog/Portenta_H7_PWM)
12. [**MBED_RP2040_PWM**](https://github.com/khoih-prog/MBED_RP2040_PWM)
13. [**nRF52_MBED_PWM**](https://github.com/khoih-prog/nRF52_MBED_PWM)
14. [**STM32_PWM**](https://github.com/khoih-prog/STM32_PWM)

---

The most important feature is they're purely hardware-based PWM channels. Therefore, their operations are **not blocked by bad-behaving software functions / tasks**.

This important feature is absolutely necessary for mission-critical tasks. These hardware PWM-channels, still work even if other software functions are blocking. Moreover, they are much more precise (certainly depending on clock frequency accuracy) than other software timers using millis() or micros(). That's necessary if you need to control external systems (Servo, etc.) requiring better accuracy.

New efficient `setPWM_manual()` function enables waveform creation using PWM.

The [**PWM_Multi**](examples/PWM_Multi) example will demonstrate the usage of multichannel PWM using multiple Hardware-PWM blocks (slices). The 4 independent Hardware-PWM channels are used **to control 4 different PWM outputs**, with totally independent frequencies and dutycycles on `Arduino Mega`.

Being hardware-based PWM, their executions are not blocked by bad-behaving functions / tasks, such as connecting to WiFi, Internet or Blynk services.

This non-being-blocked important feature is absolutely necessary for mission-critical tasks.


---

#### Why using hardware-based PWM is better

Imagine you have a system with a **mission-critical** function, controlling a robot or doing something much more important. You normally use a software timer to poll, or even place the function in loop(). But what if another function is **blocking** the loop() or setup().

So your function **might not be executed, and the result would be disastrous.**

You'd prefer to have your function called, no matter what happening with other functions (busy loop, bug, etc.).

The correct choice is to use `hardware-based PWM`.

These hardware-based PWM channels still work even if other software functions are blocking. Moreover, they are much more **precise** (certainly depending on clock frequency accuracy) than other software-based PWMs, using millis() or micros().

Functions using normal software-based PWMs, relying on loop() and calling millis(), won't work if the loop() or setup() is blocked by certain operation. For example, certain function is blocking while it's connecting to WiFi or some services.


---

### Currently supported Boards

- **AVRDA-based boards (AVR128DA, AVR64DA, AVR32DA, etc.) using DxCore**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_PWM/blob/main/pics/Curiosity_AVR128DA48.png">
</p>


- **AVRDB-based boards (AVR128DB, AVR64DB, AVR32DB, etc.) using DxCore**

<p align="center">
    <img src="https://github.com/khoih-prog/Dx_PWM/blob/main/pics/Curiosity_AVR128DB48.png">
</p>


---
---

## Prerequisites

1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
2. [`SpenceKonde DxCore core 1.4.10+`](https://github.com/SpenceKonde/DxCore) for Arduino AVRDx boards.  [![GitHub release](https://img.shields.io/github/release/SpenceKonde/DxCore.svg)](https://github.com/SpenceKonde/DxCore/releases/latest). Follow [**DxCore Installation**](https://github.com/SpenceKonde/DxCore/blob/main/Installation.md).
 
 
---
---

## Installation

### Use Arduino Library Manager

The best and easiest way is to use `Arduino Library Manager`. Search for [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM), then select / install the latest version.
You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/Dx_PWM.svg?)](https://www.ardu-badge.com/Dx_PWM) for more detailed instructions.

### Manual Install

Another way to install is to:

1. Navigate to [**Dx_PWM**](https://github.com/khoih-prog/Dx_PWM) page.
2. Download the latest release `Dx_PWM-main.zip`.
3. Extract the zip file to `Dx_PWM-main` directory 
4. Copy whole `Dx_PWM-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**Dx_PWM** library](https://registry.platformio.org/libraries/khoih-prog/Dx_PWM) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/Dx_PWM/installation). Search for **Dx_PWM** in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

## More useful Information

### 1. Documents

1. [Arduino 101: Timers and Interrupts](https://www.robotshop.com/community/forum/t/arduino-101-timers-and-interrupts/13072)
2. [Getting Started with Timer/Counter Type B (TCB)](https://ww1.microchip.com/downloads/aemDocuments/documents/MCU08/ApplicationNotes/ApplicationNotes/TB3214-Getting-Started-with-TCB-DS90003214.pdf)
3. [DXCore README.md](https://github.com/SpenceKonde/DxCore/blob/master/README.md)
4. [AVR128DA48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DA48-Curiosity-Nano-UG-DS50002971B.pdf)
5. [AVR128DB48-Curiosity-Nano-Hardware-User Guide](https://ww1.microchip.com/downloads/en/DeviceDoc/AVR128DB48-Curiosity-Nano-HW-UserG-DS50003037A.pdf)



### 2. Timer TCB0-TCB4

TCB0-TCB4 are 16-bit timers

The AVRDx boards with 14, 20, 28 or 32 pins, such as `AVRDx28`, will have only 3 TCB timers, (TCB0-TCB2)

The AVRDx with 48 pins, such as `Curiosity Nano AVRDA48`, `Curiosity Nano AVRDB48`, will have 4 TCB timers, (TCB0-TCB3)

The AVRDx with 64 pins, such as `AVRDA64`, `AVRDB64`, will have 5 TCB timers, (TCB0-TCB4)

The number of TCB timers will be automatically configured by the library.

---
---

## Usage

Before using any PWM `Timer` and `channel`, you have to make sure the `Timer` and `channel` has not been used by any other purpose.

#### 1. Create PWM Instance with Pin, Frequency and dutycycle

```cpp
Dx_PWM* PWM_Instance;

PWM_Instance = new Dx_PWM(PWM_Pins, freq, dutyCycle);
```

#### 2. Initialize PWM Instance

```cpp
if (PWM_Instance)
{
  PWM_Instance->setPWM();
}
```

#### 3. Set or change PWM frequency or dutyCycle

To use `float new_dutyCycle`

```cpp
PWM_Instance->setPWM(PWM_Pins, new_frequency, new_dutyCycle);
```

such as 

```cpp
dutyCycle = 10.0f;
  
Serial.print(F("Change PWM DutyCycle to ")); Serial.println(dutyCycle);
PWM_Instance->setPWM(pinToUse, frequency, dutyCycle);
```

---

To use `uint32_t new_dutyCycle` = `(real_dutyCycle * 65536) / 100`


```cpp
PWM_Instance->setPWM_Int(PWM_Pins, new_frequency, new_dutyCycle);
```

such as for `real_dutyCycle = 50%`

```cpp
// 50% dutyCycle = (real_dutyCycle * 65535) / 100
dutyCycle = 32767;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

for `real_dutyCycle = 50%`

```cpp
// 20% dutyCycle = (real_dutyCycle * 65535) / 100
dutyCycle = 13107;

Serial.print(F("Change PWM DutyCycle to (%) "));
Serial.println((float) dutyCycle * 100 / 65536);
PWM_Instance->setPWM_Int(pinToUse, frequency, dutyCycle);
```

#### 4. Set or change PWM frequency and dutyCycle manually and efficiently in waveform creation

Function prototype

```cpp
bool setPWM_manual(const uint8_t& pin, const uint16_t& DCValue);
```

Need to call only once for each pin


```cpp
PWM_Instance->setPWM(PWM_Pins, frequency, dutyCycle);
```

after that, if just changing `dutyCycle` / `level`, use 

```cpp
PWM_Instance->setPWM_manual(PWM_Pins, new_level);
```


---
---

### Examples: 

 1. [PWM_Basic](examples/PWM_Basic)
 2. [PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle)
 3. [PWM_DynamicDutyCycle_Int](examples/PWM_DynamicDutyCycle_Int)
 4. [PWM_DynamicFreq](examples/PWM_DynamicFreq)
 5. [PWM_Multi](examples/PWM_Multi)
 6. [PWM_MultiChannel](examples/PWM_MultiChannel)
 7. [PWM_Waveform](examples/PWM_Waveform)

 
---
---

### Example [PWM_Multi](examples/PWM_Multi)


https://github.com/khoih-prog/Dx_PWM/blob/84687f4fae4d5cae1e51d7d502575d523e32aae6/examples/PWM_Multi/PWM_Multi.ino#L11-L135


---
---

### Debug Terminal Output Samples

### 1. PWM_DynamicDutyCycle on AVR128DB

The following is the sample terminal output when running example [PWM_DynamicDutyCycle](examples/PWM_DynamicDutyCycle) on **AVR128DB** using `DxCore`, to demonstrate the ability to provide high PWM frequencies and ability to change DutyCycle `on-the-fly`.


```
Starting PWM_DynamicDutyCycle on AVR128DB
Dx_PWM v1.0.0
[PWM] Dx_PWM: freq = 5000.00
[PWM] Dx_PWM: _dutycycle = 0
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58981
[PWM] setPWM_Int: pin = 39 , _dutycycle = 58981 , old frequency = 5000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 58981
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 4800
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 75 , _actualFrequency = 5000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 67 , DC % = 90.67
=====================================================================================
Actual data: pin = 39, PWM DC = 78642.67, PWMPeriod = 75.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 20.00
[PWM] setPWM: _dutycycle = 13107
[PWM] setPWM_Int: pin = 39 , _dutycycle = 13107 , old frequency = 5000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 13107
[PWM] setPWM_Int: TIMERB, dutycycle = 15 , DC % = 21.33
=====================================================================================
Actual data: pin = 39, PWM DC = 17477.33, PWMPeriod = 75.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58981
[PWM] setPWM_Int: pin = 39 , _dutycycle = 58981 , old frequency = 5000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 58981
[PWM] setPWM_Int: TIMERB, dutycycle = 67 , DC % = 90.67
=====================================================================================
Actual data: pin = 39, PWM DC = 78642.67, PWMPeriod = 75.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 20.00
[PWM] setPWM: _dutycycle = 13107
[PWM] setPWM_Int: pin = 39 , _dutycycle = 13107 , old frequency = 5000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 13107
[PWM] setPWM_Int: TIMERB, dutycycle = 15 , DC % = 21.33
=====================================================================================
Actual data: pin = 39, PWM DC = 17477.33, PWMPeriod = 75.00, PWM Freq (Hz) = 5000.0000
=====================================================================================
Change PWM DutyCycle to 90.00
[PWM] setPWM: _dutycycle = 58981
[PWM] setPWM_Int: pin = 39 , _dutycycle = 58981 , old frequency = 5000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 58981
[PWM] setPWM_Int: TIMERB, dutycycle = 67 , DC % = 90.67
=====================================================================================
Actual data: pin = 39, PWM DC = 78642.67, PWMPeriod = 75.00, PWM Freq (Hz) = 5000.0000
=====================================================================================

```

---

### 2. PWM_Multi on AVR128DB

The following is the sample terminal output when running example [**PWM_Multi**](examples/PWM_Multi) on **AVR128DB**, to demonstrate the ability to provide high PWM frequencies on multiple `PWM-capable` pins.


```
Starting PWM_Multi on AVR128DB
Dx_PWM v1.0.0
[PWM] Dx_PWM: freq = 2000.00
[PWM] Dx_PWM: _dutycycle = 13107
[PWM] setPWM_Int: pin = 10 , _dutycycle = 13107 , old frequency = 2000.00
[PWM] setPeriod_TimerA1: F_CPU = 24000000 , microseconds = 500 , TCA_Freq_mult = 1.00 , beginning pwmPeriod =  1500
[PWM] setPeriod_TimerA1: CLKSEL_DIV64
[PWM] setPeriod_TimerA1: pwmPeriod = 188 , _actualFrequency = 1994.00
[PWM] setPWM_Int: TIMER_TCA1, _dutycycle = 38
[PWM] Dx_PWM: freq = 3000.00
[PWM] Dx_PWM: _dutycycle = 19660
[PWM] setPWM_Int: pin = 14 , _dutycycle = 19660 , old frequency = 3000.00
[PWM] setPeriod_TimerA0: F_CPU = 24000000 , microseconds = 333 , TCA_Freq_mult = 1.00
[PWM] setPeriod_TimerA0: CLKSEL_DIV64
[PWM] setPeriod_TimerA0: pwmPeriod = 125 , _actualFrequency = 3000.00
[PWM] setPWM_Int 4: _dutycycle = 38
[PWM] Dx_PWM: freq = 4000.00
[PWM] Dx_PWM: _dutycycle = 26214
[PWM] setPWM_Int: pin = 38 , _dutycycle = 26214 , old frequency = 4000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 26214
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 6000
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 93 , _actualFrequency = 4000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 37 , DC % = 40.86
[PWM] Dx_PWM: freq = 8000.00
[PWM] Dx_PWM: _dutycycle = 52428
[PWM] setPWM_Int: pin = 39 , _dutycycle = 52428 , old frequency = 8000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 52428
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 3000
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 46 , _actualFrequency = 8000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 36 , DC % = 80.43
=====================================================================================
Index	Pin	PWM_freq	DutyCycle	Actual Freq
=====================================================================================
0	10	2000.00		20.00		1994.0000
1	14	3000.00		30.00		3000.0000
2	38	4000.00		40.00		4000.0000
3	39	8000.00		80.00		8000.0000
=====================================================================================
Actual data: pin = 10, PWM DC = 20.74, PWMPeriod = 188.00, PWM Freq (Hz) = 1994.0000
=====================================================================================
=====================================================================================
Actual data: pin = 14, PWM DC = 31.20, PWMPeriod = 125.00, PWM Freq (Hz) = 3000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 38, PWM DC = 28188.17, PWMPeriod = 93.00, PWM Freq (Hz) = 4000.0000
=====================================================================================
=====================================================================================
Actual data: pin = 39, PWM DC = 113976.09, PWMPeriod = 46.00, PWM Freq (Hz) = 8000.0000
=====================================================================================
```

---

### 3. PWM_DynamicFreq on AVR128DB

The following is the sample terminal output when running example [**PWM_DynamicFreq**](examples/PWM_DynamicFreq) on **AVR128DB**, to demonstrate the ability to change dynamically PWM frequencies.

```
Starting PWM_DynamicFreq on AVR128DB
Dx_PWM v1.0.0
[PWM] Dx_PWM: freq = 10000.00
[PWM] Dx_PWM: _dutycycle = 32767
Stop here forever
Starting PWM_DynamicFreq on AVR128DB
Dx_PWM v1.0.0
[PWM] Dx_PWM: freq = 10000.00
[PWM] Dx_PWM: _dutycycle = 32767
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32767
[PWM] setPWM_Int: pin = 39 , _dutycycle = 32767 , new frequency = 20000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 32767
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 1200
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 18 , _actualFrequency = 20000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 8 , DC % = 50.00
=====================================================================================
Actual data: pin = 39, PWM DC = 182044.43, PWMPeriod = 18.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
Change PWM Freq to 10000.00
[PWM] setPWM: _dutycycle = 32767
[PWM] setPWM_Int: pin = 39 , _dutycycle = 32767 , new frequency = 10000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 32767
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 2400
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 37 , _actualFrequency = 10000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 18 , DC % = 51.35
=====================================================================================
Actual data: pin = 39, PWM DC = 88562.17, PWMPeriod = 37.00, PWM Freq (Hz) = 10000.0000
=====================================================================================
Change PWM Freq to 20000.00
[PWM] setPWM: _dutycycle = 32767
[PWM] setPWM_Int: pin = 39 , _dutycycle = 32767 , new frequency = 20000.00
[PWM] setPWM_Int: TimerB, _dutycycle = 32767
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 1200
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 18 , _actualFrequency = 20000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 8 , DC % = 50.00
=====================================================================================
Actual data: pin = 39, PWM DC = 182044.43, PWMPeriod = 18.00, PWM Freq (Hz) = 20000.0000
=====================================================================================
```

---

### 4. PWM_Waveform on AVR128DB

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **AVR128DB**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation

```
Starting PWM_Waveform on AVR128DB
Dx_PWM v1.0.0
[PWM] Dx_PWM: freq = 2000.00
[PWM] Dx_PWM: _dutycycle = 0
[PWM] setPWM: _dutycycle = 0
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 12000
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 187 , _actualFrequency = 2000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 0 , DC % = 0.00
============================================================================================
Actual data: pin = 39, PWM DutyCycle = 0.53, PWMPeriod = 187.00, PWM Freq (Hz) = 2000.0000
============================================================================================
[PWM] setPWM_Int: TIMERB, dutycycle = 0 , DC % = 0.00
[PWM] setPWM_Int: TIMERB, dutycycle = 9 , DC % = 4.81
[PWM] setPWM_Int: TIMERB, dutycycle = 18 , DC % = 9.63
[PWM] setPWM_Int: TIMERB, dutycycle = 28 , DC % = 14.97
[PWM] setPWM_Int: TIMERB, dutycycle = 37 , DC % = 19.79
[PWM] setPWM_Int: TIMERB, dutycycle = 46 , DC % = 24.60
[PWM] setPWM_Int: TIMERB, dutycycle = 56 , DC % = 29.95
[PWM] setPWM_Int: TIMERB, dutycycle = 65 , DC % = 34.76
[PWM] setPWM_Int: TIMERB, dutycycle = 74 , DC % = 39.57
[PWM] setPWM_Int: TIMERB, dutycycle = 84 , DC % = 44.92
[PWM] setPWM_Int: TIMERB, dutycycle = 93 , DC % = 49.73
[PWM] setPWM_Int: TIMERB, dutycycle = 102 , DC % = 54.55
[PWM] setPWM_Int: TIMERB, dutycycle = 112 , DC % = 59.89
[PWM] setPWM_Int: TIMERB, dutycycle = 121 , DC % = 64.71
[PWM] setPWM_Int: TIMERB, dutycycle = 130 , DC % = 69.52
[PWM] setPWM_Int: TIMERB, dutycycle = 140 , DC % = 74.87
[PWM] setPWM_Int: TIMERB, dutycycle = 149 , DC % = 79.68
[PWM] setPWM_Int: TIMERB, dutycycle = 158 , DC % = 84.49
[PWM] setPWM_Int: TIMERB, dutycycle = 168 , DC % = 89.84
[PWM] setPWM_Int: TIMERB, dutycycle = 177 , DC % = 94.65
[PWM] setPWM_Int: TIMERB, dutycycle = 187 , DC % = 100.00
[PWM] setPWM_Int: TIMERB, dutycycle = 177 , DC % = 94.65
[PWM] setPWM_Int: TIMERB, dutycycle = 168 , DC % = 89.84
[PWM] setPWM_Int: TIMERB, dutycycle = 158 , DC % = 84.49
[PWM] setPWM_Int: TIMERB, dutycycle = 149 , DC % = 79.68
[PWM] setPWM_Int: TIMERB, dutycycle = 140 , DC % = 74.87
[PWM] setPWM_Int: TIMERB, dutycycle = 130 , DC % = 69.52
[PWM] setPWM_Int: TIMERB, dutycycle = 121 , DC % = 64.71
[PWM] setPWM_Int: TIMERB, dutycycle = 112 , DC % = 59.89
[PWM] setPWM_Int: TIMERB, dutycycle = 102 , DC % = 54.55
[PWM] setPWM_Int: TIMERB, dutycycle = 93 , DC % = 49.73
[PWM] setPWM_Int: TIMERB, dutycycle = 84 , DC % = 44.92
[PWM] setPWM_Int: TIMERB, dutycycle = 74 , DC % = 39.57
[PWM] setPWM_Int: TIMERB, dutycycle = 65 , DC % = 34.76
[PWM] setPWM_Int: TIMERB, dutycycle = 56 , DC % = 29.95
[PWM] setPWM_Int: TIMERB, dutycycle = 46 , DC % = 24.60
[PWM] setPWM_Int: TIMERB, dutycycle = 37 , DC % = 19.79
[PWM] setPWM_Int: TIMERB, dutycycle = 28 , DC % = 14.97
[PWM] setPWM_Int: TIMERB, dutycycle = 18 , DC % = 9.63
[PWM] setPWM_Int: TIMERB, dutycycle = 9 , DC % = 4.81
[PWM] setPWM_Int: TIMERB, dutycycle = 0 , DC % = 0.00
```

---


### 5. PWM_Waveform on AVR128DA

The following is the sample terminal output when running example [**PWM_Waveform**](examples/PWM_Waveform) on **AVR128DA**, to demonstrate how to use the `setPWM_manual()` function in wafeform creation


```
Starting PWM_Waveform on AVR128DA
Dx_PWM v1.0.0
[PWM] Dx_PWM: freq = 2000.00
[PWM] Dx_PWM: _dutycycle = 0
[PWM] setPWM: _dutycycle = 0
[PWM] setPeriod_TimerB: F_CPU = 24000000 , cycles = 12000
[PWM] setPeriod_TimerB: cycles < TIMERB_RESOLUTION * 64, using divider = 64
[PWM] setPeriod_TimerB: pwmPeriod = 187 , _actualFrequency = 2000.00
[PWM] setPWM_Int: TIMERB, dutycycle = 0 , DC % = 0.00
============================================================================================
Actual data: pin = 39, PWM DutyCycle = 0.53, PWMPeriod = 187.00, PWM Freq (Hz) = 2000.0000
============================================================================================
[PWM] setPWM_Int: TIMERB, dutycycle = 0 , DC % = 0.00
[PWM] setPWM_Int: TIMERB, dutycycle = 9 , DC % = 4.81
[PWM] setPWM_Int: TIMERB, dutycycle = 18 , DC % = 9.63
[PWM] setPWM_Int: TIMERB, dutycycle = 28 , DC % = 14.97
[PWM] setPWM_Int: TIMERB, dutycycle = 37 , DC % = 19.79
[PWM] setPWM_Int: TIMERB, dutycycle = 46 , DC % = 24.60
[PWM] setPWM_Int: TIMERB, dutycycle = 56 , DC % = 29.95
[PWM] setPWM_Int: TIMERB, dutycycle = 65 , DC % = 34.76
[PWM] setPWM_Int: TIMERB, dutycycle = 74 , DC % = 39.57
[PWM] setPWM_Int: TIMERB, dutycycle = 84 , DC % = 44.92
[PWM] setPWM_Int: TIMERB, dutycycle = 93 , DC % = 49.73
[PWM] setPWM_Int: TIMERB, dutycycle = 102 , DC % = 54.55
[PWM] setPWM_Int: TIMERB, dutycycle = 112 , DC % = 59.89
[PWM] setPWM_Int: TIMERB, dutycycle = 121 , DC % = 64.71
[PWM] setPWM_Int: TIMERB, dutycycle = 130 , DC % = 69.52
[PWM] setPWM_Int: TIMERB, dutycycle = 140 , DC % = 74.87
[PWM] setPWM_Int: TIMERB, dutycycle = 149 , DC % = 79.68
[PWM] setPWM_Int: TIMERB, dutycycle = 158 , DC % = 84.49
[PWM] setPWM_Int: TIMERB, dutycycle = 168 , DC % = 89.84
[PWM] setPWM_Int: TIMERB, dutycycle = 177 , DC % = 94.65
[PWM] setPWM_Int: TIMERB, dutycycle = 187 , DC % = 100.00
[PWM] setPWM_Int: TIMERB, dutycycle = 177 , DC % = 94.65
[PWM] setPWM_Int: TIMERB, dutycycle = 168 , DC % = 89.84
[PWM] setPWM_Int: TIMERB, dutycycle = 158 , DC % = 84.49
[PWM] setPWM_Int: TIMERB, dutycycle = 149 , DC % = 79.68
[PWM] setPWM_Int: TIMERB, dutycycle = 140 , DC % = 74.87
[PWM] setPWM_Int: TIMERB, dutycycle = 130 , DC % = 69.52
[PWM] setPWM_Int: TIMERB, dutycycle = 121 , DC % = 64.71
[PWM] setPWM_Int: TIMERB, dutycycle = 112 , DC % = 59.89
[PWM] setPWM_Int: TIMERB, dutycycle = 102 , DC % = 54.55
[PWM] setPWM_Int: TIMERB, dutycycle = 93 , DC % = 49.73
[PWM] setPWM_Int: TIMERB, dutycycle = 84 , DC % = 44.92
[PWM] setPWM_Int: TIMERB, dutycycle = 74 , DC % = 39.57
[PWM] setPWM_Int: TIMERB, dutycycle = 65 , DC % = 34.76
[PWM] setPWM_Int: TIMERB, dutycycle = 56 , DC % = 29.95
[PWM] setPWM_Int: TIMERB, dutycycle = 46 , DC % = 24.60
[PWM] setPWM_Int: TIMERB, dutycycle = 37 , DC % = 19.79
[PWM] setPWM_Int: TIMERB, dutycycle = 28 , DC % = 14.97
[PWM] setPWM_Int: TIMERB, dutycycle = 18 , DC % = 9.63
[PWM] setPWM_Int: TIMERB, dutycycle = 9 , DC % = 4.81
[PWM] setPWM_Int: TIMERB, dutycycle = 0 , DC % = 0.00
```

---
---

### Debug

Debug is enabled by default on Serial.

You can also change the debugging level `_PWM_LOGLEVEL_` from 0 to 4

```cpp
// Don't define _PWM_LOGLEVEL_ > 0. Only for special ISR debugging only. Can hang the system.
#define _PWM_LOGLEVEL_     0
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of the core for Arduino boards.

Sometimes, the library will only work if you update the board core to the latest version because I am using newly added functions.


---
---

### Issues

Submit issues to: [Dx_PWM issues](https://github.com/khoih-prog/Dx_PWM/issues)

---

## TO DO

1. Search for bug and improvement.
2. Support to **TCD0** to change frequency

---

## DONE

 1. Basic hardware-based multi-channel PWMs for **AVRDx-based boards (AVR128Dx, AVR64Dx, AVR32Dx, etc.) using DxCore**



---
---

### Contributions and Thanks

Many thanks for everyone for bug reporting, new feature suggesting, testing and contributing to the development of this library.

  
---

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [MIT](https://github.com/khoih-prog/Dx_PWM/blob/main/LICENSE)

---

## Copyright

Copyright 2022- Khoi Hoang
