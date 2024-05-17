#include "../include/client_sit_event.h"

#include "../include/computer_club.h"

void ClientSitEvent::execute(ComputerClub& club,
                             std::vector<std::string>& outputEvents) {
  outputEvents.push_back(toString());
  club.clientSits(time_, clientName_, tableNumber_, outputEvents);
}