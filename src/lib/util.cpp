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
  std::transform(algorithm_name.begin(), algorithm_name.end(),
      algorithm_name.begin(), ::tolower);
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
