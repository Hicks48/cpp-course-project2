#ifndef FILE_PARSER_H
#define FILE_PARSER_H

#include <string>
#include <regex>
#include <utility>
#include <optional>
#include <unordered_map>
#include <vector>
#include <fstream>

// namespace to store helper functions not usable to file parser clients
namespace {
  std::optional<std::pair<std::string, std::vector<std::string>>> ParseLine(const std::regex& pattern, const std::string& line) {
    std::smatch match;
    bool matches = std::regex_search(line, match, pattern);

    // if line matches then it can be parsed
    if (matches && match.size() > 0) {
      // first match is always interpret as the key
      const std::string key = match[1];

      // index zero is full match and groups are in the following indexes
      // add group matches to vector
      std::vector<std::string> groups;
      for (unsigned int i = 2; i < match.size(); i++) {
        groups.push_back(match[i].str());
      }

      return std::optional{std::make_pair(key, groups)};
    }

      // if line did not match then it return empty optional
    else {
      return std::nullopt;
    }
  }
}

namespace FileParser {
  // template functions must be defined in the header file
  template <typename T>
  std::unordered_map<std::string, T> ParseFile(
      const std::string &linePattern,
      const std::string &filepath,
      T (*lineFactory)(std::vector<std::string>),
      int numberOfLinesToParse = -1) {

    std::unordered_map<std::string, T> contents;

    std::fstream file(filepath);
    if (!file.is_open()) {
      return contents;
    }

    std::regex pattern(linePattern);
    std::string line;
    int lineNumber = 0;

    // continue parsing as long as there are lines and the number of parsed lines is not numberOfLinesToParse
    // -1 in numberOfLinesToParse indicates that whole file should be parsed
    while (std::getline(file, line) && (numberOfLinesToParse == -1 || lineNumber < numberOfLinesToParse)) {
      auto parsed = ParseLine(pattern, line);
      if (parsed.has_value()) {
        contents.insert(std::make_pair(parsed.value().first, lineFactory(parsed.value().second)));
      }

      lineNumber++;
    }

    return contents;
  }
}

#endif