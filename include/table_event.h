#ifndef TABLE_EVENT_H_
#define TABLE_EVENT_H_

#include "client_event.h"

class TableEvent : public ClientEvent {
 protected:
  int tableNumber_;

 public:
  TableEvent(const std::string& time, const std::string& clientName,
             int tableNumber)
      : ClientEvent(time, clientName), tableNumber_(tableNumber) {}
  int getTableNumber() const { return tableNumber_; }
};

#endif  // TABLE_EVENT_H_
