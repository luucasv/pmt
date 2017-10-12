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

#include "wu_manber_64.h"

#include <stdint.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

const size_t SIGMA_SIZE = 500;
namespace wu_manber_64 {

vector<uint_fast64_t> BuildPatternMask(const string &pattern) {
  vector<uint_fast64_t> masks(SIGMA_SIZE, ~uint_fast64_t(0));
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

WuManber64::WuManber64(const vector<string> &patterns, size_t max_error = 0) {
  this->pattern_masks_.assign(patterns.size(), vector<uint_fast64_t>());
  this->lengths_.assign(patterns.size(), 0);
  for (size_t i = 0; i < patterns.size(); i++) {
    this->pattern_masks_[i] = BuildPatternMask(patterns[i]);
    this->lengths_[i] = patterns[i].size();
  }
  this->max_error_ = max_error;
}

int WuManber64::Search(const string &text) const {
  int count = 0;
  for (size_t p = 0; p < this->pattern_masks_.size(); p++) {
    size_t pattern_length = this->lengths_[p];
    vector<uint_fast64_t> dp[2];
    dp[0].assign(this->max_error_ + 1, ~uint_fast64_t(0));
    for (size_t i = 1; i <= this->max_error_; i++) {
      dp[0][i] = dp[0][i - 1] << 1;
    }
    dp[1] = dp[0];
    for (size_t i = 0; i < text.length(); i++) {
      dp[1][0] = dp[0][0];
      dp[1][0] <<= 1;
      dp[1][0] |= this->pattern_masks_[p][(unsigned char) text[i]];
      for (size_t j = 1; j <= this->max_error_; j++) {
        // remoção de letra
        dp[1][j] = dp[0][j - 1];
        // troca de letra
        dp[1][j] &= (dp[0][j - 1] << 1);
        // adição de letra
        dp[1][j] &= (dp[1][j - 1] << 1);
        // match
        unsigned char cur_ch = static_cast<unsigned char>(text[i]);
        dp[1][j] &= ((dp[0][j] << 1) | this->pattern_masks_[p][cur_ch]);
      }
      if (((dp[1][this->max_error_] >> (pattern_length - 1)) & 1) == 0) {
        count++;
      }
      dp[1].swap(dp[0]);
    }
  }
  return count;
}

}  // namespace wu_manber_64
