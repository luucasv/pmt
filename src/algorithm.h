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

#ifndef SRC_ALGORITHM_H_
#define SRC_ALGORITHM_H_

#include <string>
#include <vector>
#include <iostream>

#include "algorithm_base.h"

namespace algorithm {

// All algorithms implemented
enum AlgorithmEnum {
  NAIVE,
  KMP,
  BOYER_MOORE,
  SHIFT_OR,
  SHIFT_OR_64,
  AHO_CORASICK,
  SELLERS,
  UKKONEN,
  WU_MANBER,
  WU_MANBER_64,
  NO_ALGORITHM
};

AlgorithmEnum GetAlgorithmEnum(std::string algorithm_name);
bool IsAproximatedMatchAlgorithm(AlgorithmEnum algorithm);

Algorithm* GetAlgorithm(
  AlgorithmEnum algorithm,
  const std::vector<std::string> &patterns,
  int max_error);

}  // namespace algorithm

#endif  // SRC_ALGORITHM_H_
