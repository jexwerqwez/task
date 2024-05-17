#ifndef CLIENT_ARRIVAL_EVENT_H_
#define CLIENT_ARRIVAL_EVENT_H_

#include "client_event.h"

class ClientArrivalEvent : public ClientEvent {
 public:
  using ClientEvent::ClientEvent;
  void execute(ComputerClub& club,
               std::vector<std::string>& outputEvents) override;
  std::string toString() const override { return time_ + " 1 " + clientName_; }
};

#endif  // CLIENT_ARRIVAL_EVENT_H_
