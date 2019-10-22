#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
RF24 radio(9, 8); // CE, CSN
const byte address1[6] = "00001";
const byte address2[6] = "00010";

void setup() {
  Serial.begin(9600);
  pinMode(6, OUTPUT);
  radio.begin();
//  radio.openReadingPipe(0, address1);
//  radio.setPALevel(RF24_PA_MIN);
//  radio.startListening();

}

void loop() {
  //open pipe 1
  radio.openReadingPipe(0, address1);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //process first distance
  if(radio.available()){
    radioRead();
  }


  delay(10);
  //open pipe 2
  radio.openReadingPipe(0, address2);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  if(radio.available()){
    radioRead();
  }

  
  }

void radioRead(){
    //read radio channel and convert to integer
    char text[32] = "";
    radio.read(&text, sizeof(text));
    int distanceInt = atoi(text);

    //act accordingly

    //int threshold = 50;
    if (distanceInt < 65){
      for (int i = 0; i <= 4; i++) {
      radio.read(&text, sizeof(text)); //Empty radio 'queue'
        digitalWrite(6, HIGH);
        delay(90);
        digitalWrite(6, LOW);
        delay(90);

    }}
    else if (distanceInt < 185 && distanceInt > 0){
        digitalWrite(6, HIGH);
        delay(750);
        digitalWrite(6, LOW);
        
      }
      else if (distanceInt >= 185 && distanceInt < 235){
        for (int i = 0; i <= 9; i++) {
          radio.read(&text, sizeof(text)); //Empty radio 'queue'
          digitalWrite(6, HIGH);
          delay(30);
          digitalWrite(6, LOW);
          delay(30);
      }}
    
    Serial.println(distanceInt);  
}
