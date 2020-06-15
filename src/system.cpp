#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

std::unordered_map<int, Process> toProcessMap(const std::vector<Process>& processes) {
  std::unordered_map<int, Process> map;

  for (auto process : processes) {
    map.insert(std::make_pair(process.Pid(), process));
  }

  return map;
}

std::vector<Process> toProcessList(std::unordered_map<int, Process> processes) {
  std::vector<Process> list;

  for (auto entry : processes) {
    list.push_back(entry.second);
  }

  return list;
}

Processor& System::Cpu() { return this->cpu_; }

std::vector<Process>& System::Processes() {
  const auto currentPids = LinuxParser::Pids();
  auto processMap = toProcessMap(this->processes_);

  // add processes
  for (int pid : currentPids) {
    const auto prevStat = processMap.find(pid) == processMap.end()
      ? LinuxParser::PidStat()
      : processMap.at(pid).CurrentStats();

    const auto process = Process(
        pid,
        LinuxParser::PidStat(),
        prevStat,
        LinuxParser::UpTime(),
        LinuxParser::Ram(pid),
        LinuxParser::User(pid),
        LinuxParser::Command(pid));

    processMap.insert(std::make_pair(pid, process));
  }

  // remove processes which are no longer present
  for (auto entry : processMap) {
    if (std::find(currentPids.begin(), currentPids.end(), entry.first) == currentPids.end()) {
      processMap.erase(entry.first);
    }
  }

  this->processes_ = toProcessList(processMap);
  return this->processes_;
}

std::string System::Kernel() {
  return LinuxParser::Kernel();
}

float System::MemoryUtilization() {
  return LinuxParser::MemoryUtilization();
}

std::string System::OperatingSystem() {
  return LinuxParser::OperatingSystem();
}

int System::RunningProcesses() {
  return LinuxParser::RunningProcesses();
}

int System::TotalProcesses() {
  return LinuxParser::TotalProcesses();
}

long int System::UpTime() {
  return LinuxParser::UpTime();
}