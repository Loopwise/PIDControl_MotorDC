// Usando el TB6612 hay una pérdida de 0.30V aproximadamente
#include <TimerOne.h>
#include "MotorDC.h"
#include "PID.h"

// MotorDC(int EN1, int EN2, int ENM, int encA, int encB)
MotorDC* Motor75 = new MotorDC(11, 8, 7, 3, 2);
volatile float velocity = 0;
//float ratio = 1.0*336743/4500; // Exact gear ratio = 74.83
float ratio = 30.0;

// PID constants
int setPoint = 0;
//PID *PID_75 = new PID(1, 0.3, 0.1);
PID *PID_75 = new PID(2, 0.5, 0.1);

/*
const double P = 1.44262631098083;
const double I = 0.407578521547111;
const double D = 1.26530066820265;*/

void setup(){
    // Configuramos la interrupción timer1 para la ejecución constante de la velocidad
    Timer1.initialize(100000);
    Timer1.attachInterrupt(ISRVelocity);
    
    Motor75 -> begin(ratio);
    Motor75 -> setup(ISR75_A, ISR75_B);
    Motor75 -> start(true);
    Serial.begin(9600);
    delay(5000);

    // Inicializamos los primeros PID
    PID_75 -> Link(&velocity);
}

volatile float v_out = 0;

void loop(){
    // Serial Plotter
    if(Serial.available()){
      setPoint = Serial.readStringUntil('\n').toInt();
      PID_75 -> set_Point(setPoint);
    }
    Motor75 -> set_PWM(v_out);
    Serial.print(v_out);
    Serial.print(',');
    Serial.println(velocity);
    delay(250);
}

void ISR75_A(){
  Motor75 -> contA++;
}

void ISR75_B(){
  Motor75 -> contB++;
}

void ISRVelocity(){
  velocity = Motor75 -> get_VelocityA();
  v_out = PID_75 -> compute();
}
