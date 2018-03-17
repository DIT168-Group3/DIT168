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

using namespace std;

int main(int /*argc*/, char** /*argv*/) {

    od4p = new cluon::OD4Session (111,[](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == (uint8_t) opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            cout << "Sent a message for ground steering to " << receivedMsg.steeringAngle() << "." << endl;
        }
        else if (envelope.dataType() == (uint8_t) opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            cout << "Sent a message for pedal position to " << receivedMsg.percent() << "." << endl;
        }
    });

    if(od4p->isRunning() == 0)
    {
            cout << "OD4 is not running CLOSING!" << endl;
        return -1;
    }

    cout << "VEHICLE_CONTROL" << std::endl;

    // lets check the value of the speed and angle
    cout << "SPEED VALUE: "<< car.get_speed()<< "." << endl;
    cout << "ANGLE VALUE: "<< car.get_angle()<< "." << endl;
    car.moveForward(od4p);
    car.stop(od4p);
    //setting the speed and angle
    car.set_speed(0.4);
    car.set_angle(15.0);
    car.turnLeft(od4p);
    car.stop(od4p);
    car.turnRight(od4p);
    car.stop(od4p);
    // lets check the value of the speed and angle again
    cout << "SPEED VALUE: "<< car.get_speed()<< "." << endl;
    cout << "ANGLE VALUE: "<< car.get_angle()<< "." << endl;


    return 0;
}
