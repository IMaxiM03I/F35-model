#include "FlightControlSurface.h"

class Flap: public FlightControlSurface {

    protected:

        Servo servos[2];

    public:

        Flap(byte servo_pins[]);

};