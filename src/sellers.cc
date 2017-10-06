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
#include "sellers.h"

#include <string>
#include <vector>
#include <algorithm>

#include "algorithm_base.h"

using std::string;
using std::vector;

namespace sellers {

Sellers::Sellers(const vector<string> &patterns, int max_error) {
  this->patterns_ = patterns;
  this->max_error_ = max_error;
  this->max_pattern_size_ = 0;
  for (const std::string &pattern : patterns) {
    this->max_pattern_size_ = std::max(this->max_pattern_size_, pattern.size());
  }
}

int Sellers::Search(const string &text) const {
  static vector<vector<int>> memo(2, vector<int>(this->max_pattern_size_ + 1, 0));
  int count = 0;
  for (const string &pattern : this->patterns_) {
    for (size_t j = 0; j <= pattern.size(); j++) {
      memo[0][j] = static_cast<int>(j);
    }
    for (size_t i = 1; i <= text.size(); i++) {
      memo[(i&1)][0] = 0;
      for (size_t j = 1; j <= pattern.size(); j++) {
        int d = text[i-1] == pattern[j-1] ? 0 : 1;
        memo[(i&1)][j] = d + memo[1 - (i&1)][j-1];
        memo[(i&1)][j] = std::min(memo[(i&1)][j], 1 + memo[(i&1)][j-1]);
        memo[(i&1)][j] = std::min(memo[(i&1)][j], 1 + memo[1 - (i&1)][j]);
      }
      if (memo[(i&1)][pattern.size()] <= this->max_error_) {
        count++;
      }
    }
  }
  return count;
}

}  // namespace sellers
