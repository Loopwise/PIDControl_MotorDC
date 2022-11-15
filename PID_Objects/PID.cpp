#include "PID.h"
#include <Arduino.h>

PID::PID(){};

PID::PID(double Kp, double Ki, double Kd){
  this -> Kp = Kp;
  this -> Ki = Ki;
  this -> Kd = Kd;
}

PID::PID(double Kp, double Ki, double Kd, volatile float *Variable){
  this -> Kp = Kp;
  this -> Ki = Ki;
  this -> Kd = Kd;
  this -> Variable = Variable;
}

void PID::set_Point(double SetPoint){
  this -> SetPoint = SetPoint;
}

void PID::Link(volatile float *Variable){
  this -> Variable = Variable;
}

void PID::begin(){
  this -> t0 = millis();
}

double PID::compute(){
  this -> t1 = millis();
  
  float dt = 1.0*((this -> t1) - (this -> t0))/1000;

  this -> last_error = this -> error;
  this -> error = (this -> SetPoint) - *(this -> Variable);
  this -> accum_error += (this -> error)*dt;
  this -> rate_error = ((this -> error) - (this -> last_error))/dt;
  
  double value = (this -> Kp)*(this -> error) + (this -> Ki)*(this -> accum_error) + (this -> Kd)*(this -> rate_error);
  this -> t0 = millis();
  return value;
}
