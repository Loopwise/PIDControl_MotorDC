clc; clear; close all;

In = xlsread('Datos.xlsx', 'A781:A1050');
Out = xlsread('Datos.xlsx', 'B781:B1050');

hold on
plot(In)
plot(Out)
title('SetPoint & Output')
legend('SetPoint', 'Output')