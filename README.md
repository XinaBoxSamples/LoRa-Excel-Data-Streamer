# LoRa Excel Data Streamer
Using LoRa radios from XinaBox to send data to Excel Data Streamer

## Getting Started

### Get the components

Go to https://xinabox.cc and get yourself the following xChips:

Qty|xChip|Description
---:|:---:|---
2|CR0x|Arduino Uno core xChip with LoRa radio
1 | IP01 | Power, Programming and Comminucation xChip
1| PG01| Generic Power xChip, 6-24 Volt DC input
1 | SW01 | Weather Sensors for Temperature, Humidity and Bariometric Pressure
1 | OC03 | Relay
? | PU02 | Micro USB power source, if you don't want to hassle with power for the PG01
1|XC10|bag of connectors

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

#### Needed software

- You need Arduino for this project.
- The Arduino project files uses the following libraries
  - Arduino LoRa: https://github.com/sandeepmistry/arduino-LoRa
  - XinaBox Core: https://github.com/xinabox/arduino-core
  - XinaBox SW01: https://github.com/xinabox/arduino-sw01
  - XinaBox OC03: https://github.com/xinabox/arduino-oc03
- And then you need Excel for Office 365. Check out if you have Data Streamer first before you continue - see below.

#### The "Receiver" End
I put __Receiver__ in quotes because both .ino files both sends and receive, but this .ino file is the one that is connected to your computer and talks directly to Excel.
- Download the [src/receiver.ino] file and make a project in Arduino with this file. 
- It is prepared for the CR03 radio, so if you have a CR02, then change "915E6" to "868E6". And if yu are using the CR01, then change "915E6" to "433E6".
- Connect the IP01 and the CR0x using a connector. Insert into your computer.
- In Ardunio select Board: "Arduino Pro or Pro Mini" and then select Processor: "ATmega328P (5V, 16Mhz)"
- Select the port where the IP01 is inserted. Compile and Upload.

#### The "Sender" End
This .ino file is the one that is connected to ... your environment.
- Download the [src/sender.ino] file and make a project in Arduino with this file. 
- It is prepared for the CR03 radio, so if you have a CR02, then change "915E6" to "868E6". And if yu are using the CR01, then change "915E6" to "433E6".
- Connect the IP01 and the other CR0x using a connector. Insert into your computer.
- In Ardunio select Board: "Arduino Pro or Pro Mini" and then select Processor: "ATmega328P (5V, 16Mhz)"
- Select the port where the IP01 is inserted. Compile and Upload.

#### Make your 2 circuits
<img src="images/circuits.jpg" width="35%" height="auto" align="right">
- Connect the IP01 and CR03 with the Receiver software using a connector. Attach the Antenna. Connect to your computer.
- Connect the other CR03 with the PG01, OC03, and SW01, using 4 connectors. Attache the Antenna.
- If you don't connect anything to the OC03, you can still see it turns on and off by looking at the blue LED just below the "Power" logo.
- Connect a power source to the PG01. While the power has to be DC (it has to have a + and a -), it doesn't matter which wire goes where, the PG01 will find the + and - it self. You can use any power from 6V (like in the picture) to 24 Volt (such as 12-14 volt from a car battery).
- I have a couple of wires going into the PG01 feeding the fan, but using the OC03 as a switch.

#### Start up Excel
- Open Excel and activate Data Streamer, see more here: https://support.office.com/en-us/article/what-is-data-streamer-1d52ffce-261c-4d7b-8017-89e8ee2b806f
- Click on "Data Streamer" in the menu
- Click "Connect aevice" and click on the serial port for the IP01. Excel will now build sheets for you to play with.
- Click "Start Streaming" and slowly the table should be filled with that.
- But it is really much easier to watch the video....



![Video](https://youtu.be/p3n13H2vXbU "Video")

<a href="http://xib.one/bg" title="Video"><img src="images/youtubelogo.svg" alt="Video" /></a>

