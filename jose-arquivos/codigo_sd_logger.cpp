#include <SPI.h>
#include <SD.h>

const int chipSelect = 10;		//cs or cc pin
int temp = 1, vel = 2, cont = 0;	//test variables

File dataFile;

void setup()
{

 // open serial communications and wait for port to open
  Serial.begin(9600);

  Serial.print("Initializing SD card...");
  
  // make sure that the default chip select pin is set to output, even if you don't use it:
  pinMode(chipSelect, OUTPUT);
  
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present, please restart!");
    // don't do anything
    while (1) ;
  }
  Serial.println("card initialized.");
  
  // Open up the file we're going to log to!
  dataFile = SD.open("file.txt", FILE_WRITE);	// here we can use the EEPROOM to change our file name and keep information on the same cicle
  if (! dataFile) {
    Serial.println("Error opening file.txt");
    // Wait forever since we cant write data
    while (1) ;
  }

  dataFile.print("Velocity");
  dataFile.print(",");
  dataFile.println("Temperature");	// same line break as Serial.println -- very usefull
 
}

void loop()
{
  
  vel += 1;
  temp += 2;
  
  dataFile.print(vel);
  dataFile.print(",");
  dataFile.println(temp);
  Serial.println("Colected:" + cont);

  dataFile.flush();
  
  delay(500);

  cont++;

  if(cont == 30){
    Serial.println("Finished");
    dataFile.close();
    while(1);
  }
  

}
