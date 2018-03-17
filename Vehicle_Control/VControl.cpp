/*
 * Author: Martin Chukaleski 03.16.2018
 */

#include "VControl.hpp"


void VControl::moveForward(cluon::OD4Session *od4_pointer){

    std::cout << "MOVING_FORWARD..." << std::endl;
    msgSteering.steeringAngle(0.0);
    od4_pointer->send(msgSteering);
    msgPedal.percent(0.4);
    od4_pointer->send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

}

void VControl::stop(cluon::OD4Session *od4_pointer){

    std::cout << "STOPPING ..." << std::endl;
    msgPedal.percent(0.0);
    od4_pointer->send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));

}

void VControl::turnLeft(cluon::OD4Session *od4_pointer){

    std::cout << "TURN LEFT ..." << std::endl;
    msgSteering.steeringAngle(-15.0);
    od4_pointer->send(msgSteering);
    msgPedal.percent(0.2);
    od4_pointer->send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay/2));
}

void VControl::turnRight(cluon::OD4Session *od4_pointer){

    std::cout << "TURN RIGHT ..." << std::endl;
    msgSteering.steeringAngle(15.0);
    od4_pointer->send(msgSteering);
    msgPedal.percent(0.2);
    od4_pointer->send(msgPedal);
    std::this_thread::sleep_for(std::chrono::milliseconds(delay/2));
}




