#include <string>
#include <sstream>
#include <math.h>

#include "format.h"

using std::string;

string Format::ElapsedTime(const long totalSeconds) {
  const int seconds = totalSeconds % 60;
  const int minutes = floor(totalSeconds / 60);
  const int hours = floor(minutes / 60);

  std::ostringstream stream;
  stream << (hours >= 10 ? std::to_string(hours) : "0" + std::to_string(hours));
  stream << ":";
  stream << (minutes >= 10 ? std::to_string(minutes) : "0" + std::to_string(minutes));
  stream << ":";
  stream << (seconds >= 10 ? std::to_string(seconds) : "0" + std::to_string(seconds));
  return stream.str();
}