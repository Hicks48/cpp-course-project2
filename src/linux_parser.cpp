#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include <sstream>
#include <unordered_map>
#include <utility>

#include "file_parser.h"
#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;


// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
  auto content = FileParser::ParseFile<float>(
      "^(MemTotal|MemFree|Buffers):\\s*([0-9]+).*$",
      kProcDirectory + kMeminfoFilename,
      [](std::vector<std::string> groups) { return std::stof(groups[0]); });

  const float total = content["MemTotal"];
  const float free = content["MemFree"];
  const float buffers = content["Buffers"];

  return 1.0 - (free / (total - buffers));
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  std::ifstream fileStream(kUptimeFilename);

  // if for some reason file can't be opened return -1 to indicate a problem
  if (!fileStream.is_open()) {
    return -1;
  }

  // read the only line in the file
  std::string line;
  std::getline(fileStream, line);

  // parse line - first number is system uptime in seconds
  // the decimal part is ignored so is effectively floor of system uptime
  long systemUptime = -1;
  std::istringstream lineStream(line);
  lineStream >> systemUptime;

  // round to long
  return systemUptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid[[maybe_unused]]) { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
LinuxParser::CpuStats LinuxParser::CpuUtilization() {
  return FileParser::ParseFile<CpuStats>(
      "^(cpu)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+).*$",
      kProcDirectory + kStatFilename,
      [](std::vector<std::string> groups) {
        return CpuStats{
            std::stol(groups[0]),
            std::stol(groups[1]),
            std::stol(groups[2]),
            std::stol(groups[3]),
            std::stol(groups[4]),
            std::stol(groups[5]),
            std::stol(groups[6]),
            std::stol(groups[7]),
            std::stol(groups[8]),
            std::stol(groups[9]),
        };
      }, 1)["cpu"];
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  auto content = FileParser::ParseFile<int>(
      "^(processes)\\s+([0-9]+).*$",
      kProcDirectory + kStatFilename,
      [](std::vector<std::string> groups) { return std::stoi(groups[0]); });

  return content["processes"];
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  auto content = FileParser::ParseFile<int>(
      "^(procs_running)\\s+([0-9]+).*$",
      kProcDirectory + kStatFilename,
      [](std::vector<std::string> groups) { return std::stoi(groups[0]); });

  return content["procs_running"];
}

string LinuxParser::Command(int pid) {
  return string();
}

string LinuxParser::Ram(int pid) {
  return FileParser::ParseFile<std::string>(
      "^(VmSize):\\s+([0-9]+).*$",
      kProcDirectory + "/" + std::to_string(pid) + "/status",
      [](std::vector<std::string> groups) {
        return groups[0];
      })["VmSize"];
}

string LinuxParser::User(int pid) {
  const std::string uid = FileParser::ParseFile<std::string>(
      "^(Uid):\\s+([0-9]+)\\s+.*$",
      kProcDirectory + "/" + std::to_string(pid) + "/status",
      [](std::vector<std::string> groups) {
        return groups[0];
    })["Uid"];

  const user =

  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid[[maybe_unused]]) {
  return 0;
}