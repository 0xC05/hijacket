const int sensor1=A0; // Assigning analog pin A1 to variable 'sensor'
const int sensor2=A1;  // Assigning analog pin A1 to variable 'sensor'

float tempc;  //variable to store temperature in degree Celsius
float tempf;  //variable to store temperature in Fahreinheit 
float vout;  //temporary variable to hold sensor reading
void setup()
{
pinMode(sensor1,INPUT); // Configuring pin A1 as input
pinMode(sensor2,INPUT); // Configuring pin A1 as input

Serial.begin(9600);
}
void loop() 
{
vout=analogRead(sensor1);

vout=analogRead(sensor1);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
tempf=(vout*1.8)+32; // Converting to Fahrenheit 

Serial.print("Sensor ar A0 value in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();
Serial.print("in Fahrenheit=");
Serial.print("\t");
Serial.print(tempf);
Serial.println();
 //Delay of 1 second for ease of viewing 

vout=analogRead(sensor2);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
tempf=(vout*1.8)+32; // Converting to Fahrenheit 

Serial.print("Sensor at A1 value in DegreeC=");
Serial.print("\t");
Serial.print(tempc);
Serial.println();
Serial.print("in Fahrenheit=");
Serial.print("\t");
Serial.print(tempf);
Serial.println();
delay(5000); //Delay of 1 second for ease of viewing 


}
