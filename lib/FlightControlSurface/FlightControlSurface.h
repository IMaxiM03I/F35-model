#include <Arduino.h>

class FlightControlSurface {

    protected:

        byte pin;
        int angle;
    
    public:

        FlightControlSurface(byte pin);

        int getAngle();
        
        void setAngle(int new_angle);

        void move();

        void elevate();

        void lower();

        void center();

        void performCheck();

};