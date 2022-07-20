#include <TimerOne.h>
#include "MotorDC.h"

// MotorDC(int EN1, int EN2, int ENM, int encA, int encB)
MotorDC Motor75(7, 8, 6, 3, 2);
volatile float velocity = 0;
float ratio = 1.0*336743/4500; // Exact gear ratio = 74.83


void setup(){
    // Configuramos la interrupción timer1 para la ejecución constante de la velocidad
    Timer1.initialize(100000);
    Timer1.attachInterrupt(ISRVelocity);
    
    Motor75.begin(ratio);
    Motor75.start(true);
    Serial.begin(9600);
    delay(5000);
}

void loop(){
    // Serial Plotter
    for(int i = 160; i <= 255; i+=5){
      Motor75.set_PWM(i);
      for(int j= 0; j < 10; j++){
        Serial.print(map(i,0, 255, 0, 130));
        Serial.print(",");
        Serial.println(velocity);
        delay(250);
      }
    }
}

void ISRVelocity(){
  velocity = Motor75.get_VelocityB();
}
