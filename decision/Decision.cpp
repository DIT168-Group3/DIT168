/*
 * Author: Martin Chukaleski 04.19.2018
 */

#include "Decision.hpp"

using namespace std;


int main(int argc, char **argv) {

    auto arguments = cluon::getCommandlineArguments(argc, argv);
    // convert the arg to correct type
    const uint16_t cid = (uint16_t) std::stoi(arguments["cid"]);
    const uint16_t runFreq = (uint16_t) std::stoi(arguments["freq"]);
    const bool VERBOSE{arguments.count("verbose") != 0};

    //cout << "CID: " << cid << " FREQ: " << runFreq << "\n" << endl;

    //std::shared_ptr<Decision> decision = std::make_shared<Decision>();

    float speed = 0; // the leader speed
    float angle = 0; // the leader angle
    float distance = 0; // the internal distance

    //Get the speed, angle and distance from the car
    cluon::OD4Session od4(cid,[&speed, &angle, &distance](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            angle = receivedMsg.steeringAngle();
            std::cout << "Angle " << receivedMsg.steeringAngle() << "." << std::endl;
        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            speed = receivedMsg.percent();
            std::cout << "Speed: " << receivedMsg.percent() << "." << std::endl;
        }
        else if (envelope.dataType() == opendlv::proxy::DistanceReading::ID()) {
            opendlv::proxy::DistanceReading msgDistance = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            distance = msgDistance.distance();
            cout << "Distance: " << msgDistance.distance() << endl;
        }
    });

    if(od4.isRunning() == 0)
    {
        std::cout << "ERROR: No od4 running!!!" << std::endl;
        return -1;
    }


    //Send the leaderStatus commands with the runtime freq
    auto printSensorData{[&distance, &speed, &angle, &VERBOSE]() -> bool {
        if(VERBOSE){
            std::cout << "Speed: " << speed << " Angle: "<< angle << " Front Distance: " << distance << std::endl;
        }

        return true;
    }};
    od4.timeTrigger(runFreq, printSensorData);


}

