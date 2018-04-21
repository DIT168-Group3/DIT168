/*
 * Author: Martin Chukaleski 04.19.2018
 */

#include "Decision.hpp"

using namespace std;

opendlv::proxy::GroundSteeringReading msgSteering;
opendlv::proxy::PedalPositionReading msgPedal;


int main(int argc, char **argv) {

    auto arguments = cluon::getCommandlineArguments(argc, argv);
    // convert the arg to correct type
    //the cid is used to receive and store data about distance, angle and speed
    const uint16_t cid = (uint16_t) std::stoi(arguments["cid"]);
    //the cid2 is used to send the data to proxy
    const uint16_t cid2 = (uint16_t) std::stoi(arguments["cid2"]);
    const uint16_t runFreq = (uint16_t) std::stoi(arguments["freq"]);
    const bool VERBOSE{arguments.count("verbose") != 0};


    float speed = 0; // the leader speed
    float angle = 0; // the leader angle
    float distance = 0; // the internal distance
    const float obstacle_distance = 0.12;

    //Get the speed, angle and distance from the remote or v2v protocol and store them
    cluon::OD4Session od4(cid,[&speed, &angle, &distance](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == opendlv::proxy::GroundSteeringReading::ID()) {
            opendlv::proxy::GroundSteeringReading receivedMsg = cluon::extractMessage<opendlv::proxy::GroundSteeringReading>(std::move(envelope));
            angle = receivedMsg.steeringAngle();
        }
        else if (envelope.dataType() == opendlv::proxy::PedalPositionReading::ID()) {
            opendlv::proxy::PedalPositionReading receivedMsg = cluon::extractMessage<opendlv::proxy::PedalPositionReading>(std::move(envelope));
            speed = receivedMsg.percent();
        }
        else if (envelope.dataType() == opendlv::proxy::DistanceReading::ID()) {
            opendlv::proxy::DistanceReading msgDistance = cluon::extractMessage<opendlv::proxy::DistanceReading>(std::move(envelope));
            distance = msgDistance.distance();
        }
    });

    cluon::OD4Session internal{cid2};

    if(od4.isRunning() == 0 || internal.isRunning() == 0)
    {
        std::cout << "ERROR: No od4 running!!!" << std::endl;
        return -1;
    }

    //Send the movement commands with the runtime freq
    auto printSensorData{[&distance, &speed, &angle, &VERBOSE, &internal, &obstacle_distance]() -> bool {
        if(VERBOSE){
            std::cout << "Speed: " << speed << " Angle: "<< angle << " Front Distance: " << distance << std::endl;
        }
        //if sensor detects a smaller value than 0.12 we stop the car so it doesn't crash
        if(obstacle_distance >= distance){
            //sending a message to stop the car
            msgPedal.percent(0.0);
            internal.send(msgPedal);
            if(VERBOSE){
                cout << "Obstacle detected stopping car" << endl;
            }
        }else{
            //sending the proxy with steering messages that we get from the remote or v2v(other car)
            msgSteering.steeringAngle(angle);
            internal.send(msgSteering);
            msgPedal.percent(speed);
            internal.send(msgPedal);
        }
        return true;
    }};
    od4.timeTrigger(runFreq, printSensorData);
}

