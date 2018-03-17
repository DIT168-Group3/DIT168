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
    const int delay = 1000;
    opendlv::proxy::GroundSteeringReading msgSteering;
    opendlv::proxy::PedalPositionReading msgPedal;

public:
    void moveForward(cluon::OD4Session *od4_pointer);
    void stop(cluon::OD4Session *od4_pointer);
    void turnLeft(cluon::OD4Session *od4_pointer);
    void turnRight(cluon::OD4Session *od4_pointer);
    VControl() = default;

};

#endif
