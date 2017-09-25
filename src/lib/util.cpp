/* Copyright (C) Lucas Santana and Tiago Gonçalves - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lucas Santana <lvcs@cin.ufpe.br> and
 *  Tiago Gonçalves <tfg@cin.ufpe.br>
 * September-Octuber 2017
 */

#include "util.h"
#include <algorithm>

util::Algorithms util::GetAlgorithm(std::string algorithm_name) {
  StringToLower(algorithm_name);
  if (algorithm_name == "kmp") {
    return util::KMP;
  } else if (algorithm_name == "aho_corasick") {
    return util::AHO_CORASICK;
  } else if (algorithm_name == "shift_or") {
    return util::SHIFT_OR;
  } else if (algorithm_name == "ukkonen") {
    return util::UKKONEN;
  } else {
    return util::NO_ALGORITHM;
  }
}

std::pair<bool, int> util::StringToInt(const char *str) {
  if(str[0] == '\0' || (!isdigit(str[0]) && str[0] != '-' && str[0] != '-')) {
    return std::make_pair(false, 0);
  }
  char *end;
  int ans = strtol(str, &end, 10);
  return std::make_pair(*end == '\0', ans);
}

inline void util::StringToLower(std::string &str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
