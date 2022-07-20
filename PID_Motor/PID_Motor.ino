#include <TimerOne.h>
#include "MotorDC.h"

// MotorDC(int EN1, int EN2, int ENM, int encA, int encB)
MotorDC Motor75(7, 8, 6, 3, 2);
volatile float velocity = 0;
float ratio = 1.0*336743/4500; // Exact gear ratio = 74.83


// PID constants
const double P = 1;
const double I = 0.3;
const double D = 0.1;

/*
const double P = 1.44262631098083;
const double I = 0.407578521547111;
const double D = 1.26530066820265;*/

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
    
    Motor75.begin(ratio);
    Motor75.start(true);
    Serial.begin(9600);
    delay(5000);

    // Inicializamos los primeros PID
    setPoint = 80;
    lastError = setPoint;
    previousTime = millis();
}

void loop(){
    // Serial Plotter
    velocity_out = computePID();
    Motor75.set_PWM(velocity_out);
    Serial.print(velocity_out);
    Serial.print(',');
    Serial.println(velocity);
    delay(250);
}

double computePID(){
    currentTime = millis();
    elapsedTime = (double)(currentTime-previousTime);

    error = setPoint - velocity;
    cumError += error;
    rateError = (error - lastError);

    double out = P*error + I*cumError + D*rateError;
    lastError = error;
    previousTime = currentTime;

    if(out > 255)return 255;
    if(out < 66)return 0;
    return out;
}

void ISRVelocity(){
  velocity = Motor75.get_VelocityB();
}
