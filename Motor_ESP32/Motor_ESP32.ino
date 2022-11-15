#include "MotorDC.h"

// MotorDC(int EN1, int EN2, int ENM, int encA, int encB)
MotorDC Motor75(25, 26, 27, 18, 19);
volatile float velocity = 0;
float ratio = 1.0*336743/4500; // Exact gear ratio = 74.83


// PID constants
const double P = 1;
const double I = 0.3;
const double D = 0.1;

/*const double P = 2.23284233711159;
const double I = 0.4413065399803;
const double D = 2.82433209726537;*/

unsigned long currentTime, previousTime;
double elapsedTime;
double error;
double lastError;
double velocity_out, setPoint;
double cumError = 0, rateError = 0;


void setup(){   
    Motor75.begin(ratio);
    Motor75.start(true);
    Serial.begin(115200);
    delay(5000);

    // Inicializamos los primeros PID
    setPoint = 0;
    lastError = setPoint;
    previousTime = millis();
}

void loop(){
    if(Serial.available())
      setPoint = (Serial.readString()).toDouble();
    velocity = Motor75.get_VelocityB();
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
    if(out < 60)return 0;
    return out;
}
