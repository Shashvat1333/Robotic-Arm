#include <Bluepad32.h>
#include <ESP32Servo.h>

Servo Servo1; Servo2; Servo3; Servo4; Servo5; Servo6;

ControllerPtr Controller = nullptr; 

const int DEADBAND = 50; 

int Pos1 = 1500;
int Pos2 = 1500;
int Pos3 = 1500;
int Pos4 = 1500;
int Pos5 = 1500;
int Pos6 = 1500;

unsigned long lastUpdate = 0;

void Connected(ControllerPtr ctl){
  Controller = ctl;
}

void Disconnected(ControllerPtr ctl){
  Controller = nullptr;
}

void setup() {
  Serial.begin(115200);

  Servo1.attach(21, 500, 2500);
  Servo2.attach(5, 500, 2500);
  Servo3.attach(18, 500, 2500);
  Servo4.attach(19, 500, 2500);
  Servo5.attach(4, 500, 2500);
  Servo6.attach(22, 500, 2500);

  Servo1.writeMicroseconds(Pos1);
  Servo2.writeMicroseconds(Pos2);
  Servo3.writeMicroseconds(Pos3);
  Servo4.writeMicroseconds(Pos4);
  Servo5.writeMicroseconds(Pos5);
  Servo6.writeMicroseconds(Pos6);

  BP32.setup(&Connected, &Disconnected);
  BP32.forgetBluetoothKeys(); 
}

void loop() {
  BP32.update();

  if (Controller && Controller->isConnected()) {

    if (millis() - lastUpdate > 20) {
      lastUpdate = millis();

      int axisX = Controller->axisX();
      if (axisX > DEADBAND) {
        Pos1 = 1700;
      } else if (axisX < -DEADBAND) {
        Pos1 = 1300;
      } else {
        Pos1 = 1500;
      }
      Servo1.writeMicroseconds(Pos1);

      int axisY = Controller->axisY();
      if (axisY > DEADBAND) {
        Pos2 = 1700;
      } else if (axisY < -DEADBAND) {
        Pos2 = 1300;
      } else {
        Pos2 = 1500;
      }
      Servo2.writeMicroseconds(Pos2);

      int axisRY = Controller->axisRY();
      if (axisRY > DEADBAND) {
        Pos3 = 1700;
      } else if (axisRY < -DEADBAND) {
        Pos3 = 1300;
      } else {
        Pos3 = 1500;
      }
      Servo3.writeMicroseconds(Pos3);

      int axisRX = Controller->axisRX();
      if (axisRX > DEADBAND) {
        Pos4 = 1700;
      } else if (axisRX < -DEADBAND) {
        Pos4 = 1300;
      } else {
        Pos4 = 1500;
      }
      Servo4.writeMicroseconds(Pos4);

      if (Controller->a()) {
        Pos5 = 1700;
      } else if (Controller->b()) {
        Pos5 = 1300;
      } else {
        Pos5 = 1500;
      }
      Servo5.writeMicroseconds(Pos5);

      if (Controller->y()) {
        Pos6 = 1700;
      } else if (Controller->x()) {
        Pos6 = 1300;
      } else {
        Pos6 = 1500;
      }
      Servo6.writeMicroseconds(Pos6);
    }

  } else {
    Servo1.writeMicroseconds(1500);
    Servo2.writeMicroseconds(1500);
    Servo3.writeMicroseconds(1500);
    Servo4.writeMicroseconds(1500);
    Servo5.writeMicroseconds(1500);
    Servo6.writeMicroseconds(1500);
  }
  
  delay(10); 
}
