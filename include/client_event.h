#ifndef CLIENT_EVENT_H_
#define CLIENT_EVENT_H_

#include <string>

#include "event.h"

class ClientEvent : public Event {
 protected:
  std::string time_;
  std::string clientName_;

 public:
  ClientEvent(const std::string& time, const std::string& clientName)
      : time_(time), clientName_(clientName) {}
  std::string getTime() const { return time_; }
  std::string getClientName() const { return clientName_; }
};

#endif  // CLIENT_EVENT_H_
