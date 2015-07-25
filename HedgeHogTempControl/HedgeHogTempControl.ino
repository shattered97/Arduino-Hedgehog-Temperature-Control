/*  Hedgehog heater control
start date:  7 Sept 13
Shattered97

Concept:  Use arduino board to control Power Tail II from makershed
to turn on or off a 110VAC ceramic heater and 5VDC heating pad.
TMP36 tempature sensors are used to test the environment then 
either turn on or off the heaters.

RBG LCD Setup (Basic setup from Ardunio.cc)
http://www.arduino.cc/en/Tutorial/LiquidCrystal
 
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 * PWM digital pin 6 to LCD pin 16 (green backlight)
 * PWM digital pin 9 to LCD pin 17 (red bacllight)
 * PWM digital pin 10 to LCD pin 18 (blue backlight)
 * 5V to LCD pin 15 used to run backlight lightcolor
*/

//Include Files
#include <LiquidCrystal.h>
#define aref_voltage 3.3

//Initialize LCD Pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Variables
  int x = 0;
 //LCD Variables
  int green = 1;  //background color for LCD
  int red = 2;  //background color for LCD
  int blue = 3;  //background color for LCD
  int bgBlue = 6; //use PWM to set color
  int bgGreen = 9; //use PWM to set color
  int bgRed = 10; //use PWM to set color
 //TMP36 Variables
  int tmpSensor1 = 0;

TMP36 sensor1(A0);

void setup()
{
  //LCD Setup
  lcd.begin(16, 2); //setup the LCD's number of columns and rows
  lcd.print("Loading");
  pinMode(bgRed, OUTPUT);  //setup digital pin 10 for output
  pinMode(bgBlue, OUTPUT);  //setup digital pin 6 for output
  pinMode(bgGreen, OUTPUT);  //setup digital pin 9 for output
  //TMP36 Setup
  Serial.begin(9600);
  analogReference(EXTERNAL);
}

void loop()  //test code
{

int reading = analogRead(A0);
  int reading2 = analogRead(A1);
  float voltage = (reading * 3.3)/1024;
  Serial.println(reading);
  Serial.print(voltage, 4); 
  Serial.println(" volts");
  float temperatureC = (voltage - 0.5) * 100;
  Serial.print(temperatureC); 
  Serial.println(" degrees C");
  float temperatureF = (temperatureC * 9.0 /5.0) + 32.0;
  Serial.print(temperatureF, 4); 
  Serial.println(" degrees F");
  bgLCD(green);
  textLCD(temperatureF, temperatureF, temperatureF);
  delay(1000);
  
  
}
//LCD Functions
void bgLCD(int color)
{
  /* use analogWrite(PIN, Value) to set color.  Value is 0 to 255.  Zero is
  on and 255 is off.  Any mixture of the value will result in a combination 
  of the colors.
  PINS used:  Digital 6, 9, 10
  */
  switch (color)
  {
    case 1:  //Set Background to green
      analogWrite(bgGreen, 0);
      analogWrite(bgRed, 255);
      analogWrite(bgBlue, 255); 
      break;
    case 2:  //Set Background to red
      analogWrite(bgGreen, 255);
      analogWrite(bgRed, 0);
      analogWrite(bgBlue, 255);
      break;
    case 3:  //Set Background to blue
      analogWrite(bgGreen, 255);
      analogWrite(bgRed, 255);
      analogWrite(bgBlue, 0);
      break;
    default:  //debug code - no background color
      analogWrite(bgGreen, 255);
      analogWrite(bgRed, 255);
      analogWrite(bgBlue, 255);
      break;
  }
}

void textLCD(float left, float center, float right)
{
  /* Used to set up input from temp36 sensor to display the current temp.
  int left is left sensor, int center is center sensor, int right is right
  sensor.  
  */
  
  int average = (left + right + center)/3;  //Average Temp from all sensors
  
  //setup display
  lcd.clear();
  lcd.print("Average:  ");
  lcd.setCursor(10,0);
  lcd.print(average);
  lcd.setCursor(0,1);
  lcd.print("L:");
  lcd.print(left);
  lcd.setCursor(6,1);
  lcd.print("C:");
  lcd.print(center);
  lcd.setCursor(12,1);
  lcd.print("R:");
  lcd.print(right);
}




