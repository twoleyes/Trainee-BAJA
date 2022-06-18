import serial.tools.list_ports
import serial

ports = serial.tools.list_ports.comports
serialInst = serial.Serial()

portList = []

arquivo = "mpu6050.csv"

for onePort in ports():
    portList.append(str(onePort))
    print(str(onePort))

val = input("select Port: COM")

for x in range (0,len(portList)):
    if portList[x].startswith("COM" + str(val)):
        portVar = "COM" + str(val)
        print(portList[x])

serialInst.baudrate = 9600
serialInst.port = portVar
serialInst.open()

amostra = 200
linha = 0 

while linha <= amostra:
    packet = serialInst.readline()
    print(packet.decode('utf').rstrip('\n'))
    file = open(arquivo, "a")
    file.write(packet.decode('utf').rstrip('\n'))

file.close()
serialInst.close()







