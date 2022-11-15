#include <Arduino.h>
#include "MotorDC.h"

MotorDC::MotorDC(){}

MotorDC::MotorDC(int EN1, int EN2, int ENM, int encA, int encB){
    this -> EN1 = EN1;
    this -> EN2 = EN2;
    this -> ENM = ENM;
    this -> encA = encA;
    this -> encB = encB;
}

void MotorDC::begin(float ratio){
    pinMode(this -> EN1, OUTPUT);
    pinMode(this -> EN2, OUTPUT);
    pinMode(this -> ENM, OUTPUT);
    pinMode(this -> encA, INPUT);
    pinMode(this -> encB, INPUT);

    this -> ratio = ratio;
}

void MotorDC::setup(void (*ISR_A)(void), void (*ISR_B)(void)){
    attachInterrupt(digitalPinToInterrupt(this -> encA), ISR_A, RISING);
    attachInterrupt(digitalPinToInterrupt(this -> encB), ISR_B, RISING);

    interrupts();
}

void MotorDC::start(bool state){
  digitalWrite(this -> EN1, state);
  digitalWrite(this -> EN2, !state);
  digitalWrite(this -> ENM, LOW);
}



int MotorDC::get_encA(){
    return digitalRead(this -> encA);
}

int MotorDC::get_encB(){
    return digitalRead(this -> encB);
}

void MotorDC::set_PWM(int value){
  analogWrite(this->ENM, value);
}

float MotorDC::get_VelocityA(){
  float tMax = 100;
  if(millis() - (this -> t) > tMax){
    noInterrupts();
    this -> velocityA = 1.0*(this -> contA)/(this->ratio*this->ppr); // Revoluciones en tms
    this -> velocityA *= 60.0*1000/(millis()- (this -> t)); // 
    this -> t = millis();
    this -> contA = 0;
    interrupts();
  }
  return this -> velocityA;
}

float MotorDC::get_VelocityB(){
  float tMax = 100;
  if(millis() - (this -> t) > tMax){
    noInterrupts();
    this -> velocityB = 1.0*(this -> contB)/(this->ratio*this->ppr); // Revoluciones en tms
    this -> velocityB *= 60.0*1000/(millis() - (this -> t)); // 
    this -> t = millis();
    this -> contB = 0;
    interrupts();
  }
  return this -> velocityB;
}
