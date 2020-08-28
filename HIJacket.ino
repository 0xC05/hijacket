#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading


BluetoothSerial SerialBT;

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 

int DSMpin = 16;//DSM501A input D8

int MQpin = 34; //MQ Pin
const int sensor1=12; // LM35 Sensor 1
const int sensor2=13;  // LM35 Sensor 2

int sensorValue;

byte buff[2];

long oldValue=0;
long newValue =0;
long valueToShow = 0;


unsigned long duration;
unsigned long starttime;
unsigned long endtime;
unsigned long sampletime_ms = 10000;
unsigned long lowpulseoccupancy = 0;
float ratio = 0;
float concentration = 0;
 
void setup() {  
  SerialBT.begin("Hi-jack it"); //Bluetooth device name
//                
  Serial.begin(115200);
 
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  
  // Clear the buffer.
  display.clearDisplay();

  
  display.setTextSize(1);
  
  
  display.setTextColor(WHITE);
  
  display.setCursor(0,0);
  
pinMode(sensor1,INPUT); // Configuring pin A1 as input
pinMode(sensor2,INPUT); // Configuring pin A1 as input


  starttime = millis(); 
  
  

}
 
 
void loop() {
   
 duration = pulseIn(DSMpin, LOW);
  lowpulseoccupancy += duration;
  endtime = millis();
  if ((endtime-starttime) > sampletime_ms)
  {
    oldValue = newValue;
    ratio = (lowpulseoccupancy-endtime+starttime + sampletime_ms)/(sampletime_ms*10.0);  // Integer percentage 0=>100
    concentration = (1.1 * pow( ratio, 3) - 3.8 *pow(ratio, 2) + 520 * ratio + 0.62)/100; 
    newValue = concentration;
    if(newValue - oldValue > 100 || newValue - oldValue < -100  ){
      valueToShow = oldValue;
    }else{
      valueToShow = newValue;
    }
    lowpulseoccupancy = 0;
    starttime = millis(); 
     display.clearDisplay();
    display.setCursor(0,0);
     
    display.print("PM value: " + String(valueToShow));
    display.setCursor(0,15);
    display.print("air sensor: "+ String(analogRead(MQpin)/40.95)+"%");
    display.display();
  
vout=analogRead(sensor1);

vout=analogRead(sensor1);
vout=(vout*500)/4095;
tempc=vout; // Storing value in Degree Celsius

Serial.print("Sensor ar A0 value in DegreeC=");
Serial.print("\t");
Serial.println(tempc);
 //Delay of 1 second for ease of viewing 

vout=analogRead(sensor2);
vout=(vout*500)/4095;
tempf=vout; // Storing value in Degree Celsius

Serial.print("Sensor at A1 value in DegreeC=");
Serial.print("\t");
Serial.print(tempf);
Serial.println();
    

  starttime = millis(); 

    String s = "*" +String(concentration) + "#" +String(analogRead(MQpin)/40.95) + "#" + String(tempc)+ "#"+ String(tempf) + "~";
    SerialBT.print(s);


    
  }
 }
