
#include<Arduino.h>
int Out1=13;
int r1= 2;
int r2= 3;
int rEna=8;

int l1=4;
int l2=5;
int lEna=9;

float pwmr=1023;
float pwml=1023;



void setup() {

  Serial.begin(115200);
  pinMode(Out1, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(rEna, OUTPUT);
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(lEna, OUTPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  analogWrite(rEna,pwmr);
  analogWrite(lEna,pwml);
  digitalWrite(Out1, HIGH);



}

void loop() {
  while(1)
  {
  if(digitalRead(A1)==HIGH) digitalWrite(r1,HIGH);
  if(digitalRead(A2)==HIGH) digitalWrite(r2,HIGH);
  if(digitalRead(A3)==HIGH) digitalWrite(l1,HIGH);
  if(digitalRead(A4)==HIGH) digitalWrite(l2,HIGH);

  if(digitalRead(A1)==LOW) digitalWrite(r1,LOW);
  if(digitalRead(A2)==LOW) digitalWrite(r2,LOW);
  if(digitalRead(A3)==LOW) digitalWrite(l1,LOW);
  if(digitalRead(A4)==LOW) digitalWrite(l2,LOW);
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
