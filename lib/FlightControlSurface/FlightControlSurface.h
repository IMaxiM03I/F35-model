#include <Arduino.h>
#include <Servo.h>

class FlightControlSurface {

    protected:

        const int MAX_SERVO_ANGLE = 180;
        const int MIN_SERVO_ANGLE = 0;
        const int IDLE_SERVO_ANGLE = int ((MAX_SERVO_ANGLE - MIN_SERVO_ANGLE) / 2);
        
        const int SERVO_TURN_RATE = 5;

        byte pin;
        int angle;
        int target_angle;
        Servo servo;

        void moveServo();
    
    public:

        FlightControlSurface(byte pin);

        int getAngle();
        
        void setAngle(int new_angle);

        Servo getServo();

        void move();

        void elevate();

        void lower();

        void center();

        void performCheck();

};