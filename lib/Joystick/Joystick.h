#include <Arduino.h>

class Joystick {

    protected:

        static const int MIN_ANALOG_VALUE = 0;
        static const int MAX_ANALOG_VALUE = 1023;
        static const int IDLE_ANALOG_VALUE = (MIN_ANALOG_VALUE + MAX_ANALOG_VALUE) / 2;

        byte x_pin;
        byte y_pin;
        int x_pos;
        int y_pos;

        void read(byte pin, int &value);
    
    public:

        static int getMinAnalogValue();

        static int getMaxAnalogValue();

        static int getIdleAnalogValue();

        Joystick(byte xpin, byte ypin);

        void read();

        int getX();

        int getY();

};