#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
  auto cpuStats = LinuxParser::CpuUtilization();

  // calculations are based on:
  // https://stackoverflow.com/questions/23367857/accurate-calculation-of-cpu-usage-given-in-percentage-in-linux
  const float prevIdle = this->prevCpuStats.idle + this->prevCpuStats.iowait;
  const float idle = cpuStats.idle + cpuStats.iowait;

  const float prevActive = this->prevCpuStats.user + this->prevCpuStats.nice +
                           this->prevCpuStats.system + this->prevCpuStats.irq +
                           this->prevCpuStats.softirq + this->prevCpuStats.steal;

  const float active = cpuStats.user + cpuStats.nice + cpuStats.system +
                       cpuStats.irq + cpuStats.softirq + cpuStats.steal;

  const float prevTotal = prevIdle + prevActive;
  const float total = idle + active;

  const float totalDelta = total - prevTotal;
  const float idleDelta = idle - prevIdle;

  // update previous
  this->prevCpuStats = cpuStats;

  // return current utilization
  return (totalDelta - idleDelta) / totalDelta;
}