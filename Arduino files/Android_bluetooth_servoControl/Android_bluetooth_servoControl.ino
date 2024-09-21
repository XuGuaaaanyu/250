#include <SoftwareSerial.h>
#include <Servo.h>

int bluetoothRX=10;
int bluetoothTX=11;
char input = 0;
Servo myservo;
int pos = 0;

SoftwareSerial bluetooth(bluetoothRX,bluetoothTX);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  bluetooth.begin(9600);
  myservo.attach(6);
  // myservo.write(90);
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (bluetooth.available() > 0) {
    input = bluetooth.read();
    pos = myservo.read();
    Serial.println(input);
    //wxbit->app on phone;app->bluetooth->arduino->servo motor
    //Name:HC-02
    if (input == 'l') {//https://app.wxbit.com/?locale=en#960721
      while (pos < 175) {
        myservo.write(pos + 1);
        pos = myservo.read();
        delay(10);

        if (bluetooth.available() > 0) {
          input = bluetooth.read();
          Serial.println(input);
          break;
        }
      }
    }

    else if (input == 'r') {
      while (pos > 5) {
        myservo.write(pos - 1);
        pos = myservo.read();
        delay(10);

        if (bluetooth.available() > 0) {
          input = bluetooth.read();
          Serial.println(input);
          break;
        }
      }
    }
  }
}