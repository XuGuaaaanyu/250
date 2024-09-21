#include <SoftwareSerial.h>
#include <Servo.h>

//base plate rotation motor (RMotor) pin definitions
const int RMotor_RPWM = 8; 
const int RMotor_LPWM = 9;
const int RMotor_REN = 30;
const int RMotor_LEN = 31;
//X-shape lifter motor (LMotor) pin definitions
const int LMotor_RPWM = 11;
const int LMotor_LPWM = 10;
const int LMotor_REN = 29;
const int LMotor_LEN = 28;
//Cantilever screw motor (SMotor) pin definitions
const int SMotor_RPWM = 5;
const int SMotor_LPWM = 4;
const int SMotor_REN = 35;
const int SMotor_LEN = 34;
//Pump motor (PMotor) pin definitions
const int PMotor_RPWM = 6;
const int PMotor_LPWM = 7;
const int PMotor_REN = 32;
const int PMotor_LEN = 33;

const int Relay = 36; //Relay signal pin
const int servoPin = 12;//Servo signal pin

Servo myServo;

char input;
int pos;

void setup() 
{
  Serial.begin(9600);
  Serial3.begin(9600);
  myServo.attach(servoPin);
  myServo.write(115); //initialize servo position
  Serial.println("Welcome to VM250 Project!");
  for (int i = 4; i <= 11; i++)
  {
    pinMode(i,OUTPUT);
    analogWrite(i,0);
  }
  for (int i = 28; i <= 35; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  pinMode(Relay,OUTPUT);
  digitalWrite(Relay,LOW);
}


void loop() 
{
  if (Serial3.available() > 0) 
  {
    input = Serial3.read();
    Serial.print("Char received:");
    Serial.println(input);
    pos = myServo.read();
    Serial.print("The Position of the servo:");
    Serial.println(pos);

    if (input == 's') //Bottom plate turn clockwise
    {
      analogWrite(RMotor_RPWM,255);
      analogWrite(RMotor_LPWM,0);
    }
    if (input == 'n') //Bottom plate turn counter-clockwise
    {
      analogWrite(RMotor_RPWM,0);
      analogWrite(RMotor_LPWM,255);
    }
    if (input == 'i') //Horizontal move inward
    {
      analogWrite(SMotor_RPWM,0);
      analogWrite(SMotor_LPWM,255);
    }
    else if (input == 'o') //Horizontal move outward
    {
      analogWrite(SMotor_RPWM,255);
      analogWrite(SMotor_LPWM,0);
    }
    if (input == 'u') //Platform move up
    {
      analogWrite(LMotor_RPWM,0);
      analogWrite(LMotor_LPWM,255);
    }
    else if (input == 'd') //Platform move down
    {
      analogWrite(LMotor_RPWM,255);
      analogWrite(LMotor_LPWM,0);
    }
    else if (input == 'b') //open the pump
    {
      analogWrite(PMotor_RPWM,0);
      analogWrite(PMotor_LPWM,255);
    }
    else if (input == 'a') //release gas
    {
      digitalWrite(Relay,HIGH);
    }
    else if (input == 'c') //close the pump
    {
      analogWrite(PMotor_RPWM,0);
      analogWrite(PMotor_LPWM,0);
    }
    else if (input == 'l') // Servo rotate clockwise
    {
      while (pos < 160) 
      {
        myServo.write(pos + 1);
        pos = myServo.read();
        delay(10);
        if (Serial3.available() ) 
        {
          input = Serial3.read();
          Serial.println(input);
          break;
        }
      }
    }
    else if (input == 'r') //Servo rotate conter clockwise
    {
      while (pos > 20) 
      {
        myServo.write(pos - 1);
        pos = myServo.read();
        delay(10);
        if (Serial3.available() > 0) 
        {
          input = Serial3.read();
          Serial.println(input);
          break;
        }
      }

    }
    else if (input == '0')
    {
      analogWrite(RMotor_RPWM,0);
      analogWrite(RMotor_LPWM,0);
      analogWrite(LMotor_RPWM,0);
      analogWrite(LMotor_LPWM,0);
      analogWrite(SMotor_RPWM,0);
      analogWrite(SMotor_LPWM,0);
      digitalWrite(Relay,LOW);
    }
  }
}


