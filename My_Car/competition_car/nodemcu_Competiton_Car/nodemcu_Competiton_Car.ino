
#include<Arduino.h>
#include<Servo.h>
Servo Al,Ar;
Servo Bl,Br;

int r1= A1;
int r2= A2;
int rEna=A0;

int l1=A3;
int l2=A4;
int lEna=A5;

float pwmr=1023;
float pwml=1023;



void setup() {

  Serial.begin(115200);

  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(rEna, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(lEna, OUTPUT);
  pinMode(5, INPUT);
  pinMode(4, INPUT);
  pinMode(3, INPUT);
  pinMode(2, INPUT);

  pwmr=map(pwmr,0,1023,0,255);
  pwml=map(pwml,0,1023,0,255);
  
  analogWrite(rEna,pwmr);
  analogWrite(lEna,pwml);




}

void loop() {
  while(1)
  {
  if(digitalRead(2)==HIGH) digitalWrite(r1,HIGH);
  if(digitalRead(3)==HIGH) digitalWrite(r2,HIGH);
  if(digitalRead(4)==HIGH) digitalWrite(l1,HIGH);
  if(digitalRead(5)==HIGH) digitalWrite(l2,HIGH);

  if(digitalRead(2)==LOW) digitalWrite(r1,LOW);
  if(digitalRead(3)==LOW) digitalWrite(r2,LOW);
  if(digitalRead(4)==LOW) digitalWrite(l1,LOW);
  if(digitalRead(5)==LOW) digitalWrite(l2,LOW);
  else 
  {
    digitalWrite(r1,LOW);
    digitalWrite(r2,LOW);
    digitalWrite(l1,LOW);
    digitalWrite(l2,LOW);
    continue;
  }

  }
 

}
