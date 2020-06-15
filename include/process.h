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
  Process(int pid, const LinuxParser::PidStat prevStats);
  int Pid() const;
  std::string User() const;
  std::string Command() const;
  float CpuUtilization() const;
  std::string Ram() const;
  long int UpTime() const;
  bool operator<(Process const& a) const;
 private:
  const int pid;
  const LinuxParser::PidStat prevStats;
};

#endif