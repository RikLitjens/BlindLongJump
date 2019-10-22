#include <Ultrasonic.h>
#include <SPI.h>
#include <RF24.h>
#include <RF24.nRF24L01.h>

RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

Ultrasonic ultrasonic(3,4);
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
  //Obtain distance 
  distance = ultrasonic.read();
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(50);  

  //Transmit info
  const char text[] = "Hello World";
  Serial.println(text);
  radio.write(&text, sizeof(text));
  delay(1000);


  //Vibrate when in range
  if (distance < 30) {
    
    digitalWrite(6, HIGH);
    delay(100);
    digitalWrite(6, LOW);
    
    delay(100);

  }
  
}
