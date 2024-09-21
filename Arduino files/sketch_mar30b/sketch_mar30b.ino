#include <SoftwareSerial.h>
#include <Servo.h>


const int TXD = 15; //connect TXD pin on HC-02 module to pin 2 on Arduino MEGA (RX3)
const int RXD = 14; //connect RXD pin on HC-02 module to pin 3 on Arduino MEGA (TX3)
const int RMotorP = 35;
const int RMotorN = 37; //Bottom Turnplate Motor (RMotoe)
//const int RMotorEn= 6; //Bottom Turnplate Motor PWM
const int HMotorP = 5;
const int HMotorN = 6; //Platform Up/Down Motor (HMotor)
const int SMotorP = 31;
const int SMotorN = 33; //Sliding Screw Motor (SMotor)
const int PumpP = 8;
const int PumpN = 9; //Air pump Motor (Pump)
//const int PumpEn= 10; //Air pump Motor PWM
const int Relay = 39; //Relay digital pin
const int servoPin = 7;
Servo myServo;

char input;
int pos;

void setup() 
{
  Serial.begin(9600);
  Serial3.begin(9600);
  myServo.attach(servoPin);
  myServo.write(115);
  Serial.println("Bluetooth - Button test");
  pinMode(RMotorP,OUTPUT); pinMode(RMotorN,OUTPUT);
  pinMode(HMotorP,OUTPUT); pinMode(HMotorN,OUTPUT);
  pinMode(SMotorP,OUTPUT); pinMode(SMotorN,OUTPUT);
  pinMode(PumpP,OUTPUT); pinMode(PumpN,OUTPUT);
  pinMode(Relay,OUTPUT);
  digitalWrite(RMotorP,LOW); digitalWrite(RMotorN,LOW);
  digitalWrite(HMotorP,LOW); digitalWrite(HMotorN,LOW);
  digitalWrite(SMotorP,LOW); digitalWrite(SMotorN,LOW);
  digitalWrite(PumpP,LOW); digitalWrite(PumpN,LOW);
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
      digitalWrite(RMotorP,HIGH);
      digitalWrite(RMotorN,LOW);
    }
    if (input == 'n') //Bottom plate turn counter-clockwise
    {
      digitalWrite(RMotorP,LOW);
      digitalWrite(RMotorN,HIGH);
    }
    if (input == 'l') //Horizontal move left
    {
      digitalWrite(SMotorP,HIGH);
      digitalWrite(SMotorN,LOW);
    }
    else if (input == 'r') //Horizontal move right
    {
      digitalWrite(SMotorP,LOW);
      digitalWrite(SMotorN,HIGH);
    }
    if (input == 'u') //Horizontal move left
    {
      digitalWrite(HMotorP,HIGH);
      digitalWrite(HMotorN,LOW);
    }
    else if (input == 'd') //Horizontal move right
    {
      digitalWrite(HMotorP,LOW);
      digitalWrite(HMotorN,HIGH);
    }
    else if (input == 'b')
    {
      digitalWrite(PumpP,HIGH);
      digitalWrite(PumpN,LOW);
    }
    else if (input == 'h')
    {
      digitalWrite(PumpP,LOW);
      digitalWrite(PumpN,LOW);
    }
    else if (input == 'p') // Servo rotate clockwise
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
    else if (input == 'm') //Servo rotate conter clockwise
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
      digitalWrite(Relay,LOW);
      digitalWrite(SMotorP,LOW);
      digitalWrite(SMotorN,LOW);
      digitalWrite(RMotorP,LOW);
      digitalWrite(RMotorN,LOW);
      digitalWrite(HMotorP,LOW);
      digitalWrite(HMotorN,LOW);
    }
  }
}
