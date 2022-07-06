//The arduino library is automatically included.
//Library for the servo motor&the IR receiver
//===========================================
#include <Servo.h>
#include <IRremote.h> //Library for the IR reciever

//Creation of the servo objects for the agv_servo & the ultrasonic servo
//========================================================================
Servo agv_servo;
Servo IR_servo;

//DEFINATION OF VARIABLES
//========================

//Vitron Remote.
//==============
#define Button_L 0xFFA857
#define Button_R 0xFFE01F
#define Button_P 0xFFC23D
#define Moving_Forward 0xFF02FD
#define Moving_Backward 0xFF22DD
#define Power 0xFFA25D
#define Mute 0xFFE21D
#define Button_Dec 0xFF22DD
#define Button_Dec 0xFF22DD

//IR receiver & the servo position
//=================================
int init_pos = 42;//This is the initial servo position.
int init2_pos = 90;//THis is the initial position for the ultrasonic sensor.
int servo_pos = 3;//This is the pin to which the servo is attached to 
int servo2_pos = 9;//This is the pin attached to the ultrasonic servo
int c_speed = 100;//THis is for the speed increment and decrement.
int b_speed = 100;//This is the constant speed for reversing.

//IR receiver variables
//======================
int receiver = 10; //Reciever Pin
uint32_t Previous;

//DC motor variables
//===================
int enA = 5;
int in1 = 2;
int in2 = 4;

//Ultrasonic Sensor Variables
//===========================
long duration;
int distance;

#define echoPin 8
#define trigPin 6
#define buzzerPin 9


//Ultrasonic Servo Variables
//===========================
int obstacle;
int obstacle_left;
int obstacle_right;

//Millis function variables.
//==========================
unsigned long current_time; 
unsigned long previousTime_1 = 0;
unsigned long interval = 5000;

//IR receiver setup
//===================
IRrecv irrecv(receiver);
decode_results results;

//LIST OF FUNCTIONS.
//==================
void buttonAssignment(){
  if (irrecv.decode(&results)){
// CODE THAT PRINTS OUT THE HEX CODE RETURNED
//=============================================
Serial.println(results.value,HEX);//Displays the hex results in a line.
  irrecv.resume();//THis is for the next value.
  
if(results.value==0xFFFFFFFF){
  results.value = Previous;
};
};
};


int speedIncrement (int new_speed){
  if(new_speed<250){
    new_speed += 10;
    return (new_speed);
    }else if(new_speed==250){
     new_speed+=5;
     return(new_speed);
      }else if (new_speed==255){
        for (int count=0;count<=5;count++){
          blinking();
          };
      return (new_speed);
      }
 
  };
  

  int speedDecrement (int new_speed){
  if(new_speed<255 && new_speed>0){
    new_speed -= 10;
    return (new_speed);
    }else if(new_speed==255){
     new_speed-=5;
     return(new_speed);
      }else if (new_speed==0){
       for (int count=0;count<=5;count++){
          blinking();
          };
      return (new_speed);
      }
 
  };

  void  inc_speed(){
    c_speed = speedIncrement(c_speed);
    Serial.println(c_speed);
    movingForward(c_speed);
    };

  void dec_speed(){
    c_speed = speedDecrement(c_speed);
    Serial.println(c_speed);
    movingForward(c_speed);
    };

void servoTest(){
  agv_servo.write(25);
  };
  
void blinking(){
    digitalWrite(12,HIGH);
    digitalWrite(7,HIGH);
    delay(100);
    digitalWrite(12,LOW);
    digitalWrite(7,LOW);
    delay(100);
    };
   
 void turningLeft(){
 for(int angle = 42; angle <=70; angle += 2) // goes from 45 degrees to 0 degrees
 { // in steps of 1 degree
 agv_servo.write(angle);
 delay(20);
 }
  };
 void turningRight(){
 for(int angle = 42; angle >=0; angle -= 2) // goes from 45 degrees to 90 degrees
 { // in steps of 1 degree
 agv_servo.write(angle); // tell servo to go to position in variable 'angle'
 delay(20);
 }}; 


void meanPosR(){
  for(int angle = 0; angle <= 42; angle += 2) // goes from 90 degrees to mean postion
 {
 agv_servo.write(angle); // move servo in opposite direction
 delay(20);
 }
};
void meanPosL(){
  for(int angle = 70; angle >= 42; angle -= 2) // goes from 0 degrees to mean position.
 {
 agv_servo.write(angle); // move servo in opposite direction                            
 delay(20);
 }
};

  void turnOff(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,0);//We shall include a for loop here. For continuous increment and decrement.
  };

 void movingForward(int c_speed){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,c_speed);//We shall include a for loop here. For continuous increment and decrement.
 };

 void movingBackward(int b_speed){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,b_speed);//We shall include a for loop here. For continuous increment and decrement.
  };


//FUNCTIONS FOR THE IR RECEIVER SERVO
//=======================================
 void servo_left(){
 for(int angle = 90; angle <=30; angle -= 1) // goes from 45 degrees to 0 degrees
 { // in steps of 1 degree
 IR_servo.write(angle);
 delay(20);
 }
  obstacle_left = IR_sensor();//Servo to capture the value
  Serial.print("A move to the left : ");
  Serial.println(obstacle_left);
 };

 void servo_right(){
 for(int angle = 30; angle >=150; angle += 1) // goes from 45 degrees to 90 degrees
 { // in steps of 1 degree
 IR_servo.write(angle); // tell servo to go to position in variable 'angle'
 delay(20);
 }
   obstacle_right = IR_sensor();//Servo to capture the value
   Serial.print("A move to the right : ");
   Serial.println(obstacle_right);
 }; 
  
 
 int IR_sensor(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
 duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2); 
//  Serial.print("Distance : ");
//  Serial.print(distance);
//  Serial.println(" cm ");//After printing out to the screen return the distance to the obstacle variable.
  return distance;
 };

//BASICS FOR OBJECT DETECTION.
//============================
  void IR_Receiver_Module(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
 duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm ");
//  delay(500);


  if (distance<=100){
  tone(buzzerPin,2000);
  delay(50);
  turnOff();
  for (int blk =0; blk<=5;blk++){
    blinking();
  };
    turningLeft();
    meanPosL();
    turningRight();
    meanPosR();
  
  
    }
  else{
  movingForward(c_speed);
  noTone(buzzerPin);
      };
      };


//This is the after math after the value is taken by the ultrasonic sensor
//========================================================================//

void buzzer_action(){//This should just be a simple buzzer test.
//  Blink LEDs 5 times.
//======================
  for (int blk =0; blk<=5; blk++){
    blinking();
  };  

  turnOff();//Bringing our car to a halt.
  
//Move the servo left & right to take in the values.
//==================================================
 servo_left();
 servo_right();

//Using the global variables to decide the fate/direction.
//========================================================
 if(obstacle_right > obstacle_left)
    {
movingBackward(b_speed);//Duration of time needs to be defined
delay(500);
Serial.print("Turning Right ");
turningRight();
movingForward(c_speed);
delay(2000);
turningLeft();
movingForward(c_speed);
delay(2000);
meanPosR();
movingForward(c_speed);
}else if(obstacle_right < obstacle_left){
movingBackward(b_speed);//Duration of time needs to be defined
delay(500);
Serial.print("Turning Left");
turningLeft();
movingForward(c_speed);
delay(2000);
turningRight();
movingForward(c_speed);
delay(2000);
meanPosR();
movingForward(c_speed);
  }else {
turnOff();
for (int blk =0; blk<=5;blk++){
    blinking();
    delay(50);
  };  
};

};
   

void test (){
  
 blinking();
 delay(100);
 turningLeft();
 delay(100);
 movingForward(c_speed);
 delay(1000);
 turnOff();
 delay(100);
 meanPosL();
 delay(200);
 movingBackward(b_speed);
 delay(1000);
 turnOff();
 delay(1000);

 for (int blk =0; blk<=3;blk++){
    blinking();
    delay(100);
  };  

turningRight();
delay(100);
movingForward(c_speed);
delay(1000);
turnOff();
delay(100);
meanPosR();
delay(100);
movingBackward(b_speed);
delay(1000);
turnOff();
delay(100);

};
//SWITCH STATEMENT
//================
void switchCase(){
if (irrecv.decode(&results)){
// CODE THAT PRINTS OUT THE HEX CODE RETURNED
//=============================================
Serial.println(results.value,HEX);//Displays the hex results in a line.
 irrecv.resume();//THis is for the next value.
  
if(results.value==0xFFFFFFFF){
  results.value = Previous;
};
switch (results.value){

 case Power:
 blinking();
 IR_Receiver_Module();
 break;
  

 case Button_L:
 blinking();
 turningLeft();
 meanPosL();

 break;
 
 case Button_R:
 blinking();
 turningRight();
 meanPosR();

 break;

 case Button_P:
 blinking();
 turnOff();
 
 break;

 case Moving_Forward:
 blinking();
 movingForward(c_speed);
 break;

 case Moving_Backward:
 blinking();
 movingBackward(b_speed);
 break;
};//END OF THE CASE SWITCH STATEMENT
};
};


void setup(){
Serial.begin(9600);
irrecv.enableIRIn();//Starts the receiver.

//LED MODES
//==========
pinMode (12, OUTPUT);//LED attached to pin 12
pinMode(7,OUTPUT);

//SERVO SETUP
//===========
agv_servo.attach(servo_pos); // Servo attached to pin 3
IR_servo.attach(servo2_pos);//Sero attached to pin 9
agv_servo.write(init_pos);
IR_servo.write(init2_pos);

//ULTRASONIC SENSOR
//==================
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(buzzerPin,OUTPUT);

//DC MOTOR CONTROLS
//=================
pinMode(in1,OUTPUT);
pinMode(in2,OUTPUT);
pinMode(enA,OUTPUT);//PWM
//DEBUG SECTION
//=============
//servo_left();

//servo_right();

}
void loop(){
//  inc_speed();
//dec_speed();
//Serial.print("The current speed is : ");
//Serial.println(c_speed);
//delay(1000);

//  switchCase(); //The code is working correctly.
// IR_Receiver_Module();

//Taking the ultrasonic sensor readings at intervals of 200ms.
//=============================================================

current_time = millis();
if(current_time - previousTime_1>=interval){
  Serial.println(previousTime_1);
 obstacle = IR_sensor();//Appends the IR sensor value to the obstacle variable.
 Serial.print("Normal Obstacle Distance Checkup : ");
 Serial.println(obstacle);

//START OF BODY
//==============
 if(obstacle>90){
    blinking(); 
   movingForward(c_speed);
  }
  else if(obstacle<=90){
    buzzer_action();//This edf cccccccccccccccccgfunction should kick in.
  };
//  This is like the function event tracker.
  previousTime_1 = current_time;
  
}

};
