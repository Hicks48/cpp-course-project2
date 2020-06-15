#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

long int calculateUptime(const LinuxParser::PidStat& stats, const long systemUptime) {
  return systemUptime - (stats.starttime / sysconf(_SC_CLK_TCK));
}

Process::Process(int pid) : pid(pid) {}

int Process::Pid() const { return this->pid; }

float Process::CpuUtilization() const {
  // calculations based on:
  // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
  auto stats = LinuxParser::Stat(this->pid);
  const float processCpuTime = (stats.utime + stats.stime) / sysconf(_SC_CLK_TCK);
  const float processUptime =  calculateUptime(stats, LinuxParser::UpTime());
  return processCpuTime / processUptime;
}

string Process::Command() const { return LinuxParser::Command(this->pid); }

string Process::Ram() const { return LinuxParser::Ram(this->pid); }

string Process::User() const { return LinuxParser::User(this->pid); }

long int Process::UpTime() const { return calculateUptime(LinuxParser::Stat(this->pid), LinuxParser::UpTime()); }

// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& other) const {
  return this->CpuUtilization() < other.CpuUtilization();
}