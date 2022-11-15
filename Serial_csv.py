import serial as ser
from time import time
import csv

Arduino = ser.Serial('COM9', 115200)
f = open('data.csv', 'w', newline='')
start_time = time()
t = start_time
while True:
    t = time()
    t_t = t - start_time
    line = Arduino.readline().strip().decode('utf-8')
    line = line.split(',')
    line = [round(t_t, 3)] + line
    print(line)
    writer = csv.writer(f, delimiter=';')
    writer.writerow(line)
    if t_t > 300:
        break

f.close()
Arduino.close()