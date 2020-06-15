#include <string>
#include <math.h>

#include "format.h"

using std::string;

string Format::ElapsedTime(const long totalSeconds) {
  const int seconds = totalSeconds % 60;
  const int minutes = floor(totalSeconds / 60);
  const int hours = floor(minutes / 60);
  return std::to_string(hours) + ":" + std::to_string(minutes) + ":" + std::to_string(seconds);
}