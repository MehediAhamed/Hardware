
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>

// WiFi settings
#define SSID_AP            "Radib's Car" 
#define PASSWORD_AP        "00001111"         

// motor settings
#define RIGHT_MOTOR_PIN1  D0                   
#define RIGHT_MOTOR_PIN2  D1                 
#define LEFT_MOTOR_PIN1   D2                  
#define LEFT_MOTOR_PIN2   D3                  
#define ENA   D7
#define ENB   D8
#define Out   D5
                   

IPAddress local_ip(192, 168, 4, 1);           //IP for AP mode
IPAddress gateway(192, 168, 100, 1);          //IP for AP mode
IPAddress subnet(255, 255, 255, 0);           //IP for AP mode
ESP8266WebServer server(80);

int car_mode = 0;
String command;
int RIGHT_MOTOR_SPEED= 1023;              // speed for right motor (0-1023)
int LEFT_MOTOR_SPEED=  1023;                // speed for left motor (0-1023)

// initialize
void setup() {
  
  Serial.begin(115200);

  pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
  pinMode(RIGHT_MOTOR_PIN2, OUTPUT);
  pinMode(LEFT_MOTOR_PIN1, OUTPUT);
  pinMode(LEFT_MOTOR_PIN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(Out, OUTPUT);
  //car_control(); // stop the car

  digitalWrite(ENA, HIGH);
  digitalWrite(ENB, HIGH);
  digitalWrite(Out, HIGH);

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  WiFi.softAP(SSID_AP, PASSWORD_AP);

  // setup web server to handle specific HTTP requests
  server.on("/", HTTP_GET, handle_OnConnect);
  server.on("/forward", HTTP_GET, handle_forward);
  server.on("/backward", HTTP_GET, handle_backward);
  server.on("/left", HTTP_GET, handle_left);
  server.on("/right", HTTP_GET, handle_right);
  server.on("/stop", HTTP_GET, handle_stop);
  server.onNotFound(handle_NotFound);

  //start server
  server.begin(); 
  ArduinoOTA.begin();  
  Serial.println("ESP8266 car server started.");
  
}

// handle HTTP requests and control car
void loop() { 
  ArduinoOTA.handle();
  server.handleClient();
  command = server.arg("State");
  car_control();
}

// HTTP request: on connect
void handle_OnConnect() {
  car_mode = 0;
  Serial.println("Client connected");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: stop car
void handle_stop() {
  car_mode = 0;
  Serial.println("Stopped");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go forward
void handle_forward() {
  car_mode = 1;
  Serial.println("Go forward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: go backward
void handle_backward() {
  car_mode = 2;
  Serial.println("Go backward...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn left
void handle_left() {
  car_mode = 3;
  Serial.println("Turn left...");
  server.send(200, "text/html", SendHTML());
}

// HTTP request: turn right
void handle_right() {
  car_mode = 4;
  Serial.println("Turn right...");
  server.send(200, "text/html", SendHTML());
}


// function to move forward
void Forward(){ 

   analogWrite(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_SPEED);
   digitalWrite(RIGHT_MOTOR_PIN2, LOW);
   analogWrite(LEFT_MOTOR_PIN1, LEFT_MOTOR_SPEED);
   digitalWrite(LEFT_MOTOR_PIN2, LOW);
}

// function to move backward
void Backward(){
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, RIGHT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN1, LOW);
      analogWrite(LEFT_MOTOR_PIN2, LEFT_MOTOR_SPEED);
}

// function to turn Left
void TurnLeft(){
   digitalWrite(RIGHT_MOTOR_PIN1, RIGHT_MOTOR_SPEED);
   analogWrite(RIGHT_MOTOR_PIN2, LOW);
   digitalWrite(LEFT_MOTOR_PIN1, LOW);
   analogWrite(LEFT_MOTOR_PIN2,LEFT_MOTOR_SPEED);
     
}

// function to turn Right
void TurnRight(){
      digitalWrite(RIGHT_MOTOR_PIN1, LOW);
      analogWrite(RIGHT_MOTOR_PIN2, RIGHT_MOTOR_SPEED);
      digitalWrite(LEFT_MOTOR_PIN1, LEFT_MOTOR_SPEED);
      analogWrite(LEFT_MOTOR_PIN2, LOW);
}

// function to stop motors

void Stop(){  
  digitalWrite(RIGHT_MOTOR_PIN1, LOW);
  digitalWrite(RIGHT_MOTOR_PIN2, LOW);
  digitalWrite(LEFT_MOTOR_PIN1, LOW);
  digitalWrite(LEFT_MOTOR_PIN2, LOW);
}

// HTTP request: other
void handle_NotFound() {
  car_mode = 0;
  Serial.println("Page error");
  server.send(404, "text/plain", "Not found");
}

// control car movement
void car_control() {
  if(car_mode==0 ) {
    
      Stop();
  }
  if(car_mode==1 ||command == "F") {
      Forward();
  }
   if(car_mode==2 ||command == "B") {
      Backward();
  }
    if(car_mode==3 ||command == "L") {
      TurnLeft();
  }
    if(car_mode==4 ||command == "R") {
      TurnRight();
  }



  //speed Control
      
      if (command == "0")
      {
        LEFT_MOTOR_SPEED=330;
        RIGHT_MOTOR_SPEED=330;
      }
      if (command == "1") 
      {
        LEFT_MOTOR_SPEED=400;
        RIGHT_MOTOR_SPEED=400;
      }
       if (command == "2")
      {
        LEFT_MOTOR_SPEED=430;
        RIGHT_MOTOR_SPEED=430;
      }

      if (command == "3")
      {
        LEFT_MOTOR_SPEED=530;
        RIGHT_MOTOR_SPEED=530;
      }
       if (command == "4")
      {
        LEFT_MOTOR_SPEED=630;
        RIGHT_MOTOR_SPEED=630;
      }
       if (command == "5")
      {
        LEFT_MOTOR_SPEED=680;
        RIGHT_MOTOR_SPEED=680;
      }
       if (command == "6")
      {
        LEFT_MOTOR_SPEED=730;
        RIGHT_MOTOR_SPEED=730;
      }
       if (command == "7")
      {
        LEFT_MOTOR_SPEED=830;
        RIGHT_MOTOR_SPEED=830;
      }
      if (command == "8")
      {
        LEFT_MOTOR_SPEED=890;
        RIGHT_MOTOR_SPEED=890;
      }
       if (command == "9")
      {
        LEFT_MOTOR_SPEED=930;
        RIGHT_MOTOR_SPEED=930;
      }
      if (command == "q")
      {
        LEFT_MOTOR_SPEED=1023;
        RIGHT_MOTOR_SPEED=1023;
      }
}



// output HTML web page for user
String SendHTML() {
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<title>ESP8266 WiFi Car</title>";
  html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  html += "<style>body {background-color: Moccasin;} h1 {color: SaddleBrown;} h2 {color: Olive;}</style>";
  html += "</head>";
  html += "<body>";

  html += "<div align=\"center\">";
  html += "<h1>Mehedi's Car</h1>";
  html += "<h2>Press \"stop\" after the server has been reset</h2>";
  html += "<br>\n";
  html += "</div>\n";
  
  html += "<form method=\"GET\">";
  html += "<div align=\"center\">";
  html += "<input type=\"button\" value=\"Car stop\" onclick=\"window.location.href='/stop'\">";
  html += "<br>\n";
  
  html += "<input type=\"button\" value=\"Go forward\" onclick=\"window.location.href='/forward'\">";
  html += "<input type=\"button\" value=\"Go backward\" onclick=\"window.location.href='/backward'\">";
  html += "<br>\n";
  
  html += "<input type=\"button\" value=\"Turn left\" onclick=\"window.location.href='/left'\">";
  html += "<input type=\"button\" value=\"Turn right\" onclick=\"window.location.href='/right'\">";
  html += "</div>\n";
  html += "</form>\n";
 
  html += "</body>\n";
  html += "</html>\n";
  return html;
}
