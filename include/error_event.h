#ifndef ERROR_EVENT_H_
#define ERROR_EVENT_H_

#include <string>

#include "event.h"

class ErrorEvent : public Event {
 private:
  std::string time_;
  std::string errorMessage_;

 public:
  ErrorEvent(const std::string& time, const std::string& errorMessage)
      : time_(time), errorMessage_(errorMessage) {}
  void execute(ComputerClub& club,
               std::vector<std::string>& outputEvents) override;
  std::string toString() const override {
    return time_ + " 13 " + errorMessage_;
  }
};

#endif  // ERROR_EVENT_H_
