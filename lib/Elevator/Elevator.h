#include "FlightControlSurface.h"

class Elevator: public FlightControlSurface {

    protected:

        Servo servos[1];

    public:

        Elevator(byte servo_pins[]);

};