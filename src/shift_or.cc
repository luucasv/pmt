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

#include "shift_or.h"

#include <vector>
#include <string>

#include "bitset.h"

using bitset::Bitset;
using std::vector;
using std::string;

const size_t SIGMA_SIZE = 500;

namespace shift_or {

vector<Bitset> BuildPatternMask(const string &pattern) {
  vector<Bitset> masks(SIGMA_SIZE, Bitset(pattern.length(), true));
  Bitset at(pattern.length(), true);
  at[0] = 0;
  for (size_t i = 0; i < pattern.length(); i++) {
    masks[pattern[i]] &= at;
    at <<= 1;
    at[0] = 1;
  }
  return masks;
}

ShiftOr::ShiftOr(const vector<string> &patterns) {
  this->pattern_masks_.assign(patterns.size(), vector<Bitset>());
  for (size_t i = 0; i < patterns.size(); i++) {
    this->pattern_masks_[i] = BuildPatternMask(patterns[i]);
  }
}

int ShiftOr::Search(const string &text) {
  int count = 0;
  for (const vector<Bitset> &masks : this->pattern_masks_) {
    size_t pattern_length = masks[0].length(); 
    Bitset actual_mask(pattern_length, true);
    for (size_t i = 0; i < text.length(); i++) {
      actual_mask <<= 1;
      actual_mask |= masks[text[i]];
      if (!actual_mask[pattern_length - 1]) {
        count++;
      }
    }
  }
  return count;
}

}  // namespace shift_or
