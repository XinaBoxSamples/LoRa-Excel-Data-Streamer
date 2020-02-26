[![Build Status](https://travis-ci.org/xinaboxsamples/LoRa-Excel-Data-Streamer.svg?branch=master)](https://travis-ci.org/xinaboxsamples/LoRa-Excel-Data-Streamer)
[![GitHub issues](https://img.shields.io/github/issues/xinaboxsamples/LoRa-Excel-Data-Streamer.svg)](https://github.com/xinaboxsamples/LoRa-Excel-Data-Streamer/issues) ![GitHub Commit](https://img.shields.io/github/last-commit/xinaboxsamples/LoRa-Excel-Data-Streamer) ![Maintained](https://img.shields.io/maintenance/yes/2020)

# LoRa Excel Data Streamer
Using LoRa radios from XinaBox to send data to Excel Data Streamer. 

Reading temperature, humidity and barometric pressure from a **SW01** xChip (based on the BME280) and send the data via a LoRa radio to a receiving LoRa radio that is connected to a computer running *Excel 365*. In return reading a value from the same Excel spreadsheet sending that value via LoRa radio to the weather station to turn a relay on and off.

This project can be modified easily with other sensory input from XinaBox, such as the **SL01** Light Sensor, the **SG33** VOC and eCO2 Sensor, the **SL19** Infrared Temperatur Sensor, or any of the many other sensors.
Similarly the output can be increased with more **OC03** Relays, or modified to use Servos using the **OC05** or Steppers using the **OC06**, or any of the other output options. 
There are also many power solutions. In this project the one end is powered by the computer via USB, and the weather station end with a 6V battery pack, but by changing the **PG01** to and **PU01**, **PU02** or **IP01**, you can power the weather station with USB, or even use a **PB01**, **PB02**, **PB04**, **PL01** for various battery solutions.

If you want to build you own project using another single board computer (SBC), say the *Raspberry Pi*, you can use the XinaBox I2C controlled LoRa radios, **RL01**, **RL02**, and **RL03**. Connect those to the RasPi using the RasPi bridge, **BR01**. If you are using another single board computer, then use another bridge, such as BeagleBone Black (**BB01**), 96 Boards (like DragonBoard) (**B901**), Minnowboard (**BL01**), and others. You can use the same bridges to connect XinaBox sensors to your SBC.

And if you want to use _LoRaWan_ to connect your project to a LoRaWan ready network, then take a look at our LoRaWan ready libraries for the **RL0x** radios:
- [Raspberry Pi](https://github.com/xinabox/rpi-LMIC)
- [Arduino](https://github.com/xinabox/arduino-LMIC-RL0x)

<img src="images/circuits.jpg" width="20%" height="auto" align="right">

## Getting Started
- [Get the components](#get-the-components)
- [Build](#build)
  - [Required software](#required-software)
  - [The "Receiver" End](#the-receiver-end)
  - [The "Sender" End](#the-sender-end)
  - [Make the 2 circuits](#make-the-2-circuits)
  - [Excel Data Streamer](#excel-data-streamer)
- [Watch this video first!](http://xib.one/bg "Video")
  
### Get the components

Go to https://xinabox.cc and get yourself the following xChips:

Qty Required|Qty Suggested|xChip|Description
---:|---:|:---:|---
2|2|[CR0x](https://xinabox.cc/products/CR03)|Arduino Uno core xChip with LoRa radio
1|2|[IP01](https://xinabox.cc/products/IP01)|Power, Programming and Communication xChip
1|1|[PG01](https://xinabox.cc/products/PG01)|Generic Power xChip, 6-24 Volt DC input, not needed if you get another IP01 or a PU02
1|1|[SW01](https://xinabox.cc/products/SW01)|Weather Sensor for Temperature, Humidity and Bariometric Pressure
0|1|[OC03](https://xinabox.cc/products/OC03)|Relay, optional, but included in the code
0|1|[PU02](https://xinabox.cc/products/PU02)|Micro USB power source, if you don't want to hassle with power for the PG01, or use another IP01
1|1|[XC10](https://xinabox.cc/products/XC10)|Bag of xBus connectors

#### Notes on the xChips
Study this map for which ITU Region you belong to: 

<img src="images/ITUregions.svg" width="50%" height="auto" align="center">

xChip|ITU Regions|Frequency|Notes
---|:---:|---:|---
CR01|-|433.25 MHz|Can be used globally if you hold a Radio Amateur License
CR02|1 (Yellow/B)|868.00 MHz|
CR03|2 (Blue/C)|915.00 MHz|

#### Other material
In the video I have used a fan from a computer and a 4xAA Battery holder. You can connect other power sources and other things you want to turn on and off.

---

### Build

#### Required software

- You need Arduino for this project.
- The Arduino project files uses the following libraries
  - Arduino LoRa: https://github.com/sandeepmistry/arduino-LoRa
  - XinaBox Core: https://github.com/xinabox/arduino-core
  - XinaBox SW01: https://github.com/xinabox/arduino-sw01
  - XinaBox OC03: https://github.com/xinabox/arduino-oc03
- And then you need Excel for Office 365. Check out if you have Data Streamer first before you continue - see below.

#### The "Receiver" End
I put __Receiver__ in quotes because both .ino files both sends and receive, but this .ino file is the one that is connected to your computer and talks directly to *Excel*.
- Download the [receiver.ino](src/receiver.ino) file and make a project in Arduino with this file. 
- It is prepared for the **CR03** radio, so if you have a **CR02**, then change `915E6` to `868E6`. And if yu are using the **CR01**, then change `915E6` to `433E6`.
- Connect the **IP01** and the **CR0x** using a connector. Insert into your computer.
- In *Arduino* select `Board: "Arduino Pro or Pro Mini"` and then select `Processor: "ATmega328P (5V, 16Mhz)"`
- Select the port where the **IP01** is inserted. Compile and Upload.

#### The "Sender" End
This .ino file is the one that is connected to ... your environment.
- Download the [sender.ino](src/sender.ino) file and make a project in Arduino with this file. 
- It is prepared for the **CR03** radio, so if you have a **CR02**, then change `915E6` to `868E6`. And if yu are using the **CR01**, then change `915E6` to `433E6`.
- Connect the **IP01** and the other **CR0x** using a connector. Insert into your computer.
- In *Arduino* select `Board: "Arduino Pro or Pro Mini"` and then select `Processor: "ATmega328P (5V, 16Mhz)"`
- Select the port where the **IP01** is inserted. Compile and Upload.

<img src="images/circuits.jpg" width="35%" height="auto" align="right">

#### Make the 2 circuits
- Connect the **IP01** and **CR03** with the Receiver software using a connector. Attach the Antenna. Connect to your computer.
- Connect the other **CR03** with the **PG01**, **OC03**, and **SW01**, using 4 connectors. Attache the Antenna.
- If you don't connect anything to the OC03, you can still see it turns on and off by looking at the blue LED just below the "Power" logo.
- Connect a power source to the **PG01**. While the power has to be DC (it has to have a + and a -), it doesn't matter which wire goes where, the PG01 will find the + and - it self. You can use any power from 6V (like in the picture) to 24 Volt (such as 12-14 volt from a car battery).
- I have a couple of wires going into the **PG01** feeding the fan, but using the **OC03** as a switch.

#### Excel Data Streamer
- Open *Excel* and activate Data Streamer, see more here: https://support.office.com/en-us/article/what-is-data-streamer-1d52ffce-261c-4d7b-8017-89e8ee2b806f
- Click on `Data Streamer` in the menu bar
- Click `Connect a Device` and click on the serial port for the **IP01**. *Excel* will now build sheets for you to play with.
- Click `Start Data` and slowly the table should be filled with that.

## Video
- But it is really much easier to watch the video...

<a href="http://xib.one/bg" title="Video"><img src="images/youtubelogo.svg" alt="Video" width="35%" height="auto" align="right"/></a>

