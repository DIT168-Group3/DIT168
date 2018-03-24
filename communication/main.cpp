#include <cstdint>
#include <chrono>
#include <iostream>
#include <sstream>

#include "cluon/OD4Session.hpp"
#include "cluon/Envelope.hpp"
#include "messages.hpp"
#include "Sender.hpp"
#include "Reciever.hpp"

int main(int /*argc*/, char** /*argv*/) {
	Sender send;
	
	//Reciever rcv;
	//rcv.recieveMsg();


    
   cluon::OD4Session od4(111,
        [](cluon::data::Envelope &&envelope) noexcept {
        if (envelope.dataType() == 2001) {
          MyTestMessage1 receivedMsg = cluon::extractMessage<MyTestMessage1>(std::move(envelope));
          std::cout << "Recieved message: "<<receivedMsg.myValue() << "\n" << std::endl;
        }
    });


    //Send messages
    int i = 0;
    while(i<10){
    	send.msg();
	i++;
    }
    

    return 0;
}
