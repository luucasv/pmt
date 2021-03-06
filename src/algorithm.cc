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

#include <iostream>
#include <string>

#include "algorithm_base.h"
#include "util.h"
#include "naive.h"
#include "shift_or.h"
#include "shift_or_64.h"
#include "sellers.h"
#include "wu_manber.h"
#include "wu_manber_64.h"
#include "wu_manber_naive.h"
#include "aho_corasick.h"
#include "ukkonen.h"
#include "kmp.h"
#include "boyer_moore.h"

namespace algorithm {

AlgorithmEnum GetAlgorithmEnum(std::string algorithm_name) {
  util::StringToLower(&algorithm_name);
  if (algorithm_name == "kmp") {
    return KMP;
  } else if (algorithm_name == "aho_corasick" || algorithm_name == "aho") {
    return AHO_CORASICK;
  } else if (algorithm_name == "shift_or" || algorithm_name == "so") {
    return SHIFT_OR;
  } else if (algorithm_name == "shift_or_64" || algorithm_name == "so64") {
    return SHIFT_OR_64;
  } else if (algorithm_name == "ukkonen") {
    return UKKONEN;
  } else if (algorithm_name == "naive") {
    return NAIVE;
  } else if (algorithm_name == "sellers") {
    return SELLERS;
  } else if (algorithm_name == "wu_manber" || algorithm_name == "wm") {
    return WU_MANBER;
  } else if (algorithm_name == "wu_manber_64" || algorithm_name == "wm64") {
    return WU_MANBER_64;
  } else if (algorithm_name == "boyer_moore" || algorithm_name == "bm") {
    return BOYER_MOORE;
  } else {
    return NO_ALGORITHM;
  }
}

bool IsAproximatedMatchAlgorithm(AlgorithmEnum algorithm) {
  return algorithm == WU_MANBER    || algorithm == SELLERS ||
         algorithm == WU_MANBER_64 || algorithm == UKKONEN;
}

Algorithm* GetAlgorithm(
    AlgorithmEnum algorithm,
    const std::vector<std::string> &patterns,
    int max_error) {
  // TODO(lvcs): add all algorithms
  if (algorithm == NAIVE) {
    return new naive::Naive(patterns);
  } else if (algorithm == SHIFT_OR) {
    return new shift_or::ShiftOr(patterns);
  } else if (algorithm == SHIFT_OR_64) {
    return new shift_or_64::ShiftOr64(patterns);
  } else if (algorithm == SELLERS) {
    return new sellers::Sellers(patterns, max_error);
  } else if (algorithm == WU_MANBER) {
    return new wu_manber::WuManber(patterns, max_error);
  } else if (algorithm == WU_MANBER_64) {
    return new wu_manber_64::WuManber64(patterns, max_error);
  } else if (algorithm == AHO_CORASICK) {
    return new aho_corasick::AhoCorasick(patterns);
  } else if (algorithm == UKKONEN) {
    return new ukkonen::Ukkonen(patterns, max_error);
  } else if (algorithm == KMP) {
    return new kmp::KMP(patterns);
  } else if (algorithm == BOYER_MOORE) {
    return new boyer_moore::BoyerMoore(patterns);
  } else {
    return nullptr;
  }
}

}  // namespace algorithm
