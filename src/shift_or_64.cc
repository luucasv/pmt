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

#include "shift_or_64.h"

#include <stdint.h>

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;

const size_t SIGMA_SIZE = 500;

namespace shift_or_64 {

void ShiftOr64::ProcessFile(const std::string &file_name, bool count_flag) const {
  std::ifstream text_file(file_name.c_str());
  std::string text_line;
  int total_count = 0, lines_count = 0;

  std::cout << "\nFor " << file_name << ": \n";
  while (getline(text_file, text_line)) {
    int line_count = this->Search(text_line);
    if (line_count > 0) {
      if (count_flag) {
        lines_count++;
        total_count += line_count;
      } else {
        std::cout << text_line << '\n';
      }
    }
  }
  if (count_flag) {
    std::cout << total_count << " occurrences in " << lines_count << " lines\n";
  }
}

vector<uint_fast64_t> BuildPatternMask(const string &pattern) {
  vector<uint_fast64_t> masks(SIGMA_SIZE, ~(uint_fast64_t(0)));
  uint_fast64_t at = 0;
  at = ~at;
  at <<= 1;
  for (size_t i = 0; i < pattern.length(); i++) {
    masks[pattern[i]] &= at;
    at <<= 1;
    at |= 1;
  }
  return masks;
}

ShiftOr64::ShiftOr64(const vector<string> &patterns) {
  this->pattern_masks_.assign(patterns.size(), vector<uint_fast64_t>());
  this->lengths_.assign(patterns.size(), 0);
  for (size_t i = 0; i < patterns.size(); i++) {
    this->pattern_masks_[i] = BuildPatternMask(patterns[i]);
    this->lengths_[i] = patterns[i].size();
  }
}

inline int ShiftOr64::Search(const string &text) const {
  int count = 0;
  for (size_t p = 0; p < this->pattern_masks_.size(); p++) {
    size_t pattern_length = this->lengths_[p];
    uint_fast64_t actual_mask = 0;
    actual_mask = ~actual_mask;
    for (size_t i = 0; i < text.length(); i++) {
      actual_mask <<= 1;
      actual_mask |= this->pattern_masks_[p][(unsigned char) text[i]];
      if (((actual_mask >> (pattern_length - 1)) & 1) == 0) {
        count++;
      }
    }
  }
  return count;
}

}  // namespace shift_or_64
