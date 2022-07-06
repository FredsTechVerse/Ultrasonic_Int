#include <Servo.h>
#include <IRremote.h> //Library for the IR reciever

//SERVO OBJECT CREATED TO CONTROL A SERVO
//========================================
Servo agv_servo;
Servo IR_servo;

//MILLIS CRUCIAL VARIABLES.
//==========================
 
const unsigned long eventTime_1_LDR = 1000;
const unsigned long eventTime_2_LDR = 1500;

unsigned long previousTime_1 = 0;
unsigned long previousTime_2 = 0;
unsigned long previousTime_3 = 0;
unsigned long previousTime_4 = 0;

int ledState = LOW;
long OnTime = 250;
long OffTime = 750;
//ULTRASONIC SENSOR
//==================
long duration;
int distance;

#define echoPin 8
#define trigPin 6
#define buzzerPin 9

//VITRON REMOTE CONTROL VARIABLES
//================================
#define Button_L 0xFFA857
#define Button_R 0xFFE01F
#define Button_P 0xFFC23D
#define Moving_Forward 0xFF02FD
#define Moving_Backward 0xFF22DD
#define Power 0xFFA25D
#define Mute 0xFFE21D
#define Button_Dec 0xFF22DD
#define Button_Dec 0xFF22DD

//INITIATION OF DATA VARIABLES
//=============================
int pos = 0;    // Stores the servo position
int receiver = 10; //Reciever Pin
int servo_pos = 3;
uint32_t Previous;
int c_speed = 200;

//INITIATION OF DC MOTOR VARIABLES.
//==================================
int enA = 5;
int in1 = 2;
int in2 = 4;


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
  if(new_speed<=250){
    new_speed += 10;
    return (new_speed);
    }else if(new_speed=250){
     new_speed+=5;
     return(new_speed);
      }else{
      return (new_speed);
      }
 
  };

  int speedDecrement (int new_speed){
  if(new_speed<255 && new_speed>0){
    new_speed -= 5;
    return (new_speed);
    }else if(new_speed=255){
     new_speed-=5;
     return(new_speed);
      }else{
      return (new_speed);
      }
 
  };

  void  inc_speed(){
    c_speed = speedIncrement(c_speed);
    Serial.println(c_speed);
    movingForward();
    };

  void dec_speed(){
    c_speed = speedDecrement(c_speed);
    Serial.println(c_speed);
    movingForward();
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

 int power = HIGH;
 
 void togglePowerState (){
  if(power==HIGH){
    power = LOW;
    digitalWrite(12,power);
    digitalWrite(7,power);
    
    }else if (power ==LOW){
      power = HIGH;
    digitalWrite(12,power);
    digitalWrite(7,power);
    }
  };

  void LEDTest(){
    digitalWrite(12,power);
    digitalWrite(7,power);
    };

  void togglePower(){
    togglePowerState();
    delay(100);
    LEDTest();
    };
    
  void turnOff(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  analogWrite(enA,0);//We shall include a for loop here. For continuous increment and decrement.
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

 void movingForward(){
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  analogWrite(enA,c_speed);//We shall include a for loop here. For continuous increment and decrement.
 };

 void movingBackward(){
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(enA,c_speed);//We shall include a for loop here. For continuous increment and decrement.
  };

//FUNCTIONS FOR THE IR RECEIVER SERVO
//=======================================

//INITIATION OF 
int obstacle= 0;
int obstacle_left;
int obstacle_right;


 void servo_left(){
 for(int angle = 42; angle <=70; angle += 2) // goes from 45 degrees to 0 degrees
 { // in steps of 1 degree
 IR_servo.write(angle);
 delay(10);
 }
 };

 void servo_right(){
 for(int angle = 42; angle >=0; angle -= 2) // goes from 45 degrees to 90 degrees
 { // in steps of 1 degree
 agv_servo.write(angle); // tell servo to go to position in variable 'angle'
 delay(10);
 }}; 
  
 
 int IR_sensor(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
 duration=pulseIn(echoPin,HIGH);
  distance=(duration*0.034/2);
  return distance;
  
//  Serial.print("Distance : ");
//  Serial.print(distance);
//  Serial.println(" cm ");
 };


void buzzer_init(){
//CALLING THE IR SENSOR FUNCTION
//==============================
obstacle = IR_sensor();
//obstacle = 5;
//INITIAL LOGIC TO START MOVING FORWARD AFTER READING THE SENSOR VALUE
//======================================================================
  if (obstactle<=100){
  tone(buzzerPin,2000);
  delay(50);
  turnOff();
//  BLINK 5 TIMES
//================
  for (int blk =0; blk<=5;blk++){
    blinking();
  };
  IR_Left();
 int left = IR_Sensor();
  IR_Right();
  int right = IR_Sensor();

  if (IR_Right && IR_Left >=1089 ){
//    Moving either  right or left
    }else if(IR_Right < IR_Left){
//      Move back
//      Move to the right
}else if(IR_Right> IR_Left){
//  Move back
//Then move left
  }else {
//    I don't know what to do just blink.
}

  }

//    meanPosL();
//    turningRight();
//    meanPosR();
 
  
  
    }
  else{
  movingForward();
  noTone(buzzerPin);
      };
     

 
void test (){
  
 blinking();
 delay(100);
 turningLeft();
 delay(100);
 movingForward();
 delay(1000);
 turnOff();
 delay(100);
 meanPosL();
 delay(200);
 movingBackward();
 delay(1000);
 turnOff();
 delay(1000);

 blinking();
 delay(100);

turningRight();
delay(100);
movingForward();
delay(1000);
turnOff();
delay(100);
meanPosR();
delay(100);
movingBackward();
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
 movingForward();
 break;

 case Moving_Backward:
 blinking();
 movingBackward();
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
agv_servo.write(42);

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
//CALLING THE IR SENSOR FUNCTION
//==============================
obstacle = IR_sensor();
//INITIAL LOGIC TO START MOVING FORWARD AFTER READING THE SENSOR VALUE
//======================================================================
  if (obstactle<=100){
  tone(buzzerPin,2000);
  delay(50);
  turnOff();
  for (int blk =0; blk<=5;blk++){
    blinking();
  };
};

void loop(){
//IR_Receiver_Module();
switchCase();
};

//CHALLENGES ENCOUNTERED
//======================
/*
For the switch case statement, upon the press of a certain button the code just keeps on looping. Doesnt break upon end of the execution.
For the if statement the code start to implement even b4 a user action via the remote.Also keeps looping.
*/

//KEY THINGS TO NOTE.
//===================
/*
 * Break down the repetitive code into functions.
 * Save the pins in variables for easier reference and amendments.
 * Create a for loop for buttons 0 - 9 .... Make them dynamic.
 * look into asynchronous programming of arduino where the servo motor can turn as it is being given a push by the dc motor.
 * look into the purpose of having a common ground arduino.
*/
