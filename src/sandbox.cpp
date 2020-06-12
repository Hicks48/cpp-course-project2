//
// Created by Henri Korpela on 6.6.2020.
//

#include "file_parser.h"

#include <string>
#include <vector>
#include <iostream>

int main() {
  /*auto content = FileParser::ParseFile<std::string>(
      "^(Uid):\\s+([0-9]+)\\s+.*$",
      "/Users/henrikorpela/Documents/pid-status.txt",
      [](std::vector<std::string> groups) {
        return groups[0];
      });*/

  auto content = FileParser::ParseFile<std::string>(
      "^(Uid):\\s+([0-9]+)\\s+.*$",
      "/Users/henrikorpela/Documents/pid-status.txt",
      [](std::vector<std::string> groups) {
        return groups[0];
      })

  for (auto it = content.begin(); it != content.end(); it++) {
    auto key = it->first;
    std::cout << key << " -> " << content[key] << std::endl;
  }
}
  /*auto content = FileParser::ParseFile<CpuStats>(
      "^([A-Za-z]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+)\\s+([0-9]+).*$",
      "/Users/henrikorpela/Documents/stat.txt",
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
      },
      3);*/
   /*auto content = FileParser::ParseFile<long>(
      "^([A-Za-z]+):\\s*([0-9]+).*$",
      "/Users/henrikorpela/Documents/temp.txt",
      [](std::vector<std::string> groups) { return std::stol(groups[0]); },
      3);

  std::cout << "size of content: " << content.size() << std::endl;

  for (auto it = content.begin(); it != content.end(); it++) {
    auto key = it->first;
    std::cout << key << " -> " << content[key] << std::endl;
  }

  //const float total = std::stof(content["MemTotal"]);
  //const float free = std::stof(content["MemFree"]);

  //std::cout << "total: " << total << std::endl;
  //std::cout << "free: " << free << std::endl;

  return 0;*/
//}

/*
#include <iostream>
#include <regex>

int main() {
  std::string line("key: -1234 -56789");
  std::regex pattern("^([A-Za-z]+):\\s+-([0-9]+)\\s+-([0-9]+)$");

  std::smatch match;
  bool matches = std::regex_search(line, match, pattern);

  if (matches) {
    std::cout << "size: " << match.size() << std::endl;
    for (int i = 0; i < match.size(); i++) {
      std::cout << i << ": " << match[i] << std::endl;
    }
  } else {
    std::cout << "no match" << std::endl;
  }

  return 0;
}*/