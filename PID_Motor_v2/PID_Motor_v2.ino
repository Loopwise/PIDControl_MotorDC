// Usando el TB6612 hay una pérdida de 0.30V aproximadamente
#include <TimerOne.h>
#include "MotorDC.h"

// MotorDC(int EN1, int EN2, int ENM, int encA, int encB)
MotorDC* Motor75 = new MotorDC(8, 7, 6, 2, 3  );
//MotorDC* Motor85 = new MotorDC(10, 9, 5, 3);

volatile float velocity = 0;
float ratio = 1.0*336743/4500; // Exact gear ratio = 74.83


// PID constants
/*const double P = 1;
const double I = 0.3;
const double D = 0.1;*/

const double P = 1.775;
const double I = 2.25;
const double D = 0.005;

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double velocity_out, setPoint;
double cumError = 0, rateError = 0;

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
    setPoint = 0;
    lastError = setPoint;
    previousTime = millis();
}

void loop(){
    // Serial Plotter
    if(Serial.available())
      setPoint = Serial.readStringUntil('\n').toInt();
    velocity_out = computePID();
    Motor75 -> set_PWM(velocity_out);
    Serial.print(velocity_out);
    Serial.print(',');
    Serial.println(velocity);
    delay(250);
}

double computePID(){
    currentTime = millis();
    elapsedTime = (double)(currentTime-previousTime);

    error = setPoint - velocity; // Proporcional
    cumError += error*elapsedTime/1000.0; // Integral
    rateError = (error - lastError)/elapsedTime*1000.0; // Derivada

    double out = P*error + I*cumError + D*rateError;
    lastError = error;
    previousTime = currentTime;

    if(out > 255)return 255;
    if(out < 0)return 0;
    return out;
}

void ISR75_A(){
  Motor75 -> contA++;
}

void ISR75_B(){
  Motor75 -> contB++;
}

void ISRVelocity(){
  velocity = Motor75 -> get_VelocityA();
}
