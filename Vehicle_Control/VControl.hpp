/*
 * Author: Martin Chukaleski 03.16.2018
 */

#ifndef VCONTROL
#define VCONTROL

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"


class VControl {

private:
    const int delay = 1000; // the delay used between commands
    opendlv::proxy::GroundSteeringReading msgSteering;
    opendlv::proxy::PedalPositionReading msgPedal;
    float speed = 0.4; // the default speed
    float angle = 0.0; // the default angle
    const float stop_speed = 0.0;
    int odometer_data = 0;

public:
    void move(cluon::OD4Session *od4_pointer);
    void moveForward(cluon::OD4Session *od4_pointer);
    void stop(cluon::OD4Session *od4_pointer);
    void turnLeft(cluon::OD4Session *od4_pointer);
    void turnRight(cluon::OD4Session *od4_pointer);

    VControl() = default; // default constructor

    void set_speed(float speed); // setters for speed, angle and odometer data
    void set_angle(float angle);
    void set_odometer_data(int odometer);
    float get_speed(); // getters for speed, angle and odometer data
    float get_angle();
    int get_odometer_data();
};

#endif
