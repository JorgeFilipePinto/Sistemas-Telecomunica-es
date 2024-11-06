#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>

void setup() {
  SPI.begin(5, 19, 27, 18);
  LoRa.setPins(18,23,26);
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Receiver");

  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read packet
    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    // print RSSI of packet
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
    LoRa.beginPacket();
    LoRa.print("OK");
    LoRa.endPacket();
  }
}
