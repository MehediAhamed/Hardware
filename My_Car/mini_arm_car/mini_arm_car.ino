//Code for 3 dof arm

#include "Motor.h"
#include "sbus.h"
#include <Servo.h>

#define SBUS_PIN A8
SBUS sbus;

Servo myservo_p;
Servo myservo_s;
Servo myservo_g;

int xarm_p[3] = {900, 900, 900};
int xarm_s[3] = {900, 900, 900};
int xarm_g[3] = {900, 900, 900};


Motor motor_Right(6, 5);
Motor motor_Left(4, 3);

int rEna=7;
int lEna=2;
float pwm=255;


void setup() {

  //These 3 motors are for arm
  
  myservo_g.attach(11);   // base motor
  myservo_s.attach(10);  // middle motor
  myservo_p.attach(9);   //clutch motor

//These are wheel motors
  pinMode(rEna,OUTPUT);
  pinMode(lEna,OUTPUT);

  analogWrite(rEna,pwm);
  analogWrite(lEna,pwm);


  Serial.begin(9600);
  sbus.begin(SBUS_PIN, sbusNonBlocking);
}
//This is the filter function to filter noise
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
//arm() controls arm
void arm()
{
   for (int i = 2; i >= 1; i --) {
    xarm_p[i] = xarm_p[i-1];
    xarm_p[i] = xarm_p[i-1];
    xarm_p[i] = xarm_p[i-1];
   }
   
   xarm_p[0] = filterG(sbus.getChannel(3),xarm_p[0]);
   xarm_s[0] = filterG(sbus.getChannel(1),xarm_s[0]);
   xarm_g[0] = filterG(sbus.getChannel(8),xarm_g[0]);

   xarm_p[0] = (xarm_p[0] + xarm_p[1] + xarm_p[2])/3;
   xarm_s[0] = (xarm_s[0] + xarm_s[1] + xarm_s[2])/3;
   xarm_g[0] = (xarm_g[0] + xarm_g[1] + xarm_g[2])/3;

  Serial.print(xarm_p[0]);
  Serial.print(' ');
  Serial.print(xarm_s[0]);
  Serial.print(' ');
  Serial.println(xarm_g[0]);

//  Serial.println(xarm_g);


  myservo_p.writeMicroseconds(xarm_p[0]);             // drive servo
  myservo_s.writeMicroseconds(xarm_s[0]);             // drive servo LEFT
  myservo_g.writeMicroseconds(xarm_g[0]);             // drive servo RIGHT


}
void loop() {

//  for (int i = 1; i <= 10; i ++) {
//      Serial.print(sbus.getChannel(i));
//      Serial.print(' ');
//    }
  int xvel = sbus.getChannel(2) + 7;
  int zvel = sbus.getChannel(4) - 3;

//  Serial.print(xvel);
//  Serial.print(' ');
//  Serial.println(zvel);

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

//  Serial.print(xvel);
//  Serial.print(' ');
//  Serial.println(zvel);

  xvel = map(xvel, 2000, 1000, -100, 100);
  zvel = map(zvel, 1000, 2000, -100, 100);

//  Serial.print(xvel);
//  Serial.print(' ');
//  Serial.println(zvel);

  motor_Right.setSpeed(5*(xvel - zvel));
  motor_Left.setSpeed(5*(xvel + zvel));
  arm();

  delay(10);

}
