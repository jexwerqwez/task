#ifndef EVENT_H_
#define EVENT_H_

#include <string>
#include <vector>

class ComputerClub;

class Event {
 public:
  virtual ~Event() = default;
  virtual void execute(ComputerClub& club,
                       std::vector<std::string>& outputEvents) = 0;
  virtual std::string toString() const = 0;
};

#endif  // EVENT_H_
