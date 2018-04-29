/*
 * Author: Martin Chukaleski 04.19.2018
 */

#ifndef DECISION
#define DECISION

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
#include <iomanip>
#include <unistd.h>
#include <sys/time.h>


class Decision {

public:
    opendlv::proxy::GroundSteeringReading msgSteering;
    opendlv::proxy::PedalPositionReading msgPedal;
    opendlv::proxy::DistanceReading msgDistance;

    Decision() = default; // default constructor

};

#endif
