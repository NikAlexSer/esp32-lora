#include <SPI.h>  
#include <LoRa.h> 
#include <Wire.h> 
#include "SSD1306.h"

#define SCK 5 // GPIO5 -- SX127x's SCK
#define MISO 19 // GPIO19 -- SX127x's MISO
#define MOSI 27 // GPIO27 -- SX127x's MOSI
#define SS 18 // GPIO18 -- SX127x's CS
#define RST 14 // GPIO14 -- SX127x's RESET
#define DI00 26 // GPIO26 -- SX127x's IRQ (Interrupt Request)
 
#define BAND 868E6 // 433E6, 868E6, 915E6
#define PABOOST true

unsigned int counter = 0;  
SSD1306 display(0x3c, 4, 15);
String rssi = "RSSI --";
String packSize = "--";
String packet ;

void setup() {
  pinMode(16,OUTPUT);
  pinMode(25,OUTPUT);
  digitalWrite(16, LOW); 
  delay(50); 
  digitalWrite(16, HIGH); /
 
  display.init(); 
  display.flipScreenVertically(); 
  display.setFont(ArialMT_Plain_10);
  delay(1500);
  display.clear(); 
 
  SPI.begin(SCK,MISO,MOSI,SS);
  LoRa.setPins(SS,RST,DI00);
  
  if (!LoRa.begin(BAND)) {
    display.drawString(0, 0, "Starting LoRa failed!");
    display.display();
    while (1);
  }
  display.drawString(0, 0, "LoRa Initial success!");
  display.display();
  delay(1000);
}

void loop() {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Sending packet: ");
  display.drawString(40, 26, String(counter));
  display.display();   
   
  LoRa.beginPacket();
  LoRa.print("{id: 1, ziga: 'hi o/', " + (String)counter + "}");
  LoRa.endPacket(); 
  counter++; 
  digitalWrite(2, HIGH); 
  delay(500); 
  digitalWrite(2, LOW);
  delay(500); 
}
