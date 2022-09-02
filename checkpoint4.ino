#include <SPI.h>

#include <MFRC522.h>

#include <ArduinoJson.h>

const int TAMANHO = 50

#define SS_PIN 10
#define RST_PIN 9 MFRC522 mfrc522(SS_PIN, RST_PIN);
char st[20];
void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();

}
void loop() {
  StaticJsonDocument < TAMANHO > json;
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  String conteudo = "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }

  conteudo.toUpperCase();
  Serial.print(conteudo);

  json["vendoArduino"] = conteudo;

  serializeJson(json, Serial);
  Serial.println();
}
