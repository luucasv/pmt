/* Copyright (C) Lucas Santana and Tiago Gonçalves - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lucas Santana <lvcs@cin.ufpe.br> and
 *  Tiago Gonçalves <tfg@cin.ufpe.br>
 * September-Octuber 2017
 */

#ifndef PMT_SRC_LIB_UTIL_H
#define PMT_SRC_LIB_UTIL_H

#include <string>

namespace util {

enum Algorithms {
  KMP,
  AHO_CORASICK,
  SHIFT_OR,
  UKKONEN,
  NO_ALGORITHM
};

Algorithms GetAlgorithm(std::string algorithm_name);
}

#endif
