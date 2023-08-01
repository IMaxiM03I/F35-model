#include <Arduino.h>

#include "Joystick.h"
#include "Flap.h"
#include "Rudder.h"
#include "Elevator.h"

// <-- CONSTANTS --> //

// PINS //

// flight control surfaces (PWM)

#define LEFT_OUTER_FLAP_PIN 0
#define LEFT_INNER_FLAP_PIN 0
#define RIGHT_OUTER_FLAP_PIN 0
#define RIGHT_INNER_FLAP_PIN 0

#define LEFT_RUDDER_PIN 0
#define RIGHT_RUDDER_PIN 0

#define LEFT_ELEVATOR_PIN 0
#define RIGHT_ELEVATOR_PIN 0

// flight control joystick (ANALOG)

#define FLIGHT_CONTROL_JOYSTICK_PIN_X 0
#define FLIGHT_CONTROL_JOYSTICK_PIN_Y 1

// MAPPINGS //

// flight control surfaces

#define LEFT 0
#define RIGHT 1

// <-- FUNCTIONS --> //

// <-- OBJECTS --> //

// FLIGHT CONTROL JOYSTICK

Joystick flight_control_joystick = Joystick(FLIGHT_CONTROL_JOYSTICK_PIN_X, FLIGHT_CONTROL_JOYSTICK_PIN_Y);

// FLIGHT CONTROL SURFACES

// Flap flaps[] = {Flap({LEFT_INNER_FLAP_PIN, LEFT_OUTER_FLAP_PIN}), Flap({RIGHT_INNER_FLAP_PIN, RIGHT_OUTER_FLAP_PIN})};       // doesn't work
// Flap flaps[] = {Flap({LEFT_INNER_FLAP_PIN}), Flap({RIGHT_INNER_FLAP_PIN})};                                                  // works
byte left_flap_pins[] = {LEFT_INNER_FLAP_PIN, LEFT_OUTER_FLAP_PIN};
byte right_flap_pins[] = {RIGHT_INNER_FLAP_PIN, RIGHT_OUTER_FLAP_PIN};
Flap flaps[] = {Flap(left_flap_pins), Flap(right_flap_pins)};

byte left_rudder_pins[] = {LEFT_RUDDER_PIN};
byte right_rudder_pins[] = {RIGHT_RUDDER_PIN};
Rudder rudders[] = {Rudder(left_rudder_pins), Rudder(right_rudder_pins)};

byte left_elev_pins[] = {LEFT_ELEVATOR_PIN};
byte right_elev_pins[] = {RIGHT_ELEVATOR_PIN};
Elevator elevators[] = {Elevator(left_elev_pins), Elevator(right_elev_pins)};

FlightControlSurface all_fcs[] = {flaps[LEFT], flaps[RIGHT],
                                    rudders[LEFT], rudders[RIGHT],
                                    elevators[LEFT], elevators[RIGHT]};

void setup() {
    Serial.begin(9600);

    Serial.println("Hello World!\n\n<----------------------->\n\n");
    Serial.println("initializing start-up procedure");
    
    // flight control check
    Serial.print  ("    Flight Control Check...");
    for (FlightControlSurface fcs : all_fcs)
        fcs.performCheck();
    Serial.println("OK");
}

void loop() {

    // READ FLIGHT CONTROL JOYSTICK VALUES
    flight_control_joystick.read();

    // UPDATE SERVO POSITION
    for (FlightControlSurface fcs : all_fcs)
        fcs.move();

}