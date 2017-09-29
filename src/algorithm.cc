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

#include <assert.h>

#include <string>
#include <iostream>

#include "util.h"

using std::vector;
using std::string;

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
  } else if (algorithm == NAIVE) {
    out << "NAIVE";
  } else {
    out << "NO_ALGORITHM";
  }
  return out;
}

Algorithms GetAlgorithm(string algorithm_name) {
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
  } else {
    return NO_ALGORITHM;
  }
}

// Implements virtual functions to do nothing
// It needs to be done or we'll get "undefined reference to typeinfo" error
// at compilation time
// this code should never run
Algorithm::Algorithm() {}

void Algorithm::Build(const vector<string> &patterns) {
  assert(false);
}

int Algorithm::Search(const string &text) {
  assert(false);
  return 0;
}


}  // namespace algorithm
