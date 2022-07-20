#include "MotorDC.h"

// MotorDC(int EN1, int EN2, int ENM, int encA, int encB)
MotorDC Motor75(25, 26, 27, 18, 19);
volatile float velocity = 0;
float ratio = 1.0*336743/4500; // Exact gear ratio = 74.83

void setup(){   
    Motor75.begin(ratio);
    Motor75.start(true);
    Serial.begin(115200);
    delay(5000);
}

void loop(){
  Motor75.set_PWM(255);
  for(int j = 0; j < 100; j++){
    velocity = Motor75.get_VelocityB();
    Serial.print(130);
    Serial.print(',');
    Serial.println(velocity);
    delay(50);
  }

  Motor75.set_PWM(0);
  for(int j = 0; j < 100; j++){
    velocity = Motor75.get_VelocityB();
    Serial.print(0);
    Serial.print(',');
    Serial.println(velocity);
    delay(50);
  }
}
