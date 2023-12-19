#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

class Logger {
public:
  enum class Level {
    DEBUG,
    INFO,
    WARNING,
    ERROR
  };

private:
  std::ofstream logFile;
  Level logLevel = Level::INFO;

  const std::string RESET = "\033[0m";
  const std::string RED = "\033[31m";
  const std::string GREEN = "\033[32m";
  const std::string YELLOW = "\033[33m";
  const std::string BLUE = "\033[34m";

  // level to colour
  std::string getLevelColor(Level level) {
    switch (level) {
      case Level::DEBUG:   return GREEN;
      case Level::INFO:    return BLUE;
      case Level::WARNING: return YELLOW;
      case Level::ERROR:   return RED;
      default:             return RESET;
    }
  }

  // logging to string representation
  std::string levelToString(Level level) {
    switch (level) {
      case Level::DEBUG:   return "DEBUG";
      case Level::INFO:    return "INFO";
      case Level::WARNING: return "WARNING";
      case Level::ERROR:   return "ERROR";
      default:             return "UNKNOWN";
    }
  }

  std::string getCurrentTime() {
    std::time_t now = std::time(nullptr);
    std::tm* timeinfo = std::localtime(&now);
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%H:%M:%S", timeinfo);
    return buffer;
  }

  void log(const std::string& message, Level level) {
    if (level >= logLevel) {
      std::string color = getLevelColor(level);
      std::stringstream logEntry;
      logEntry << getCurrentTime() << color << " [" << levelToString(level) << "] " << RESET << message << "\n";
      std::cout << logEntry.str();
      if (logFile.is_open()) {
        logFile << getCurrentTime() << " [" << levelToString(level) << "] " << message << "\n";
      }
    }
  }

public:
  Logger(const std::string& filename) : logFile(filename, std::ios::app) {}

  void setLevel(Level newLevel) { logLevel = newLevel; }

  void debug(const std::string& message) { log(message, Level::DEBUG); }

  void info(const std::string& message) { log(message, Level::INFO); }

  void warning(const std::string& message) { log(message, Level::WARNING); }

  void error(const std::string& message) { log(message, Level::ERROR); }
};

extern Logger logger; // global logger

#endif