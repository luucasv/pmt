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
#include <iostream>

#include "util.h"

namespace algorithm {
// rule to outup a Algorithms
std::ostream& operator<< (std::ostream& out, Algorithms algorithm) {
  if (algorithm == KMP) {
    out << "KMP";
  } else if (algorithm == AHO_CORASICK) {
    out << "AHO_CORASICK";
  } else if (algorithm == SHIFT_OR) {
    out << "SHIFT_OR";
  } else if (algorithm == UKKONEN) {
    out << "UKKONEN";
  } else {
    out << "NO_ALGORITHM";
  }
  return out;
}

Algorithms GetAlgorithm(std::string algorithm_name) {
  util::StringToLower(&algorithm_name);
  if (algorithm_name == "kmp") {
    return KMP;
  } else if (algorithm_name == "aho_corasick") {
    return AHO_CORASICK;
  } else if (algorithm_name == "shift_or") {
    return SHIFT_OR;
  } else if (algorithm_name == "ukkonen") {
    return UKKONEN;
  } else {
    return NO_ALGORITHM;
  }
}

}  // namespace algorithm
