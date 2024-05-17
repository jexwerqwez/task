#ifndef CLIENT_SIT_EVENT_H_
#define CLIENT_SIT_EVENT_H_

#include "table_event.h"

class ClientSitEvent : public TableEvent {
 public:
  using TableEvent::TableEvent;
  void execute(ComputerClub& club,
               std::vector<std::string>& outputEvents) override;
  std::string toString() const override {
    return time_ + " 2 " + clientName_ + " " + std::to_string(tableNumber_);
  }
};

#endif  // CLIENT_SIT_EVENT_H_
