
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

const int QRD1114_PIN = A0;      // Sensor at front output voltage
const int QRD1114_PINB = A1;      // Sensor at back output voltage

const int A1A = 2;//define pin 2 for A1A
const int A1B = 3;//define pin 3 for A1B

const int B1A = 8;//define pin 8 for B1A
const int B1B = 9;//define pin 9 for B1B


const int buttonPin = 13;
int run = 0;



void setup() {
  //Serial.begin(9600);     // set baud rate to 115200

  
  
  pinMode(QRD1114_PIN, INPUT); //define QRD front as input
  pinMode(QRD1114_PINB, INPUT); //define QRD back as input
  
  pinMode(B1A,OUTPUT);      // define pins A and B for motor B as output
  pinMode(B1B,OUTPUT);
  
  pinMode(A1A,OUTPUT);      // define pins A and B for motor A as output
  pinMode(A1B,OUTPUT);    

  pinMode(buttonPin, INPUT_PULLUP);
  
  delay(4950);              // initialization delay 
}


void loop() {
  if(digitalRead(buttonPin) == LOW) //funcitons based off of button pulling input pin LOW
  {
     if(run == 0)
     {
         run = 255;
     }
     else
     {
         run = 0;
     }
  }
  
  
  
  if(run > 0){
    
    delay(50);              // delay for time between each ping
  
    //Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range) in serial monitor
    //Serial.println("cm");

  
    int distance = sonar.ping_cm();   
  
    // Read in the ADC and convert it to a voltage:
    int proximityADC = analogRead(QRD1114_PIN);
    float proximityV = (float)proximityADC * 5.0 / 1023.0;

    int proximityADCB = analogRead(QRD1114_PIN);
    float proximityVB = (float)proximityADC * 5.0 / 1023.0;

    if(proximityV > 1.5){       //if front is close to white line move to back
      motorB('R');
      motorA('R');
      delay(4000);
    }
  
    if(proximityVB > 1.5){      //if back is close to white line move to front
      motorB('L');
      motorA('L');
      delay(4000);
    }

  
    if(distance<=20){          // when opponent is close (20cm or less), move towards the opponent
      motorB('L');
      motorA('L');
    }
    else if(distance<= 200){
      //motorB('O');             // remove this when both wheels are attached
      motorA('R');           // while opponent is not detected, keep moving in circles (one wheel is stationary and the other is moving backwards)
      motorB('O');
    }
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
