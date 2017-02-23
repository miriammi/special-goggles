#include <Servo.h>

// Defining the different sensors and motors:
const int IR1 = 9;
const int IR2 = 10;
Servo servo1;
Servo servo2;
const unsigned long PrinterInterval = 1000; // wait 1 sec before printing data
const unsigned long servo1speed = 850; // The speed of servo1
const unsigned long servo1stop = 1700; // When to stop servo1
const unsigned long servo2speed = 850; // The speed of servo2
const unsigned long servo2stop = 1700; // When to stop servo2

// Defining other useful variables:
String sep = ",";
// NOTE that Timers should always be unsigned long, and NOT int
unsigned long Timermove1;
unsigned long Timermove2;
unsigned long TimerPrinter;
String servo1status = "OFF";
String servo2status = "OFF";

void setup() {
// Defining the different pins:
pinMode(IR1,INPUT);
pinMode(IR2,INPUT);
servo1.attach(6);
servo2.attach(7);
Timermove1 = millis();
Timermove2 = millis();
TimerPrinter = millis();
// Opening the serial port communication and setting the time
Serial.begin(9600);
Serial.println("Food1,Food2");    // The title of the csv file created 
}

void loop() {
  // Check the state of each of the sensors
  int IRState1 = digitalRead(IR1);
  int IRState2 = digitalRead(IR2);
  if ((millis()-TimerPrinter)>=PrinterInterval)
  PrintData();
  if(digitalRead(IR1)==HIGH) { 
    servo1status = "ON";
    Timermove1 = millis();
  }
  if (servo1status == "ON"){
     servo1.writeMicroseconds(1300); // Make a turn clockwise
     if ((millis()-Timermove1)>=850) 
            servo1.writeMicroseconds(1500);
            if ((millis()-Timermove1)>=1700)
            servo1status = "OFF";
                
           }
   if(digitalRead(IR2)==HIGH) { 
    servo2status = "ON";
    Timermove2 = millis();
  }
  if (servo2status == "ON"){
     servo2.writeMicroseconds(1300); // Make a turn clockwise
     if ((millis()-Timermove2)>=850) 
            servo2.writeMicroseconds(1500);
            if ((millis()-Timermove2)>=1700)
            servo2status = "OFF";
                
           }
  }

void PrintData()
{
    int IRState1 = digitalRead(IR1);
    int IRState2 = digitalRead(IR2);
   String dat = String(IRState1) + sep + String(IRState2);
   Serial.println(dat);
   TimerPrinter = millis();  // remember when the data was printed
}


