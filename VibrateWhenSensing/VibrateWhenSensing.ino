#include <Ultrasonic.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
RF24 radio(9, 8); // CE, CSN
const byte address[6] = "00010";


Ultrasonic ultrasonic(6,7);
int distance;

void setup() {
  
  Serial.begin(9600);
  pinMode(6, OUTPUT); 
  radio.begin();
  radio.openWritingPipe(address);
  
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening(); 
}

void loop() { 
  //Obtain distance from sensor
  distance = ultrasonic.read();
  delay(30);  
  Serial.println(distance);

  //Transmit info (first convert int to char array to transmit)
  const char text[10];
  itoa(distance, text, 10);
  if(distance<300){
    
  for (int i = 0; i <= 8; i++) {
  Serial.println(text);
  (radio.write(&text, sizeof(text)));
  delay(30);
  }
  }
}
