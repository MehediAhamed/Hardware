// Main arm code comparing pots and driving servos
#include "Motor.h"
#include "sbus.h"
#include <Servo.h>

#define SBUS_PIN A8

SBUS sbus;

Servo myservo_p;
Servo myservo_s;
Servo myservo_g;

int xarm_p=1041;
int xarm_s=1041;
int xarm_g=900;


Motor motor_Right(A1, A2);
Motor motor_Left(A3, A4);

int rEna=A0;
int lEna=A5;
float pwm=255;


void setup() {


  myservo_p.attach(11);   // waist
  myservo_s.attach(10);   // left hand
  myservo_g.attach(9);   // right hand


  pinMode(rEna,OUTPUT);
  pinMode(lEna,OUTPUT);

  analogWrite(rEna,pwm);
  analogWrite(lEna,pwm);


  Serial.begin(9600);
  sbus.begin(SBUS_PIN, sbusNonBlocking);
}
int filterarm( int x , int prev)
{
  if(x<950 || x>=1050 && x<=1500 || x>=1550 && x<=1800 || x>=1968 && x<=3000)
    return prev;
  else return x;
}

int filterG( int x , int prev)
{
  if(x<900 || x>=1968 && x<=3000)
    return prev;
  else return x;
}

void arm()
{
   xarm_p = filterarm(sbus.getChannel(5),xarm_p);
   xarm_s = filterarm(sbus.getChannel(7),xarm_s);
   xarm_g = filterG(sbus.getChannel(8),xarm_g);

  
//  Serial.print(xarm_p);
//  Serial.print(' ');
//  Serial.print(xarm_s);
//  Serial.print(' ');
//  Serial.println(xarm_g);
//

  myservo_p.writeMicroseconds(xarm_p);             // drive servo
  myservo_s.writeMicroseconds(xarm_s);             // drive servo LEFT
  myservo_g.writeMicroseconds(xarm_g);             // drive servo RIGHT


}
void loop() {

      for (int i = 1; i <= 10; i ++) {
        Serial.print(sbus.getChannel(i));
        Serial.print(' ');
      }
  int xvel = sbus.getChannel(2) + 7;
  int zvel = sbus.getChannel(1) - 3;


  if (xvel < 1000 || zvel < 1000) {
    xvel = 1500;
    zvel = 1500;
  }

  if (abs(xvel - 1500) < 100) {
    xvel = 1500;
  }

  if (abs(zvel - 1500) < 100) {
    zvel = 1500;
  }

  xvel = map(xvel, 2000, 1000, -100, 100);
  zvel = map(zvel, 1000, 2000, -100, 100);

  motor_Right.setSpeed(xvel - zvel);
  motor_Left.setSpeed(xvel + zvel);
  
  arm();

  delay(100);

}
