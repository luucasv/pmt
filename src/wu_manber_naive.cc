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

#include "wu_manber_naive.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace wu_manber_naive {

WuManberNaive::WuManberNaive(const vector<string> &patterns, size_t max_error = 0) {
  this->patterns_ = patterns;
  this->max_error_ = max_error;
}

int WuManberNaive::Search(const string &text) const {
  int count = 0;
  for(size_t p = 0; p < this->patterns_.size(); p++) {
    vector<vector<bool>> dp[2];
    dp[0].assign(this->max_error_ + 1, vector<bool>(this->patterns_[p].size(), true));
    dp[1] = dp[0];
    for(size_t i = 0; i < text.size(); i++) {
      for(size_t j = 0; j <= this->max_error_; j++) {
        for(size_t k = 0; k < this->patterns_[p].size(); k++) {
          dp[1][j][k] = true;
          if(this->patterns_[p][k] == text[i]) {
            // got matching
            if(k == 0) {
              dp[1][j][k] = false;
            } else {
              dp[1][j][k] = dp[1][j][k] && dp[0][j][k - 1];
            }
          }
          if(k > 0 && j > 0) {
            // deleting this letter
            dp[1][j][k] = dp[1][j][k] && dp[0][j - 1][k - 1];
            // creating a letter
            dp[1][j][k] = dp[1][j][k] && dp[1][j - 1][k - 1];
          }
          if(j > 0) {
            // if there's an occurence of at most j - 1 errors, there's an occurence of at most j errors
            dp[1][j][k] = dp[1][j][k] && dp[1][j - 1][k];
          }
        }
      }
      if(!dp[1][this->max_error_][this->patterns_[p].size() - 1]) {
        count++;
      }
      dp[1].swap(dp[0]);
    }
  }
  return count; 
}

}  // namespace wu_manber_naive
