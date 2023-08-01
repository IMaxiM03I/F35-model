#include"FlightControlSurface.h"

#define GET_ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))


// static methods

int FlightControlSurface::getMaxServoAngle() { return MAX_SERVO_ANGLE; }

int FlightControlSurface::getMinServoAngle() { return MIN_SERVO_ANGLE; }

int FlightControlSurface::getIdleServoAngle() { return IDLE_SERVO_ANGLE; }

int FlightControlSurface::getServoTurnRate() { return SERVO_TURN_RATE; }

int FlightControlSurface::getServoDelay() { return SERVO_DELAY; }


// object methods

FlightControlSurface::FlightControlSurface(byte servo_pins[]) {

    size_t n_servo_pins = GET_ARRAY_SIZE(servo_pins);
    size_t n_servos = GET_ARRAY_SIZE(servos);
    #if n_servo_pins != n_servos
    #error "Number of servo pins does not match number of servos"
    #endif

    this->angle = IDLE_SERVO_ANGLE;
    this->target_angle = IDLE_SERVO_ANGLE;
    
    for (size_t i = 0; i < GET_ARRAY_SIZE(servos); i++) {
        servos[i] = Servo();
        servos[i].attach(servo_pins[i]);
    }

}

void FlightControlSurface::moveServos() {
    
    for (Servo servo : servos)
        servo.write(angle);
    delay(SERVO_DELAY);

}

int FlightControlSurface::getAngle() {
    return angle;
}

void FlightControlSurface::setAngle(int new_angle) {
    this->target_angle = new_angle;
}

void FlightControlSurface::move() {
    
    if (abs(target_angle - angle) > SERVO_TURN_RATE) {
        
        if (target_angle < angle)
            angle -= SERVO_TURN_RATE;
        else
            angle += SERVO_TURN_RATE;
        
    } else if (angle != target_angle)
        angle = target_angle;
    
    moveServos();
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

    auto wait = [](int target, int actual) {
        while (target != actual)
            continue;
    };

    elevate();
    wait(target_angle, angle);
    center();
    wait(target_angle, angle);

    lower();
    wait(target_angle, angle);
    center();
    wait(target_angle, angle);

}