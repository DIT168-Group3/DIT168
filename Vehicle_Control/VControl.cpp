/*
 * Author: Martin Chukaleski 03.16.2018
 */

#include "VControl.hpp"

using namespace std;

void VControl::moveForward(cluon::OD4Session *od4_pointer){

    cout << "MOVING_FORWARD..." << endl;
    msgSteering.steeringAngle(angle);
    od4_pointer->send(msgSteering);
    msgPedal.percent(speed);
    od4_pointer->send(msgPedal);
    this_thread::sleep_for(chrono::milliseconds(delay));

}

void VControl::stop(cluon::OD4Session *od4_pointer){

    cout << "STOPPING ..." << endl;
    msgPedal.percent(stop_speed);
    od4_pointer->send(msgPedal);
    this_thread::sleep_for(chrono::milliseconds(delay));

}

void VControl::turnLeft(cluon::OD4Session *od4_pointer){

    cout << "TURNING LEFT ..." << endl;
    msgSteering.steeringAngle(-(angle));
    od4_pointer->send(msgSteering);
    msgPedal.percent(speed);
    od4_pointer->send(msgPedal);
    this_thread::sleep_for(chrono::milliseconds(delay));
}

void VControl::turnRight(cluon::OD4Session *od4_pointer){

    cout << "TURNING RIGHT ..." << endl;
    msgSteering.steeringAngle(angle);
    od4_pointer->send(msgSteering);
    msgPedal.percent(speed);
    od4_pointer->send(msgPedal);
    this_thread::sleep_for(chrono::milliseconds(delay));
}

void VControl::set_speed(float new_speed){
    speed = new_speed;
}

void VControl::set_angle(float new_angle){
    angle = new_angle;
}

float VControl::get_speed(){
    return speed;
}

float VControl::get_angle(){
    return angle;
}



