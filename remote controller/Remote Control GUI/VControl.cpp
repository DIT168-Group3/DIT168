/*
 * Author: Martin Chukaleski 03.16.2018
 */

#include "VControl.hpp"

using namespace std;

/*
 * Method that will be used to drive  and stop the car,
 * only these two are needed since we can set the speed and angle
 */
void VControl::move(cluon::OD4Session *od4_pointer){
    cout << "MOVING VEHICLE IN WANTED DIRECTION..." << endl;

    // TODO: Use odometer data as a metric to move the car and stop when it is fulfilled

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
}

/*
 * Methods used for testing the car movements
 */

void VControl::moveForward(cluon::OD4Session *od4_pointer){

    cout << "MOVING_FORWARD..." << endl;
    msgSteering.steeringAngle(angle);
    od4_pointer->send(msgSteering);
    msgPedal.percent(speed);
    od4_pointer->send(msgPedal);

}

void VControl::turnLeft(cluon::OD4Session *od4_pointer){

    cout << "TURNING LEFT ..." << endl;
    msgSteering.steeringAngle(15);
    od4_pointer->send(msgSteering);
    msgPedal.percent(speed);
    od4_pointer->send(msgPedal);
}

void VControl::turnRight(cluon::OD4Session *od4_pointer){

    cout << "TURNING RIGHT ..." << endl;
    msgSteering.steeringAngle(-(15));
    od4_pointer->send(msgSteering);
    msgPedal.percent(speed);
    od4_pointer->send(msgPedal);
}

void VControl::set_speed(float new_speed){
    speed = new_speed;
}

void VControl::set_angle(float new_angle){
    angle = new_angle;
}

void VControl::set_odometer_data(int odometer) {
    odometer_data = odometer;
}

float VControl::get_speed(){
    return speed;
}

float VControl::get_angle(){
    return angle;
}

int VControl::get_odometer_data() {
    return odometer_data;
}



