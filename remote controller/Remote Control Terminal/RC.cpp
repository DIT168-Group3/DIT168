#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"

/**
 * Author Martin Chukaleski 26.03
 */

using namespace std;

int main() {

    bool state = true;
    float speed = 0.4;
    float angle = 15;
    cluon::OD4Session *od4 = new cluon::OD4Session (111,[](cluon::data::Envelope) noexcept {});

    opendlv::proxy::GroundSteeringReading msgSteering;
    opendlv::proxy::PedalPositionReading msgPedal;

    cout << "======> Group 3 Remote Control Interface <=====" <<endl;
    cout << "Press 'q' to quit the app, 't' to change the speed and 'u' to change the angle" <<endl;
    cout << "Current speed is: "<< speed << endl;
    cout << "Current angle is: "<< angle << "\n" << endl;
    cout << "**************************"<< endl;
    cout << "**      Commands:       **"<< endl;
    cout << "**          ^           **" << endl;
    cout << "**          w           **" << endl;
    cout << "**    < a   s   d >     **" <<endl;
    cout << "**************************"<< "\n" << endl;

    while (state) {

        cout << "Input a command:" <<endl;
        string input;
        getline(cin, input);

        switch (input.at(0)) {
            case 'w':
                msgPedal.position(speed);
                msgSteering.groundSteering(0);
                cout << "Moving forward \n" << endl;
                break;
            case 'a':
                msgPedal.position(speed);
                msgSteering.groundSteering(angle);
                cout << "Turning left\n" << endl;
                break;
            case 's':
                msgPedal.position(0.0);
                msgSteering.groundSteering(0);
                cout << "Stopping\n" << endl;
                break;
            case 'd':
                msgPedal.position(speed);
                msgSteering.groundSteering(-(angle));
                cout << "Turning right\n" << endl;
                break;
            case 't':
                cout << "Input the new speed NOTE! it has to be a value between 0.0 and 0.5"<< endl;
                cin >> speed;
                cin.clear();
                cout << "Changed the speed to:"<< speed << endl;
                break;
            case 'u':
                cout << "Input the new angle NOTE! it has to be a value between 0 and 15"<< endl;
                cin >> angle;
                cin.clear();
                cout << "Changed the angle to:"<< angle << endl;
                break;
            case 'q':
                state=false;
                cout << "Closing app...." << endl;
                break;
            default:
                cout << "Unknown command stopping the car..."<< endl;
                msgPedal.position(0.0);
                msgSteering.groundSteering(0);
        }
        od4->send(msgSteering);
        od4->send(msgPedal);

    }
}
