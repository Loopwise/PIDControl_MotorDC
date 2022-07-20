clc; clear; close all;

In = xlsread('data.csv', 'B1:B5900');
Out = xlsread('data.csv', 'C1:C5900');

hold on
plot(In)
plot(Out)
title('SetPoint & Output')
legend('SetPoint', 'Output')