#ifndef COMPUTER_CLUB_H_
#define COMPUTER_CLUB_H_

#include <map>
#include <memory>
#include <queue>
#include <string>
#include <vector>

#include "event.h"

class ComputerClub {
 private:
  int numTables_;
  std::string startTime_;
  std::string endTime_;
  int hourlyRate_;
  std::vector<std::tuple<std::string, std::string, std::string>> events_;
  bool errorOccurred_ = false;

  struct Client {
    std::string name;
    int tableNumber = -1;
    std::string arrivalTime;
    int totalMinutes = 0;
  };

  std::map<std::string, Client> clients_;
  std::map<int, std::string> tables_;
  std::map<int, int> tableUsage_;
  std::queue<std::string> waitingQueue_;
  std::vector<std::string> outputEvents_;

  bool isValidTime(const std::string& time) const;
  bool isValidEventId(const std::string& eventId) const;
  bool isValidNumTables(const std::string& line) const;
  bool isValidTimeFormat(const std::string& line) const;
  bool isValidHourlyRate(const std::string& line) const;
  bool isValidEventFormat(const std::string& line) const;
  bool isValidClientName(const std::string& clientName) const;
  bool isSequentialTime(const std::string& prevTime,
                        const std::string& currTime) const;

  std::unique_ptr<Event> createEvent(const std::string& line);
  void processEvent(const std::unique_ptr<Event>& event);

 public:
  void readFromFile(const std::string& filename);
  void printData();

  void clientArrives(const std::string& time, const std::string& clientName,
                     std::vector<std::string>& outputEvents);
  void clientSits(const std::string& time, const std::string& clientName,
                  int tableNumber, std::vector<std::string>& outputEvents);
  void clientWaits(const std::string& time, const std::string& clientName,
                   std::vector<std::string>& outputEvents);
  void clientLeaves(const std::string& time, const std::string& clientName,
                    std::vector<std::string>& outputEvents);
  int calculateMinutes(const std::string& start, const std::string& end) const;
  void closeClub(std::vector<std::string>& outputEvents);
  std::string formatMinutes(int totalMinutes) const;
};

#endif  // COMPUTER_CLUB_H_
