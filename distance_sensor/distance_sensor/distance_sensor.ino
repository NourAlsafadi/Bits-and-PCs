
//*******************************************************************
//*         REFERENCES:
//* http://robojax.com/learn/arduino/?vid=robojax-HC-SR04-ultrasonic
//* https://cdn.sparkfun.com/datasheets/Sensors/Proximity/HCSR04.pdf
//*
//*         FUNCTION:
//*   Detects distance of object and outputs to PC serially. 
//*   (using serial monitor)
//*
//*         NOTE: 
//*  for any distance less than 3 cm, the sensor will not be 
//*  able to pick up accurate measurements.
//*
//*******************************************************************



// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  //Serial.print("Ping: ");
  Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  int distance = sonar.ping_cm();// store the distance value in "distance" variable
  if(distance <=12){             // if distance is less than 12, do somethings. For example here just print "very close"
    Serial.println("Very close");
  }
  //exit(0);
}
