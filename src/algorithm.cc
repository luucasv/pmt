/*
Copyright (c) 2017 Lucas V. da C. Santana and Tiago Figueiredo Gonçalves

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

Written by: Lucas V. da C. Santana <lvcs@cin.ufpe.br>
            Tiago Figueiredo Gonçalves <tfg@cin.ufpe.br>
*/

#include "algorithm.h"

#include <string>

#include "algorithm_base.h"
#include "util.h"
#include "naive.h"

namespace algorithm {

AlgorithmEnum GetAlgorithmEnum(std::string algorithm_name) {
  util::StringToLower(&algorithm_name);
  if (algorithm_name == "kmp") {
    return KMP;
  } else if (algorithm_name == "aho_corasick") {
    return AHO_CORASICK;
  } else if (algorithm_name == "shift_or") {
    return SHIFT_OR;
  } else if (algorithm_name == "ukkonen") {
    return UKKONEN;
  } else if (algorithm_name == "naive") {
    return NAIVE;
  } else if (algorithm_name == "sellers") {
    return SELLERS;
  } else if (algorithm_name == "wu_manber") {
    return WU_MANBER;
  } else {
    return NO_ALGORITHM;
  }
}

bool IsAproximatedMatchAlgorithm(AlgorithmEnum algorithm) {
  return algorithm == WU_MANBER || algorithm == SELLERS || algorithm == UKKONEN;
}

Algorithm* GetAlgorithm(AlgorithmEnum algorithm) {
  // TODO(lvcs): add all algorithms
  if (algorithm == NAIVE) {
    return new naive::Naive();
  } else {
    return nullptr;
  }
}

}  // namespace algorithm