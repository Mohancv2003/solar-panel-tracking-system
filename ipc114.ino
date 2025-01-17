#include <Servo.h>

Servo servo;   // Create a servo object to control the servo
int eLDRPin = A0; // Assign pins to the LDR's
int wLDRPin = A1;
int eastLDR = 0; //Create variables to store to LDR readings
int westLDR = 0;
int difference = 0; //Create a variable to compare the two LDR's
int error = 10;  // Variable for is there is a noticable difference between the tow LDR's
int servoSet = 90; //Variable for position of servo - will be different for each device


void setup() {
  servo.attach(9);   //attaches the servo object to PWM pin 9
  Serial.begin(9600); 
}

void loop() {
  eastLDR = analogRead(eLDRPin); //Read the LDR values
  westLDR = analogRead(wLDRPin);

  if (eastLDR < 400 && westLDR < 400) {  //Check to see if there is low light on both LDR's
    while (servoSet <=140 && servoSet >=15) {     // if so, send panels back to east for the sunrise
      servoSet ++;
      servo.write(servoSet);
      delay(100);
    }
  }

  difference = eastLDR - westLDR ; //Check the difference 
  if (difference > 10) {          //Send the panel towards the LDR with a higher reading
    if (servoSet <= 140) {
      servoSet ++;
      servo.write(servoSet);
    }
  } else if (difference < -10) {
    if (servoSet >= 15) {
      servoSet --;
      servo.write(servoSet);
    }
  }
  Serial.print(eastLDR);      //Serial monitor can be useful for debugging/setting up
  Serial.print("   -   ");    //Use it to see if your LDR's are noticeably different when
  Serial.print(westLDR);      //They have equal light shining on them, if so, correct with the error value
  Serial.print("   -   ");
  Serial.print(difference);   
  Serial.print("   -   ");
  Serial.print(servoSet);     //Fine tune the servo settings, to maximise swing available
  Serial.print("   -   ");
  Serial.println(".");
  delay(100);
}
