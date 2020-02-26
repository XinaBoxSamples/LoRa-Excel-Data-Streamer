
#include <SPI.h>
#include <LoRa.h>
#include <xCore.h>
#include <xSW01.h>
#include <xOC03.h>
xSW01 SW01;
xOC03 OC03;

const int csPin = 10;         // LoRa radio chip select
const int resetPin = 9;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0x02;     // address of this device
byte destination = 0x01;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 500;          // interval between sends

void setup() {
  Serial.begin(9600);                   // initialize serial
  Wire.begin();
  SW01.begin();
  OC03.begin();
  while (!Serial);
  Serial.println("LoRa Duplex");
  LoRa.setPins(csPin, resetPin, irqPin);
  if (!LoRa.begin(915E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);
  }
}

void loop() {
  if (millis() - lastSendTime > interval) {
    SW01.poll();
    char data[65];
    sprintf(data, "%d,%d,%d", (int)SW01.getTempC(), (int)SW01.getHumidity(), (int)(SW01.getPressure() / 100));
    sendMessage(data);
    lastSendTime = millis();            // timestamp the message
    interval = random(2000) + 1000;    // 2-3 seconds
  }
  onReceive(LoRa.parsePacket());
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}

void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return
  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length

  String incoming = "";

  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length()) {   // check length for error
    Serial.println("error: message length does not match length");
    return;                             // skip rest of function
  }

  // if the recipient isn't this device or broadcast,
  if (recipient != localAddress && recipient != 0xFF) {
    Serial.println("This message is not for me.");
    return;                             // skip rest of function
  }

  // if message is for this device, or broadcast, print details:

  Serial.print(String(incomingMsgId));
  Serial.print("," + String(incomingLength));
  Serial.print(",\"" + incoming + "\"");
  Serial.print("," + String(LoRa.packetRssi()));
  Serial.print("," + String(LoRa.packetSnr()));
  Serial.println();
  if (incoming.toInt() == 1) {
    OC03.write(HIGH);
  } else {
    OC03.write(LOW);
  }
}
