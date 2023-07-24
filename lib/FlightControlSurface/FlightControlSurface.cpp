#include"FlightControlSurface.h"

FlightControlSurface::FlightControlSurface(byte pin) {

    this->pin = pin;
    this->angle = 0;

}

int FlightControlSurface::getAngle() {
    return angle;
}

void FlightControlSurface::setAngle(int new_angle) {
    this->angle = new_angle;
}

void FlightControlSurface::move() {}

void FlightControlSurface::elevate() {}

void FlightControlSurface::lower() {}

void FlightControlSurface::center() {}

void FlightControlSurface::performCheck() {

    elevate();
    center();
    lower();
    center();

}