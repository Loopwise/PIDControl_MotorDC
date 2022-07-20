clc; clear; close all;
load('Estimation.mat');

num = tf1.Structure.Numerator.Value;
den = tf1.Structure.Denominator.Value;
sys = tf(num, den)