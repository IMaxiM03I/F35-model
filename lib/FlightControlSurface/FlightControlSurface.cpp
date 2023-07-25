#include"FlightControlSurface.h"

FlightControlSurface::FlightControlSurface(byte pin) {

    this->pin = pin;
    this->angle = IDLE_SERVO_ANGLE;
    this->target_angle = IDLE_SERVO_ANGLE;
    servo.attach(pin);

}

void FlightControlSurface::moveServo() {
    servo.write(angle);
    delay(15);
}

int FlightControlSurface::getAngle() {
    return angle;
}

void FlightControlSurface::setAngle(int new_angle) {
    this->target_angle = new_angle;
}

Servo FlightControlSurface::getServo() { 
    return servo;
}

void FlightControlSurface::move() {
    
    if (abs(target_angle - angle) > SERVO_TURN_RATE) {
        
        if (target_angle < angle)
            angle -= SERVO_TURN_RATE;
        else
            angle += SERVO_TURN_RATE;
        
    } else if (angle != target_angle)
        angle = target_angle;
    
    moveServo();
}

void FlightControlSurface::elevate() {
    setAngle(MAX_SERVO_ANGLE);
}

void FlightControlSurface::lower() {
    setAngle(MIN_SERVO_ANGLE);
}

void FlightControlSurface::center() {
    setAngle(IDLE_SERVO_ANGLE);
}

void FlightControlSurface::performCheck() {

    elevate();
    center();
    lower();
    center();

}