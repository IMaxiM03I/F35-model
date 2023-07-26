#include "FlightControlSurface.h"

class Rudder: public FlightControlSurface {

    protected:

        Servo servos[1];

    public:

        Rudder(byte servo_pins[]);

};