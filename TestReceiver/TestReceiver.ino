

// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 8

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

char dataReceived[10]; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup() {

    Serial.begin(9600);
    pinMode(6, OUTPUT);
    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

//=============

void loop() {
    getData();
    showData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(dataReceived);
        int distanceInt = atoi(dataReceived);
        //int threshold = 50;
    if (distanceInt < 20){
      Serial.write("naar links");
      
      for (int i = 0; i <= 4; i++) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        digitalWrite(6, HIGH);
        delay(90);
        digitalWrite(6, LOW);
        delay(90);
      }
    }
    else if (distanceInt < 50 && distanceInt > 0){
      
        digitalWrite(6, HIGH);
        delay(500);
        digitalWrite(6, LOW);
        
      }
      else if (distanceInt >= 50 && distanceInt < 75){
        for (int i = 0; i <= 9; i++) {
          radio.read( &dataReceived, sizeof(dataReceived) );
          digitalWrite(6, HIGH);
          delay(30);
          digitalWrite(6, LOW);
          delay(30);
      }} 
        newData = false;
        
    }
}
