//By yixing Qie

//Import Libraries
#include   <Servo.h>
#include  <I2Cdev.h>
#include   <MPU6050.h>
#include   <Wire.h>

MPU6050 SENSE;
Servo servox;
Servo servoy; 
int16_t accx, accy, accz, gyrox, gyroy, gyroz;

void setup() {
  Serial.begin(9600);
  SENSE.initialize(); 

  //initializes the servos
  servo1.attach(3);
  servo2.attach(4);
  
  //set to 90 degrees middle point
  servo1.write(90);
  servo2.write(90); 
  delay(50);
}
int currentx;
double currenty;
int prevx;
int prevy;

void loop() {
  //only deal with x and y direction of the gimbal
  SENSE.getMotion6(&accx, &accy, &accz, &gyrox, &gyroy , &gyroz);

  currentx = map(accx, -1000, 1000, 0, 180); 
  currenty = map(accy, -1000, 1000, 0, 180); // maps values into workable servo values


  if (currentx != prevx){ 
    double x = currentx; //+- a constant for calibration           
    servox.write(x);  
    prevx = currentx;
  }
  if (currenty != prevy) {
    double y = currenty; //+- a constant for calibration   
    servoy.write(y);
    prevy = currenty;
  }

  delay(50);
}
