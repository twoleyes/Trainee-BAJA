import serial
import matplotlib.pyplot as ply
import numpy 
import pylab as py
from drawnow import *

 ACCX = []
 ACCY = []


 arduinodata=serial.Serial('COM4',9600) #port name and baud rate

 ply.ion()


 def makeplotting():

    ply.ylabel('ACCX (°/sec)')
    ply.xlabel('Time')
    ply.plot(ACCX)


 while True:
    while(arduinodata.inWaiting()==0):
            pass
    arduinostring=arduinodata.readline()
    arduinostring=str(arduinostring,encoding="utf-8")
    dataArray=arduinostring.split(',')        
    accxtemp=float(dataArray[0])
    ACCX.append(accxtemp)
    drawnow(makeplotting)






