#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8);  // CE, CSN
const byte address[6] = "00001";
// Broches pour chaque segment (a, b, c, d, e, f, g, dp)
const int segments[] = {9,10,2,3,4,5,6};
const int buzzerPin = 0;  // Broche du buzzer

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, address);  // Adresse du récepteur
  radio.setPALevel(RF24_PA_LOW);      // Réglez la puissance de réception en fonction de vos besoins
  radio.startListening();
  // for 7 segment
  for (int i = 0; i <= 6; i++) {
    pinMode(segments[i], OUTPUT);
  }
  displayDigit(0);
  pinMode(buzzerPin, OUTPUT);  // Définir la broche du buzzer en tant que sortie
}

void loop() {
  if (radio.available()) {
    int receivedIndex;
    radio.read(&receivedIndex, sizeof(receivedIndex));
    if (receivedIndex != 0) {
      displayDigit(receivedIndex);
      activateBuzzer();  // Activer le buzzer lors de la réception d'un index
    }
  }
}


void displayDigit(int digit) {
  // Tableau de segments pour les chiffres 0-9 (inversé pour un afficheur à anode commune)
  byte digitSegments[10] = {
    B0111111,  // 0
    B0110000,  // 1
    B1011011,  // 2
    B1001111,  // 3
    B1100110,  // 4
    B1101101,  // 5
    B1111101,  // 6
    B0000111,  // 7
    B1111111,  // 8
    B1101111,  // 9
  };

  for (int i = 0; i < 8; i++) {
    digitalWrite(segments[i], !bitRead(digitSegments[digit], i)); // Inverser la valeur (LOW pour activer les segments)
  }
}



void activateBuzzer() {
  digitalWrite(buzzerPin, HIGH);  // Activer le buzzer
  delay(1000);  // Sonnerie pendant 1 seconde (ajustez la durée au besoin)
  digitalWrite(buzzerPin, LOW);  // Désactiver le buzzer
}
