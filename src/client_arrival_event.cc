#include "../include/client_arrival_event.h"

#include "../include/computer_club.h"

void ClientArrivalEvent::execute(ComputerClub& club,
                                 std::vector<std::string>& outputEvents) {
  outputEvents.push_back(toString());
  club.clientArrives(time_, clientName_, outputEvents);
}