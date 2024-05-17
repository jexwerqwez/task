#include "../include/error_event.h"

#include "../include/computer_club.h"

void ErrorEvent::execute(ComputerClub& club,
                         std::vector<std::string>& outputEvents) {
  outputEvents.push_back(toString());
}
