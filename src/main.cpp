#include <Arduino.h>

#include "Joystick.h"
#include "Flap.h"
#include "Rudder.h"
#include "Elevator.h"

// <-- CONSTANTS --> //

// PINS //

// flight control surfaces (PWM)

#define LEFT_OUTER_FLAP_PIN 11
#define LEFT_INNER_FLAP_PIN 0
#define RIGHT_OUTER_FLAP_PIN 3
#define RIGHT_INNER_FLAP_PIN 0

#define LEFT_RUDDER_PIN 9
#define RIGHT_RUDDER_PIN 6

#define LEFT_ELEVATOR_PIN 10
#define RIGHT_ELEVATOR_PIN 5

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
// byte left_flap_pins[] = {LEFT_INNER_FLAP_PIN, LEFT_OUTER_FLAP_PIN};
// byte right_flap_pins[] = {RIGHT_INNER_FLAP_PIN, RIGHT_OUTER_FLAP_PIN};
byte left_flap_pins[] = {LEFT_OUTER_FLAP_PIN};
byte right_flap_pins[] = {RIGHT_OUTER_FLAP_PIN};
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

    Serial.println("joystick:");
    Serial.println("    X (0 - 1023): " + flight_control_joystick.getX());
    Serial.println("    Y (0 - 1023): " + flight_control_joystick.getY());

    // 0 if joystick X < joystick center; 1 if joystick X >= joystick center
    // --> 0 if left;                      1 if right
    bool turningRight = flight_control_joystick.getX() >= flight_control_joystick.getIdleAnalogValue();

    // map from joystick X angle to servo angle from aileron
    int flap_angle = flaps[turningRight].mapAngleFrom(flight_control_joystick.getX(),
                                            flight_control_joystick.getMinAnalogValue() +
                                                (flight_control_joystick.getIdleAnalogValue() * turningRight),
                                            flight_control_joystick.getIdleAnalogValue() +
                                                (flight_control_joystick.getIdleAnalogValue() * turningRight));
    flaps[turningRight].setAngle(flap_angle);
    Serial.println("Ailerons:\n    ");
    Serial.println((turningRight ? "right: " : "left: ") + flap_angle);
    
    // mirror angle over servo center
    int sym_flap_angle = flaps[!turningRight].getIdleServoAngle() +
                            pow(-1, turningRight) * abs(flaps[!turningRight].getIdleServoAngle() - flap_angle);
    flaps[!turningRight].setAngle(sym_flap_angle);
    Serial.print("    ");
    Serial.println((!turningRight ? "right: " : "left: ") + sym_flap_angle);

    // UPDATE SERVO POSITION
    for (FlightControlSurface fcs : all_fcs)
        fcs.move();

}