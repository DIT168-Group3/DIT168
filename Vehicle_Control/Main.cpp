/*
 * Author: Martin Chukaleski 03.16.2018
 */

#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>
#include <thread>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"

#include "messages.hpp"
#include "VControl.hpp"

cluon::OD4Session *od4p;
VControl car;

int main(int /*argc*/, char** /*argv*/) {

    od4p = new cluon::OD4Session (111,[](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() ==  opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            std::cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << std::endl;
        }
        else if (envelope.dataType() ==  opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            std::cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << std::endl;
        }
    });

    if(od4p->isRunning() == 0)
    {
        std::cout << "ERROR: No od4 running!!!" << std::endl;
        return -1;
    }

    std::cout << "Vehicle Control!" << std::endl;

    car.moveForward(od4p);
    car.stop(od4p);
    car.turnLeft(od4p);
    car.stop(od4p);
    car.turnRight(od4p);
    car.stop(od4p);


    return 0;
}
