#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN
const byte address[6] = "00001";

const int buttonPin1 = 2;
const int buttonPin2 = 3;
const int buttonPin3 = 4;
const int buttonPin4 = 5;

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.stopListening();
  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(buttonPin1) == LOW) {
    sendButtonIndex(1);
  }
  if (digitalRead(buttonPin2) == LOW) {
    sendButtonIndex(2);
  }
  if (digitalRead(buttonPin3) == LOW) {
    sendButtonIndex(3);
  }
  if (digitalRead(buttonPin4) == LOW) {
    sendButtonIndex(4);
  }

  delay(100); // Pour éviter de spammer la communication
}

void sendButtonIndex(int index) {
  radio.write(&index, sizeof(index));
  Serial.print("Bouton ");
  Serial.print(index);
  Serial.println(" pressé.");
}
