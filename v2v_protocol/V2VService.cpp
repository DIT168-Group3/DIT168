#include "V2VService.hpp"

using namespace std;

int main() {
    shared_ptr<V2VService> v2vService = make_shared<V2VService>();

    while (true) {
        int choice;
        cout << "Which message would you like to send?" << endl;
        cout << "(1) AnnouncePresence" << endl;
        cout << "(2) FollowRequest" << endl;
        cout << "(3) FollowResponse" << endl;
        cout << "(4) StopFollow" << endl;
        cout << "(5) LeaderStatus" << endl;
        cout << "(6) FollowerStatus" << endl;
        cout << "(7) Print present ip_collection's" << endl;
        cout << "(#) Nothing, just quit." << endl;
        cout << ">> ";
        cin >> choice;

        switch (choice) {
            case 1: v2vService->announcePresence(); break;
            case 2: v2vService->followRequest(DEMO_CAR_IP); break;
            case 3: v2vService->followResponse(); break;
            case 4: v2vService->stopFollow(DEMO_CAR_IP); break;
            case 5: v2vService->leaderStatus(50, 0, 100); break;
            case 6: v2vService->followerStatus(50, 0, 10, 100); break;
            case 7: v2vService->print_ip(); break;
            default: exit(0);
        }
    }
}

/**
 * Implementation of the V2VService class as declared in V2VService.hpp
 */
V2VService::V2VService() {
    /*
     * The broadcast field contains a reference to the broadcast channel which is an OD4Session. This is where
     * AnnouncePresence messages will be received.
     */
    broadcast = make_shared<cluon::OD4Session>(BROADCAST_CHANNEL,
                        [this](cluon::data::Envelope &&envelope) noexcept {
                            cout << "[OD4] ";
                            switch (envelope.dataType()) {
                                case ANNOUNCE_PRESENCE: {
                                    AnnouncePresence ap = cluon::extractMessage<AnnouncePresence>(move(envelope));
                                    cout << "received 'AnnouncePresence' from '"
                                              << ap.vehicleIp() << ":" << ap.activePort() << "', GroupID '"
                                              << ap.groupId() << "'!" << endl;

                                    /* TODO: monitor these IPs so you know which ones to choose from */

                                    this->add_ip(ap.vehicleIp(),ap.activePort(),ap.groupId());



                                    break;
                                }
                                default: cout << "¯\\_(ツ)_/¯" << endl;
                            }
                        });

    /*
     * Each car declares an incoming UDPReceiver for messages directed at them specifically. This is where messages
     * such as FollowRequest, FollowResponse, StopFollow, etc. are received.
     */
    incoming =
            std::make_shared<cluon::UDPReceiver>("0.0.0.0", DEFAULT_PORT,
                                 [this](string &&data, string &&sender, chrono::system_clock::time_point &&ts) noexcept {
                                     cout << "[UDP] ";
                                     std::pair<int16_t, string> msg = extract(data);

                                     switch (msg.first) {
                                         case FOLLOW_REQUEST: {
                                             FollowRequest followRequest = decode<FollowRequest>(msg.second);
                                             cout << "received '" << followRequest.LongName()
                                                       << "' from '" << sender << "'!" << endl;

                                             // After receiving a FollowRequest, check first if there is currently no car already following.
                                             if (followerIp.empty()) {
                                                 followerIp = sender; // If no, add the requester to known follower slot and establish a
                                                 // sending channel.
                                                 toFollower = make_shared<cluon::UDPSender>(followerIp, DEFAULT_PORT);
                                                 followResponse();
                                             }
                                             break;
                                         }
                                         case FOLLOW_RESPONSE: {
                                             FollowResponse followResponse = decode<FollowResponse>(msg.second);
                                             cout << "received '" << followResponse.LongName()
                                                       << "' with NTPServerIP '" << followResponse.ntpServerIp()
                                                       << "' from '" << sender << "'!" << endl;

                                             /* TODO: implement NTP synchronisation */

                                             break;
                                         }
                                         case STOP_FOLLOW: {
                                             StopFollow stopFollow = decode<StopFollow>(msg.second);
                                             cout << "received '" << stopFollow.LongName()
                                                       << "' from '" << sender << "'!" << endl;

                                             // Clear either follower or leader slot, depending on current role.
                                             if (sender == followerIp) {
                                                 followerIp = "";
                                                 toFollower.reset();
                                             }
                                             else if (sender == leaderIp) {
                                                 leaderIp = "";
                                                 toLeader.reset();
                                             }
                                             break;
                                         }
                                         case FOLLOWER_STATUS: {
                                             FollowerStatus followerStatus = decode<FollowerStatus>(msg.second);
                                             cout << "received '" << followerStatus.LongName()
                                                     << "' from '" << sender << "\tSpeed: "
                                                     << followerStatus.speed() << "\t Angle:"
                                                     << followerStatus.steeringAngle() << "\t Odometer:"
                                                     << followerStatus.distanceTraveled() << "\t Front distance:"
                                                       << followerStatus.distanceFront() << endl;

                                             /* TODO: implement lead logic (if applicable) */


                                             break;
                                         }
                                         case LEADER_STATUS: {
                                             LeaderStatus leaderStatus = decode<LeaderStatus>(msg.second);
                                             cout << "received '" << leaderStatus.LongName()
                                                       << "' from '" << sender << "\tSpeed: "
                                                       << leaderStatus.speed() << "\t Angle:"
                                                       << leaderStatus.steeringAngle() << "\t Odometer:"
                                                       << leaderStatus.distanceTraveled() << endl;

                                             /* TODO: implement follow logic */

                                             break;
                                         }
                                         default: cout << "¯\\_(ツ)_/¯" << endl;
                                     }
                                 });
}

/**
 * This function sends an AnnouncePresence (id = 1001) message on the broadcast channel. It will contain information
 * about the sending vehicle, including: IP, port and the group identifier.
 */
void V2VService::announcePresence() {
    if (!followerIp.empty()) return;
    AnnouncePresence announcePresence;
    announcePresence.vehicleIp(DEMO_CAR_IP);
    announcePresence.activePort(DEFAULT_PORT);
    announcePresence.groupId(DEMO_GROUP_ID);
    broadcast->send(announcePresence);
}

/**
 * This function sends a FollowRequest (id = 1002) message to the IP address specified by the parameter vehicleIp. And
 * sets the current leaderIp field of the sending vehicle to that of the target of the request.
 *
 * @param vehicleIp - IP of the target for the FollowRequest
 */
void V2VService::followRequest(string vehicleIp) {
    if (!leaderIp.empty()) return;
    leaderIp = vehicleIp;
    toLeader = make_shared<cluon::UDPSender>(leaderIp, DEFAULT_PORT);
    FollowRequest followRequest;
    toLeader->send(encode(followRequest));
    cout << "Sending follow request to " << vehicleIp << endl;
}

/**
 * This function send a FollowResponse (id = 1003) message and is sent in response to a FollowRequest (id = 1002).
 * This message will contain the NTP server IP for time synchronization between the target and the sender.
 */
void V2VService::followResponse() {
    if (followerIp.empty()) return;
    FollowResponse followResponse;
    followResponse.ntpServerIp(DEMO_NTP_IP);
    toFollower->send(encode(followResponse));
    cout << "Sending follow response " << endl;
}

/**
 * This function sends a StopFollow (id = 1004) request on the ip address of the parameter vehicleIp. If the IP address is neither
 * that of the follower nor the leader, this function ends without sending the request message.
 *
 * @param vehicleIp - IP of the target for the request
 */
void V2VService::stopFollow(string vehicleIp) {
    StopFollow stopFollow;
    if (vehicleIp == leaderIp){
        toLeader->send(encode(stopFollow));
        cout << "Sending stop follow to leader : "<< vehicleIp << endl;

    }
    else if(vehicleIp == followerIp){
        toFollower->send(encode(stopFollow));
        cout << "Sending stop follow to follower : "<< vehicleIp << endl;
    }

}

/**
 * This function sends a FollowerStatus (id = 3001) message on the leader channel.
 *
 * @param speed - current velocity
 * @param steeringAngle - current steering angle
 * @param distanceFront - distance to nearest object in front of the car sending the status message
 * @param distanceTraveled - distance traveled since last reading
 */
void V2VService::followerStatus(uint8_t speed, uint8_t steeringAngle, uint8_t distanceFront,
                                uint8_t distanceTraveled) {
    if (leaderIp.empty()) return;
    FollowerStatus followerStatus;
    followerStatus.speed(speed);
    followerStatus.steeringAngle(steeringAngle);
    followerStatus.distanceFront(distanceFront);
    followerStatus.distanceTraveled(distanceTraveled);
    toLeader->send(encode(followerStatus));
}

/**
 * This function sends a LeaderStatus (id = 2001) message on the follower channel.
 *
 * @param speed - current velocity
 * @param steeringAngle - current steering angle
 * @param distanceTraveled - distance traveled since last reading
 */
void V2VService::leaderStatus(uint8_t speed, uint8_t steeringAngle, uint8_t distanceTraveled) {
    if (followerIp.empty()) return;
    LeaderStatus leaderStatus;
    leaderStatus.speed(speed);
    leaderStatus.steeringAngle(steeringAngle);
    leaderStatus.distanceTraveled(distanceTraveled);
    toFollower->send(encode(leaderStatus));
}


/**
 * This function adds all the cars that announced their presence on the broadcast chanel to a map called (ip_collection)
 * and it uses the group id as a key and it combines the ip with the port as the value
 * @param ip - ip of the car
 * @param activePort - the port which the car uses to listen on the incoming udp receiver
 * @param id - the Group ID
 * Author: Martin Chukaleski 20.03
 */
void V2VService::add_ip(std::string ip_s,std::uint16_t activePort, std::string id){

    std::string ip_port;
    std::string port;

    ostringstream temp;
    temp<<activePort;
    port=temp.str();
    ip_port = ip_s + ":" + port;
    ip_collection.insert(pair<string, string>(ip_port, id));
}

/**
 * This function is used to print all of the ip which are currently stored in the map ip_collection
 */
void V2VService::print_ip() {

    for(auto elem : ip_collection)
    {
        std::cout << "IP: " << elem.first << " GroupID:  " << elem.second << "\n";
    }

}

/**
 * Gets the current time.
 *
 * @return current time in milliseconds
 *
uint32_t V2VService::getTime() {
    timeval now;
    gettimeofday(&now, nullptr);
    return (uint32_t ) now.tv_usec / 1000;
}
 */

/**
 * The extraction function is used to extract the message ID and message data into a pair.
 *
 * @param data - message data to extract header and data from
 * @return pair consisting of the message ID (extracted from the header) and the message data
 */
pair<int16_t, string> V2VService::extract(string data) {
    if (data.length() < 10) return pair<int16_t, string>(-1, "");
    int id, len;
    stringstream ssId(data.substr(0, 4));
    stringstream ssLen(data.substr(4, 10));
    ssId >> hex >> id;
    ssLen >> hex >> len;
    return pair<int16_t, string> (
            data.length() -10 == len ? id : -1,
            data.substr(10, data.length() -10)
    );
};

/**
 * Generic encode function used to encode a message before it is sent.
 *
 * @tparam T - generic message type
 * @param msg - message to encode
 * @return encoded message
 */
template <class T>
string V2VService::encode(T msg) {
    cluon::ToProtoVisitor v;
    msg.accept(v);
    stringstream buff;
    buff << hex << setfill('0')
         << setw(4) << msg.ID()
         << setw(6) << v.encodedData().length()
         << v.encodedData();
    return buff.str();
}

/**
 * Generic decode function used to decode an incoming message.
 *
 * @tparam T - generic message type
 * @param data - encoded message data
 * @return decoded message
 */
template <class T>
T V2VService::decode(string data) {
    stringstream buff(data);
    cluon::FromProtoVisitor v;
    v.decodeFrom(buff);
    T tmp = T();
    tmp.accept(v);
    return tmp;
}
