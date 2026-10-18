#include <ESP32Servo.h>
#include <Bluepad32.h>

Servo Servo1;
Servo Servo2;
Servo Servo3;
Servo Servo4;
Servo Servo5;
Servo Servo6;

ControllerPtr Controller;

int WristRotationAngle = 90;
int ClawAngle = 90;

void Connected(ControllerPtr ctl){
  Controller = ctl;
}

void Disconnected(ControllerPtr ctl){
  Controller = nullptr;
}

void setup() {
  Servo1.attach(21, 500, 2500);
  Servo2.attach(5, 500, 2500);
  Servo3.attach(18, 500, 2500);
  Servo4.attach(19, 500, 2500);
  Servo5.attach(4);
  Servo6.attach(22);

  BP32.setup(&Connected, &Disconnected);
  BP32.forgetBluetoothKeys();
}

void loop() {
  BP32.update();

  if(Controller && Controller->isConnected()){

    int BaseAngle = map(Controller->axisX(), -512, 512, 0, 270);
    Servo1.write(BaseAngle);

    int SholderAngle = map(Controller->axisY(), -512, 512, 0, 270);
    Servo2.write(SholderAngle);

    int ElbowAngle = map(Controller->axisRY(), -512, 512, 0, 270);
    Servo3.write(ElbowAngle);

    int WristAngle = map(Controller->axisRX(), -512, 512, 0, 270);
    Servo4.write(WristAngle);

 
    if(Controller->a()){
      WristRotationAngle++;
    }
    if(Controller->b()){
      WristRotationAngle--;
    }
    WristRotationAngle = constrain(WristRotationAngle, 0, 180);
    Servo5.write(WristRotationAngle);

    if(Controller->y()){
      ClawAngle++;
    }
    if(Controller->x()){
      ClawAngle--;
    }
    ClawAngle = constrain(ClawAngle, 0, 180);
    Servo6.write(ClawAngle);
    
    delay(15); 
  }
}
