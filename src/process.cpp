#include <unistd.h>
#include <string>

#include "process.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;

long calculateUptime(const LinuxParser::PidStat& stats, const long systemUptime) {
  return systemUptime - (stats.starttime / sysconf(_SC_CLK_TCK));
}

Process::Process(
    const int pid,
    const LinuxParser::PidStat stats,
    const LinuxParser::PidStat prevStats,
    const long systemUptime,
    const std::string ram,
    const std::string user,
    const std::string command
    ) : pid(pid), stats(stats), prevStats(prevStats), systemUptime(systemUptime),
        ram(ram), user(user), command(command) {}

int Process::Pid() const { return this->pid; }

float Process::CpuUtilization() const {
  auto stats = LinuxParser::Stat(this->pid);

  if (this->prevStats.starttime == -1) {
    // calculations based on:
    // https://stackoverflow.com/questions/16726779/how-do-i-get-the-total-cpu-usage-of-an-application-from-proc-pid-stat/16736599#16736599
    const float processCpuTime = (this->stats.utime + this->stats.stime) / sysconf(_SC_CLK_TCK);
    const float processUptime =  calculateUptime(this->stats, this->systemUptime);
    return processCpuTime / processUptime;
  }

  else {
    const float active = (this->stats.utime + stats.stime) - (this->prevStats.utime + this->prevStats.stime);
    const float deltaTime = std::max((this->stats.starttime - this->prevStats.starttime), 1L) / sysconf(_SC_CLK_TCK);
    return active / deltaTime;
  }
}

string Process::Command() const { return this->command; }

string Process::Ram() const { return this->ram; }

string Process::User() const { return this->user; }

long int Process::UpTime() const { return calculateUptime(this->stats, this->systemUptime); }

LinuxParser::PidStat Process::CurrentStats() const { return this->stats; }

bool Process::operator<(Process const& other) const { return this->CpuUtilization() < other.CpuUtilization(); }