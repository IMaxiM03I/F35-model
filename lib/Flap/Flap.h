#include "FlightControlSurface.h"

class Flap: public FlightControlSurface {

    protected:

        Servo servos[1];

    public:

        Flap(byte servo_pins[]);

};