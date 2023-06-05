// drive brushless motor from pot input using servo library

#include <Servo.h>
Servo myservo; 

int pot;

void setup() {

  myservo.attach(A0); 
  pinMode(8, INPUT);
  Serial.begin(115200);

}

void loop() {

  //pot = analogRead(A8);
  //pot = map(pot,0,1023,1500,2500);
  //Serial.println(pot);

  myservo.write(270); 


}
