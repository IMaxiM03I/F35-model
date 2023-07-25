#include <Arduino.h>

#include "Flap.h"
#include "Rudder.h"
#include "Elevator.h"

// <-- CONSTANTS --> //

// PINS //

// flight control surfaces

#define LEFT_OUTER_FLAP_PIN 0
#define LEFT_INNER_FLAP_PIN 0
#define RIGHT_OUTER_FLAP_PIN 0
#define RIGHT_INNER_FLAP_PIN 0

#define LEFT_RUDDER_PIN 0
#define RIGHT_RUDDER_PIN 0

#define LEFT_ELEVATOR_PIN 0
#define RIGHT_ELEVATOR_PIN 0

// <-- FUNCTIONS --> //

// <-- OBJECTS --> //

// flight control surfaces

Flap leftOuterFlap(LEFT_OUTER_FLAP_PIN);
Flap leftInnerFlap(LEFT_INNER_FLAP_PIN);
Flap rightOuterFlap(RIGHT_INNER_FLAP_PIN);
Flap rightInnerFlap(RIGHT_INNER_FLAP_PIN);

Rudder leftRudder(LEFT_RUDDER_PIN);
Rudder rightRudder(RIGHT_RUDDER_PIN);

Elevator leftElevator(LEFT_ELEVATOR_PIN);
Elevator rightElevator(RIGHT_ELEVATOR_PIN);

void setup() {
    Serial.begin(9600);

    Serial.println("Hello World!\n\n<----------------------->\n\n");
    Serial.println("initializing start-up procedure...");
    Serial.println("    Init Flight Control Check...");

    // flight control check
    leftOuterFlap.performCheck();
}

void loop() {
  // put your main code here
}