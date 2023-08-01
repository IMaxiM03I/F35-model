#ifndef FLIGHT_CONTROL_SURFACE
#define FLIGHT_CONTROL_SURFACE

#include <Arduino.h>
#include <Servo.h>

class FlightControlSurface {

    protected:

        static const int MAX_SERVO_ANGLE = 180;
        static const int MIN_SERVO_ANGLE = 0;
        static const int IDLE_SERVO_ANGLE = int ((MAX_SERVO_ANGLE - MIN_SERVO_ANGLE) / 2);
        static const int SERVO_TURN_RATE = 5;
        static const int SERVO_DELAY = 15;

        int angle;
        int target_angle;
        Servo servos[0];

        void moveServos();
    
    public:

        static int getMaxServoAngle();
        
        static int getMinServoAngle();

        static int getIdleServoAngle();

        static int getServoTurnRate();

        static int getServoDelay();

        FlightControlSurface(byte servo_pins[]);

        int getAngle();
        
        void setAngle(int new_angle);

        int mapAngleFrom(int value, int min, int max);

        void move();

        void elevate();

        void lower();

        void center();

        void performCheck();

};

#endif