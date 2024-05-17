#include "../include/client_leave_event.h"

#include "../include/computer_club.h"

void ClientLeaveEvent::execute(ComputerClub& club,
                               std::vector<std::string>& outputEvents) {
  outputEvents.push_back(toString());
  club.clientLeaves(time_, clientName_, outputEvents);
}