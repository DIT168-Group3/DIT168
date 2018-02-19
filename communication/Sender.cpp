#include "Sender.hpp"

int main(int argc, char** argv) {
	using namespace std;

	cluon::OD4Session od4(111, [](cluon::data::Envelope) noexcept {});
	//input arguments from main
	if (argc >= 2)
	{
		uint16_t val = stoi(argv[1]);
		MyTestMessage1 msg;
		msg.myValue(val);
		od4.send(msg);
		std::cout << "Message has been sent.... \n";
	} else {

		// 5 test messages send to reciever
		int i = 0;
		while (i < 5) {
			uint16_t value;
			std::cout << "We are in sender............ \n";
			std::cout << "Enter a number as a command: \n";
			std::cin >> value;
			MyTestMessage1 msg;
			msg.myValue(value);
			od4.send(msg);
			std::cout << "Message has been sent.... \n";
			i++;
		}
	}

	return 0;
}
