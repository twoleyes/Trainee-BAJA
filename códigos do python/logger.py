import serial
porta = "COM4"
baud = 9600
arquivo = "logger.csv"

ser = serial.Serial(porta,baud)
ser.flushInput()

data = str(ser.readline().decode("utf"))
print(data)

file = open(arquivo, "a")
file.write(data)
file.close()

amostra = 20
linha = 0 

ser = serial.Serial(porta,baud)
ser.flushInput()

while linha <= amostra:

    print(data)
    file = open(arquivo, "a")
    file.write(data)
    linha = linha + 1

file.close()
ser.close()

