#ifndef FLIGHT_CONTROL_SURFACE
#define FLIGHT_CONTROL_SURFACE

#include <Arduino.h>
#include <Servo.h>

class FlightControlSurface {

    protected:

        const int MAX_SERVO_ANGLE = 180;
        const int MIN_SERVO_ANGLE = 0;
        const int IDLE_SERVO_ANGLE = int ((MAX_SERVO_ANGLE - MIN_SERVO_ANGLE) / 2);
        const int SERVO_TURN_RATE = 5;
        const int SERVO_DELAY = 15;

        int angle;
        int target_angle;
        Servo servos[0];

        void moveServos();
    
    public:

        FlightControlSurface(byte servo_pins[]);

        int getAngle();
        
        void setAngle(int new_angle);

        void move();

        void elevate();

        void lower();

        void center();

        void performCheck();

};

#endif