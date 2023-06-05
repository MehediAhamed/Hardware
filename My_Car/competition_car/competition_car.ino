
#include<Arduino.h>
int rEna=A0;
int r1=A1;
int r2=A2;



int lEna=A5;
int l1= A3;
int l2= A4;



float pwmr=2000;
float pwml=2000;



void setup() {

  Serial.begin(115200);


  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(rEna, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(lEna, OUTPUT);


  analogWrite(rEna,pwmr);
  analogWrite(lEna,pwml);




}

void loop() {
 
    digitalWrite(l1,HIGH);
    digitalWrite(l2,LOW);
    digitalWrite(r1,HIGH);
    digitalWrite(r2,LOW);

    
  
}
