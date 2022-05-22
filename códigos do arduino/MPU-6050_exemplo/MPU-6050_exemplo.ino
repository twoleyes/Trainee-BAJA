#include<Wire.h>  //essa biblioteca permite comunicar com dispositivos que usam protocolo de comunicação I2C

const int MPU = 0x68; //endereço I2C em hexadecimal(0x##) do sensor MPU-6050


int girX, girY, girZ, acelX, acelY, acelZ, temperatura;  //variáveis do sensor 


void setup() {
  Serial.begin(9600);

  //inicializando a bilbioteca wire
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  
  //inicializando o sensor
  Wire.write(0); 
  Wire.endTransmission(true);

  //Configurando fundo de escala do giroscópio
  /*
    Wire.write(0b00000000); //fundo de escala em +/- 250º/s
    Wire.write(0b00001000); //fundo de escala em +/- 500º/s
    Wire.write(0b00010000); //fundo de escala em +/- 1000º/s
    Wire.write(0b00011000); //fundo de escala em +/- 2000º/s
  */
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0b00011000);
  Wire.endTransmission();

  //Configurando fundo de escala do acelerômetro
  /*
    Wire.write(0b00000000); //fundo de escala em +/- 2g
    Wire.write(0b00001000); //fundo de escala em +/- 4g
    Wire.write(0b00010000); //fundo de escala em +/- 8g
    Wire.write(0b00011000); //fundo de escala em +/- 16g
  */
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0b00011000);
  Wire.endTransmission();
}

void loop() {
  //Começa uma transmissão com o sensor
  Wire.beginTransmission(MPU);

  //Enfilera os bytes a ser transmitidos para o sensor
  //Começando com o registor 0x3B
  Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)

  //Finaliza e transmite os dados para o sensor. O false fará com que seja enviado uma mensagem 
  //de restart e o barramento não será liberado
  Wire.endTransmission(false);

  //Solicita os dados do sensor, solicitando 14 bytes (7 variáveis), o true fará com que o barramento seja liberado após a solicitação 
  //(o valor padrão deste parâmetro é true)
  Wire.requestFrom(MPU, 14, true);  
  
  //Armazena o valor dos sensores nas variaveis correspondentes
  acelX = Wire.read()<< 8|Wire.read();  //0x3B (ACCEL_XOUT_HIGH) & 0x3C (ACCEL_XOUT_LOW)  
  acelY = Wire.read()<< 8|Wire.read();  //0x3D (ACCEL_YOUT_HIGH) & 0x3E (ACCEL_YOUT_LOW)  
  acelZ = Wire.read()<< 8|Wire.read();  //0x3F (ACCEL_ZOUT_HIGH) & 0x40 (ACCEL_ZOUT_LOW)

  temperatura = Wire.read()<< 8|Wire.read();  //0x41 (TEMP_OUT_HIGH) & 0x42 (TEMP_OUT_LOW)

  girX = Wire.read()<< 8|Wire.read();  //0x43 (GYRO_XOUT_HIGH) & 0x44 (GYRO_XOUT_LOW)     
  girY = Wire.read()<< 8|Wire.read();  //0x45 (GYRO_YOUT_HIGH) & 0x46 (GYRO_YOUT_LOW)
  girZ = Wire.read()<< 8|Wire.read();  //0x47 (GYRO_ZOUT_HIGH) & 0x48 (GYRO_ZOUT_LOW)

  //Imprime no serial os valores obtidos
  /*
  Alterações devem ser feitas com base no fundo de escala escolhido
    Acelerômetro
    +/- 2g
    +/- 4g
    +/- 8g
    +/- 16g

    Giroscópio
    +/- 250º/s = 131
    +/- 500º/s = 65.6
    +/- 1000º/s = 32.8
    +/- 2000º/s = 16.4
  */

  //Printa o valor X do acelerômetro na serial
  Serial.print("Acelerômetro X = "); 
  Serial.print(acelX/2048);
 
  //Printa o valor Y do acelerômetro na serial
  Serial.print(" \tY = "); 
  Serial.print(acelY/2048);
   
  //Printa o valor Z do acelerômetro na serial
  Serial.print(" \tZ = "); 
  Serial.println(acelZ/2048);

  //Printa o valor X do giroscópio na serial
  //  Serial.print("Giroscópio X = "); 
  //  Serial.print(girX);
  //   
  //  //Printa o valor Y do giroscópio na serial
  //  Serial.print(" \tY = "); 
  //  Serial.print(girY);
  //   
  //  //Printa o valor Z do giroscópio na serial
  //  Serial.print(" \tZ = "); 
  //  Serial.println(girZ); 
  
  //  //Printa o valor da temperatura na serial, calculando em graus celsius
  //  Serial.print("Temperatura = "); 
  //  Serial.println(temperatura / 340.00 + 36.53);

  delay(100);  //delay de 200ms a cada ciclo do loop
}
