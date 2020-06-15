#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>

/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(const int pid,
          const LinuxParser::PidStat stats,
          const LinuxParser::PidStat prevStats,
          const long systemUptime,
          const std::string ram,
          const std::string user,
          const std::string command);

  int Pid() const;
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  std::string Ram() const;
  long int UpTime() const;
  LinuxParser::PidStat CurrentStats() const;
  bool operator<(Process const& a) const;
 private:
  const int pid;
  const LinuxParser::PidStat stats;
  const LinuxParser::PidStat prevStats;
  const long systemUptime;
  const std::string ram;
  const std::string user;
  const std::string command;
};

#endif