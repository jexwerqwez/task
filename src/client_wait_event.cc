#include "../include/client_wait_event.h"

#include "../include/computer_club.h"

void ClientWaitEvent::execute(ComputerClub& club,
                              std::vector<std::string>& outputEvents) {
  outputEvents.push_back(toString());
  club.clientWaits(time_, clientName_, outputEvents);
}