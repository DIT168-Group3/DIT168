#include "Reciever.hpp"

int main(int /*argc*/, char** /*argv*/) {
  using namespace std::literals::chrono_literals;

  std::cout << "We are in reciever" << std::endl;

  cluon::OD4Session od4(111,
  [](cluon::data::Envelope && envelope) noexcept {
    if (envelope.dataType() == 2001) {
      MyTestMessage1 receivedMsg = cluon::extractMessage<MyTestMessage1>(std::move(envelope));
      std::cout << "Recieved message: " << receivedMsg.myValue() << "\n" << std::endl;
    }
  });

  while (od4.isRunning()) {
    std::this_thread::sleep_for(2s);
  }

}
