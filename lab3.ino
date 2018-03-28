
#include <Servo.h>

Servo servoLeft; 
Servo servoRight;
int turnRightTime = 758;
int turnLeftTime = 760;
int correctParallel = 7; // 15
int prevTime = 0;
void setup() 
{
  Serial.begin(9600);
//MIDDLE DISTANCE SENSOR
 pinMode(7, INPUT); pinMode(8, OUTPUT);
//LEFT DISTANCE SENSOR
 pinMode(9, INPUT); pinMode(10, OUTPUT);
//RIGHT DISTANCE SENSOR
 pinMode(2, INPUT); pinMode(3, OUTPUT); 
 
 tone(4, 3000, 1000); 
 delay(1000); 
 servoLeft.attach(12); 
 servoRight.attach(11); 
 
 servoLeft.writeMicroseconds(1500);
 servoRight.writeMicroseconds(1500);


  int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
 int irLeft = irDetect(10, 9, 38000); // Check for object on left
 int irRight = irDetect(3, 2, 38000); // Check for object on left
 wallright();
 delay(300);
 parallel(0);
 parallel(1);
}

void loop() // Main loop auto-repeats
{ 



}

void wallright()
{
  int irMiddle = irDetect(8, 7, 38000);
  while(irMiddle != 0)
  {
    forward(50);
    irMiddle = irDetect(8, 7, 38000); // Check for object on middle
  }
  forward(400);
  stop(300);
  turnRight(turnRightTime);
  stop(300);
}
void parallel(int stage){
  //stage:0 moving parallel before turing
  //stage:1 moving parallel after turning
  int irLeft = irDetect(10, 9, 38000);
  int irRight = irDetect(3, 2, 38000); // Check for object on left
  if(stage == 0){
    while(irLeft == 0){
      irLeft = irDetect(10, 9, 38000);
      forward(500); 
      turnRight(correctParallel);   
    }
    forward(100);
    stop(300);
    turnLeft(turnLeftTime);
    stop(300);
    forward(1700);
    stop(300);
    turnLeft(turnLeftTime + 70);
    stop(300);
    forward(1000);
  }
  else{
      while(irLeft == 0){
         irLeft = irDetect(10, 9, 38000);
         irRight = irDetect(3, 2, 38000);
         if(irRight == 0 && prevTime == 0){
          prevTime = millis();  
          } 
         else if(irRight == 0 && prevTime != 0){
            backward((millis() - prevTime) / 2);
            break;
          }
         forward(500); 
         turnLeft(correctParallel + 5);      
       }
       turnfirstcup();
       
    }
}
void turnfirstcup(){
    //forward(1000);
    stop(300);
    turnRight(turnRightTime + 85);
    stop(300);
   int irLeft = irDetect(10, 9, 38000);
   int irRight = irDetect(3, 2, 38000); // Check for object on left
    while(irLeft != 0 || irRight != 0){
      forward(10);   
      irLeft = irDetect(10, 9, 38000);
      irRight = irDetect(3, 2, 38000);     
    }
  /* if(irRight == 0 && irLeft != 0){ //dumb code to align robot between 2 cups
      while(irLeft != 0){
        turnRight(10);
        irLeft = irDetect(10, 9, 38000);
        }
    }*/
    stop(300);
    turnmiddlecup();
}
void turnmiddlecup(){
  int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
  while(irMiddle != 0){
    irMiddle = irDetect(8, 7, 38000);
    forward(20);
  } 
    //forward(150);
    stop(300);
    turnLeft(turnLeftTime);
    stop(300);
    forward(1500);
    stop(300);
    turnRight(turnLeftTime);
    stop(300);
    forward(2000);
    stop(300);
    turnRight(turnLeftTime);
    stop(300);
    forward(1500);
    stop(300);
    turnLeft(turnLeftTime);
    forward(5000); //add code to stop robot before it hits the ending wall
    endfunc();
  } 
void endfunc(){
  int irMiddle = irDetect(8, 7, 38000); // Check for object on middle
  while(irMiddle != 0){
    irMiddle = irDetect(8, 7, 38000);
    forward(5);
  } 
  stop(99999999);
  }  
int irDetect(int irLedPin, int irReceiverPin, long frequency)
{
 tone(irLedPin, frequency, 8); // IRLED 38 kHz for at least 1 ms
 delay(1); // Wait 1 ms
 int ir = digitalRead(irReceiverPin); // IR receiver -> ir variable
 delay(1); // Down time before recheck
 return ir; // Return 1 no detect, 0 detect
}
void forward(int time) // Forward function
{
 servoLeft.writeMicroseconds(1596); // Left wheel counterclockwise
 servoRight.writeMicroseconds(1300); // Right wheel clockwise
 delay(time); // Maneuver for time ms
}
void turnLeft(int time) // Left turn function
{
 servoLeft.writeMicroseconds(1300); // Left wheel clockwise
 servoRight.writeMicroseconds(1300); // Right wheel clockwise
 delay(time); // Maneuver for time ms

}
void turnRight(int time) // Right turn function
{
 servoLeft.writeMicroseconds(1700); // Left wheel counterclockwise
 servoRight.writeMicroseconds(1650); // Right wheel counterclockwise
 delay(time); // Maneuver for time ms
}
void backward(int time) // Backward function
{
 servoLeft.writeMicroseconds(1400); // Left wheel clockwise
 servoRight.writeMicroseconds(1700); // Right wheel counterclockwise
 delay(time); // Maneuver for time ms
} 
void halforward(int time) // Forward function
{
 servoLeft.writeMicroseconds(1600); // Left wheel counterclockwise
 servoRight.writeMicroseconds(1400); // Right wheel clockwise
 delay(time); // Maneuver for time ms
}
void stop(int time) // Backward function
{
 servoLeft.writeMicroseconds(1500); // Left wheel clockwise
 servoRight.writeMicroseconds(1500); // Right wheel counterclockwise
 delay(time); // Maneuver for time ms
} 

