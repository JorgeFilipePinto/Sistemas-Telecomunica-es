#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>


int counter = 0;


void setup() {
  SPI.begin(5, 19, 27, 18);
  Serial.begin(115200);
  while (!Serial);

  Serial.println("LoRa Sender");
  LoRa.setPins(18,23,26);
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  String response;
  char message;
  if(Serial.available()) {
    message = Serial.read();
  }
  /*Serial.print("Sending packet: ");
  Serial.println(counter);
*/
  // send packet
  if (message){
    LoRa.beginPacket();
    LoRa.print("Zona Invadida: ");
    LoRa.print(message);
    LoRa.endPacket();
    Serial.print("Zona: "); Serial.println(message);
  }
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    while(LoRa.available()) {
      char text = LoRa.read();
      response += text;
    }
    Serial.print("Packet: ");
    Serial.println(response);
  }
  if (response == "OK") {
    Serial.println("Pacote foi entrgue com sucesso");
  }
  delay(2000);
}
