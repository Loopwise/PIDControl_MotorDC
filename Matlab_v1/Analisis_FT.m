clc; clear; close all;
load('Datos.mat');

num = MotorDC.Structure.Numerator.Value;
den = MotorDC.Structure.Denominator.Value;
sys = tf(num, den)