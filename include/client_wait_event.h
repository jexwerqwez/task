#ifndef CLIENT_WAIT_EVENT_H_
#define CLIENT_WAIT_EVENT_H_

#include "client_event.h"

class ClientWaitEvent : public ClientEvent {
 public:
  using ClientEvent::ClientEvent;
  void execute(ComputerClub& club,
               std::vector<std::string>& outputEvents) override;
  std::string toString() const override { return time_ + " 3 " + clientName_; }
};

#endif  // CLIENT_WAIT_EVENT_H_
