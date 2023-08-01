#include "Joystick.h"
#include "FlightControlSurface.h"

void Joystick::read(byte pin, int &value) {
    value = analogRead(pin);
}

int Joystick::getMinAnalogValue() { return MIN_ANALOG_VALUE; }

int Joystick::getMaxAnalogValue() { return MAX_ANALOG_VALUE; }

Joystick::Joystick(byte xpin, byte ypin) {
    x_pin = xpin;
    y_pin = ypin;
}

void Joystick::read() {
    read(x_pin, x_pos);
    read(y_pin, y_pos);
}

int Joystick::getX() {
    read(x_pin, x_pos);
    return x_pos;
}

int Joystick::getY() {
    read(y_pin, y_pos);
    return y_pos;
}