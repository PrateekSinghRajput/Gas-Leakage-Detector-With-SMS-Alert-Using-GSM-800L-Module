#include<LiquidCrystal_I2C.h>
#include<Wire.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(2, 3);
 
int gasValue = A0; // smoke / gas sensor connected with analog pin A1 of the arduino / mega.
int data = 0;
int Red = 6;
int Green = 7;
void setup()
{
randomSeed(analogRead(0));
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
lcd.init();
lcd.backlight();
pinMode(gasValue, INPUT);
pinMode(Red, OUTPUT);
pinMode(Green,OUTPUT);
lcd.print ("   WELCOME TO");
lcd.setCursor(0,1);
lcd.print ("JSUTDOELECTRONIC");
delay(3000);
lcd.clear();
lcd.print (" Gas Leakage ");
lcd.setCursor(0,1);
lcd.print (" Detector Alarm ");
delay(3000);
lcd.clear();
}
 
void loop()
{
 
data = analogRead(gasValue);
 
Serial.print("Gas Level: ");
Serial.println(data);
lcd.print ("Gas Scan is ON");
lcd.setCursor(0,1);
lcd.print("Gas Level: ");
lcd.print(data);
delay(1000);
 
if ( data > 80) //
{
SendMessage();
Serial.print("Gas detect alarm");
lcd.clear();
lcd.setCursor(0,0);
lcd.print(" Gas Leakage");
lcd.setCursor(0,1);
lcd.print(" SMS Sent");
delay(1000);
digitalWrite(Red, HIGH);
digitalWrite(Green, LOW);
 
}
else
{
Serial.print("Gas Level Low");
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Gas Level Normal");
digitalWrite(Red, LOW);
digitalWrite(Green, HIGH);
delay(1000);
}
 
lcd.clear();
}
 
void SendMessage()
{
Serial.println("I am in send");
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"+919975617490\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("Hi Prateek Gas Detected plz Open Windows And Check Your Gas Cylinder");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
