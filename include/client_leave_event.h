#ifndef CLIENT_LEAVE_EVENT_H_
#define CLIENT_LEAVE_EVENT_H_

#include "client_event.h"

class ClientLeaveEvent : public ClientEvent {
 public:
  using ClientEvent::ClientEvent;
  void execute(ComputerClub& club,
               std::vector<std::string>& outputEvents) override;
  std::string toString() const override { return time_ + " 4 " + clientName_; }
};

#endif  // CLIENT_LEAVE_EVENT_H_
