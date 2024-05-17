#include "../include/computer_club.h"

#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <sstream>

#include "../include/client_arrival_event.h"
#include "../include/client_leave_event.h"
#include "../include/client_sit_event.h"
#include "../include/client_wait_event.h"
#include "../include/error_event.h"

bool ComputerClub::isValidTime(const std::string& time) const {
  std::regex timePattern(R"(\d{2}:\d{2})");
  return std::regex_match(time, timePattern);
}

bool ComputerClub::isValidEventId(const std::string& eventId) const {
  std::regex eventIdPattern(R"(\d)");
  return std::regex_match(eventId, eventIdPattern);
}

bool ComputerClub::isValidNumTables(const std::string& line) const {
  std::regex numTablesPattern(R"(\d+)");
  return std::regex_match(line, numTablesPattern);
}

bool ComputerClub::isValidTimeFormat(const std::string& line) const {
  std::regex timeFormatPattern(R"(\d{2}:\d{2} \d{2}:\d{2})");
  return std::regex_match(line, timeFormatPattern);
}

bool ComputerClub::isValidHourlyRate(const std::string& line) const {
  std::regex hourlyRatePattern(R"(\d+)");
  return std::regex_match(line, hourlyRatePattern);
}

bool ComputerClub::isValidEventFormat(const std::string& line) const {
  std::regex eventFormatPattern(R"(\d{2}:\d{2} \d \w+(\s\d+)?)");
  return std::regex_match(line, eventFormatPattern);
}

bool ComputerClub::isValidClientName(const std::string& clientName) const {
  std::regex clientNamePattern(R"([a-z0-9_-]+)");
  return std::regex_match(clientName, clientNamePattern);
}

bool ComputerClub::isSequentialTime(const std::string& prevTime,
                                    const std::string& currTime) const {
  return prevTime <= currTime;
}

std::unique_ptr<Event> ComputerClub::createEvent(const std::string& line) {
  std::istringstream iss(line);
  std::string time, eventId, clientName;
  iss >> time >> eventId >> clientName;
  if (eventId == "1") {
    return std::make_unique<ClientArrivalEvent>(time, clientName);
  } else if (eventId == "2") {
    int tableNumber;
    iss >> tableNumber;
    if (tableNumber < 1 || tableNumber > numTables_) {
      return std::make_unique<ErrorEvent>(time, "Invalid table number");
    }
    return std::make_unique<ClientSitEvent>(time, clientName, tableNumber);
  } else if (eventId == "3") {
    return std::make_unique<ClientWaitEvent>(time, clientName);
  } else if (eventId == "4") {
    return std::make_unique<ClientLeaveEvent>(time, clientName);
  } else {
    return std::make_unique<ErrorEvent>(time, "Unknown event ID");
  }
}

void ComputerClub::processEvent(const std::unique_ptr<Event>& event) {
  event->execute(*this, outputEvents_);
}

void ComputerClub::readFromFile(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    errorOccurred_ = true;
    return;
  }

  std::string line;
  int lineNum = 1;

  if (!std::getline(file, line) || line.empty()) {
    std::cerr << "Error: File is empty or missing number of tables"
              << std::endl;
    file.close();
    errorOccurred_ = true;
    return;
  }
  if (!isValidNumTables(line) || std::stoi(line) <= 0) {
    std::cerr << "Error in line " << lineNum << ": Invalid number of tables"
              << std::endl;
    file.close();
    errorOccurred_ = true;
    return;
  }
  numTables_ = std::stoi(line);
  lineNum++;

  if (!std::getline(file, line) || line.empty()) {
    std::cerr << "Error in line " << lineNum << ": Missing start and end time"
              << std::endl;
    file.close();
    errorOccurred_ = true;
    return;
  }
  if (!isValidTimeFormat(line)) {
    std::cerr << "Error in line " << lineNum
              << ": Invalid start or end time format" << std::endl;
    file.close();
    errorOccurred_ = true;
    return;
  }
  std::istringstream iss(line);
  iss >> startTime_ >> endTime_;
  lineNum++;

  if (!std::getline(file, line) || line.empty()) {
    std::cerr << "Error in line " << lineNum << ": Missing hourly rate"
              << std::endl;
    file.close();
    errorOccurred_ = true;
    return;
  }
  if (!isValidHourlyRate(line)) {
    std::cerr << "Error in line " << lineNum << ": Invalid hourly rate"
              << std::endl;
    file.close();
    errorOccurred_ = true;
    return;
  }
  hourlyRate_ = std::stoi(line);
  lineNum++;

  std::string prevTime = "00:00";
  while (std::getline(file, line)) {
    if (line.empty()) {
      std::cerr << "Error in line " << lineNum << ": Empty event line"
                << std::endl;
      file.close();
      errorOccurred_ = true;
      return;
    }
    if (!isValidEventFormat(line)) {
      std::cerr << "Error in line " << lineNum << ": Invalid event format"
                << std::endl;
      file.close();
      errorOccurred_ = true;
      return;
    }
    std::istringstream iss(line);
    std::string time, eventId, clientName;
    iss >> time >> eventId >> clientName;
    if (!isValidTime(time)) {
      std::cerr << "Error in line " << lineNum << ": Invalid time format"
                << std::endl;
      file.close();
      errorOccurred_ = true;
      return;
    }
    if (!isSequentialTime(prevTime, time)) {
      std::cerr << "Error in line " << lineNum
                << ": Events are not in sequential time order" << std::endl;
      file.close();
      errorOccurred_ = true;
      return;
    }
    if (!isValidClientName(clientName)) {
      std::cerr << "Error in line " << lineNum << ": Invalid client name"
                << std::endl;
      file.close();
      errorOccurred_ = true;
      return;
    }
    prevTime = time;
    auto event = createEvent(line);
    processEvent(event);
    lineNum++;
  }

  file.close();
}

void ComputerClub::printData() {
  if (errorOccurred_) {
    return;
  }

  std::cout << startTime_ << std::endl;

  closeClub(outputEvents_);

  for (const auto& event : outputEvents_) {
    std::cout << event << std::endl;
  }

  std::cout << endTime_ << std::endl;

  for (int i = 1; i <= numTables_; ++i) {
    int totalMinutes = tableUsage_[i];
    int hoursCharged = (totalMinutes + 59) / 60;
    int revenue = hoursCharged * hourlyRate_;
    std::cout << i << " " << revenue << " " << formatMinutes(totalMinutes)
              << std::endl;
  }
}

void ComputerClub::clientArrives(const std::string& time,
                                 const std::string& clientName,
                                 std::vector<std::string>& outputEvents) {
  if (clients_.count(clientName) > 0) {
    outputEvents.push_back(time + " 13 YouShallNotPass");
    return;
  }
  if (time < startTime_ || time > endTime_) {
    outputEvents.push_back(time + " 13 NotOpenYet");
    return;
  }
  clients_[clientName] = {clientName, -1, time, 0};
}

void ComputerClub::clientSits(const std::string& time,
                              const std::string& clientName, int tableNumber,
                              std::vector<std::string>& outputEvents) {
  if (clients_.count(clientName) == 0) {
    outputEvents.push_back(time + " 13 ClientUnknown");
    return;
  }
  if (tables_.count(tableNumber) > 0 && tables_[tableNumber] != clientName) {
    outputEvents.push_back(time + " 13 PlaceIsBusy");
    return;
  }
  Client& client = clients_[clientName];
  if (client.tableNumber != -1) {
    int duration = calculateMinutes(client.arrivalTime, time);
    client.totalMinutes += duration;
    tableUsage_[client.tableNumber] += duration;
    tables_.erase(client.tableNumber);
  }
  client.tableNumber = tableNumber;
  client.arrivalTime = time;
  tables_[tableNumber] = clientName;
}

void ComputerClub::clientWaits(const std::string& time,
                               const std::string& clientName,
                               std::vector<std::string>& outputEvents) {
  if (tables_.size() < numTables_) {
    outputEvents.push_back(time + " 13 ICanWaitNoLonger!");
    return;
  }
  if (waitingQueue_.size() >= numTables_) {
    outputEvents.push_back(time + " 11 " + clientName);
    return;
  }
  waitingQueue_.push(clientName);
}

void ComputerClub::clientLeaves(const std::string& time,
                                const std::string& clientName,
                                std::vector<std::string>& outputEvents) {
  if (clients_.count(clientName) == 0) {
    outputEvents.push_back(time + " 13 ClientUnknown");
    return;
  }
  Client& client = clients_[clientName];
  if (client.tableNumber != -1) {
    int duration = calculateMinutes(client.arrivalTime, time);
    client.totalMinutes += duration;
    tableUsage_[client.tableNumber] += duration;
    tables_.erase(client.tableNumber);
    if (!waitingQueue_.empty()) {
      std::string nextClientName = waitingQueue_.front();
      waitingQueue_.pop();
      clientSits(time, nextClientName, client.tableNumber, outputEvents);
      outputEvents.push_back(time + " 12 " + nextClientName + " " +
                             std::to_string(client.tableNumber));
    }
  }
  client.tableNumber = -1;
  clients_.erase(clientName);
}

int ComputerClub::calculateMinutes(const std::string& start,
                                   const std::string& end) const {
  int startHour = std::stoi(start.substr(0, 2));
  int startMinute = std::stoi(start.substr(3, 2));
  int endHour = std::stoi(end.substr(0, 2));
  int endMinute = std::stoi(end.substr(3, 2));
  return (endHour * 60 + endMinute) - (startHour * 60 + startMinute);
}

void ComputerClub::closeClub(std::vector<std::string>& outputEvents) {
  for (auto& clientEntry : clients_) {
    Client& client = clientEntry.second;
    if (client.tableNumber != -1) {
      int duration = calculateMinutes(client.arrivalTime, endTime_);
      client.totalMinutes += duration;
      tableUsage_[client.tableNumber] += duration;
      tables_.erase(client.tableNumber);
      outputEvents.push_back(endTime_ + " 11 " + client.name);
    }
  }
}

std::string ComputerClub::formatMinutes(int totalMinutes) const {
  int hours = totalMinutes / 60;
  int minutes = totalMinutes % 60;
  std::ostringstream oss;
  oss << std::setw(2) << std::setfill('0') << hours << ":" << std::setw(2)
      << std::setfill('0') << minutes;
  return oss.str();
}
