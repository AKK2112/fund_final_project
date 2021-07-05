/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Labs/fund_final_project/src/fund_final_project.ino"

#include "oled-wing-adafruit.h"
#include "Wire.h"
#include "SparkFun_VCNL4040_Arduino_Library.h"
#include "blynk.h"

void setup();
void loop();
#line 7 "d:/Labs/fund_final_project/src/fund_final_project.ino"
SYSTEM_THREAD(ENABLED);
OledWingAdafruit display;
VCNL4040 proximitySensor;


int red = D5;
int green = D6;
int blue = D7;
uint16_t potValue;
uint16_t lowValue;
uint16_t highValue;
uint16_t lightValuesSet;

uint16_t tempPin = A4;

double temperatureC = 0.0;

double temperatureF = 0.0;
void setup() {
  //identifies the led output pins
  pinMode(A4, INPUT); //tmp 36 sensor
  pinMode(A5,INPUT); //potentiometer
  pinMode(D2,INPUT); //button
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT); //green light
  pinMode(D6, OUTPUT); //yellow light
  pinMode(D7, OUTPUT); // blue light
  Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090);
  Serial.begin(9600);
    display.setup();
    display.clearDisplay();
    display.display();
  proximitySensor.begin(); //turns on the proximity sensor
  Wire.begin(); //Join i2c bus

}

void loop()  {
Blynk.run();
  display.loop();  
 //prints the value the sensor is getting to the serial monitor. 
uint16_t potValue;
potValue = analogRead(A5);

  //when button A is pressed, it will aquire the current value from the proiximity sensor and print that on the OLED display
if(display.pressedA());
   if (digitalRead(D2) == 0){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Starting Calibration");
    display.println("Set your low light.");
    display.display();
    delay(5000);
    
    lowValue = analogRead(A5);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("Low value is: ");
    display.print(lowValue);
    display.display();
    delay(2000);
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.println("Set your high light.");
    display.display();
    delay(4000);
  
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    highValue = analogRead(A5);
    display.print("High light value is: ");
    display.print(highValue);
    display.println();
    display.print("Potentiometer calibrated.");
    display.display();
    delay(2500);
    display.clearDisplay();
    display.display();
    lightValuesSet = true;

}

proximitySensor.powerOnAmbient();
unsigned int ambientValue = proximitySensor.getAmbient(); 
Serial.print("Ambient light level: ");
Serial.println(ambientValue);
delay(10);

if (ambientValue < lowValue)
    {
      digitalWrite(D5, HIGH);
      Blynk.notify("Ambient light went under the Low light Value!!!");
    } 
      else {
      digitalWrite(D5, LOW);//if the value isnt met, the light remains off.
    }
  
    //when the proximity value is greater than 8 and less than 100, it will turn on pin D6 

  if (ambientValue > lowValue && ambientValue < highValue) 
    {
      digitalWrite(D6, HIGH);
      Blynk.notify("Ambient light is inbetween the two setpoints!!!");
    } 
      else {
      digitalWrite(D6, LOW); //if the value isnt met, the light remains off. 
    }
 
   //when the proximity value is greater than 100, it will turn on pin D7

  if (ambientValue > highValue) 
    {
      digitalWrite(D7 ,HIGH);
      Blynk.notify("Ambient light went over the High light Value!!!");
    } 
      else {
      digitalWrite(D7, LOW);//if the value isnt met, the light remains off.
    
    }
uint64_t reading = analogRead(A4);

  double voltage = (reading * 3.3) / 4095.0;

  double temperatureC = (voltage - 0.5) * 100;

  double temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
Blynk.virtualWrite(V1, temperatureC);// write temperatureC to blynk gauge
Blynk.virtualWrite(V0, temperatureF);// write temperatureF to blynk gauge
    //displaying the temperatures to a mini OLED display for easy reading of the ambient temperature in my room.
    display.clearDisplay();
    display.display();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);
    display.print("Inside temp (C):"); display.println(temperatureC); //prints the temp in Celsius with a unit for clarity
    display.display();
    display.print("Inside temp (F):"); display.print(temperatureF); // prints the temp in Fahrenheit  with a unit for clarity
    display.display(); 
    delay(500);
}
