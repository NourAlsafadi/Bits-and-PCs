
//*********************************************************************
//*         REFERENCES:
//*  - Motor file code
//*  - Distance_sensor file code
//*  - QRD file code
//*
//*         FUNCTION:
//*   This is the brain of the robot, controls the fighting behaviour.
//*
//*********************************************************************




#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.


const int A1A = 2;//define pin 2 for A1A
const int A1B = 3;//define pin 3 for A1B

const int B1A = 8;//define pin 8 for B1A
const int B1B = 9;//define pin 9 for B1B




void setup() {
  Serial.begin(115200);     // set baud rate to 115200
  
  pinMode(B1A,OUTPUT);      // define pins A and B for motor B as output
  pinMode(B1B,OUTPUT);
  
  pinMode(A1A,OUTPUT);      // define pins A and B for motor A as output
  pinMode(A1B,OUTPUT);    
  delay(3000);              // initialization delay (may remove later)
}

void loop() {
  delay(5000);              // delay start of robot for 5 seconds
  
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range) in serial monitor
  Serial.println("cm");

  
  int distance = sonar.ping_cm();   
  
  if(distance<=20){          // when opponent is close (20cm or less), move towards the opponent
    motorB('L');
    motorA('L');
  }
  else{
    motorB('O');             // remove this when both wheels are attached
    //motorA('R');           // while opponent is not detected, keep moving in circles (one wheel is stationary and the other is moving backwards)
    //motorB('O');
  }
  

}

void motorA(char d)         //function for motor A movement
{
  if(d =='R'){
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,HIGH); 
  }else if (d =='L'){
    digitalWrite(A1A,HIGH);
    digitalWrite(A1B,LOW);    
  }else{
    //Robojax.com L9110 Motor Tutorial
    // Turn motor OFF
    digitalWrite(A1A,LOW);
    digitalWrite(A1B,LOW);    
  }
}// motorA end

void motorB(char d)          //function for motor B movement
{

    if(d =='R'){
      digitalWrite(B1A,LOW);
      digitalWrite(B1B,HIGH); 
    }else if(d =='L'){
      digitalWrite(B1A,HIGH);
      digitalWrite(B1B,LOW);    
    }else{
    //Robojax.com L9110 Motor Tutorial
    // Turn motor OFF      
      digitalWrite(B1A,LOW);
      digitalWrite(B1B,LOW);     
    }

}// motorB end 
