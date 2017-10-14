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

#include "wu_manber.h"

#include <vector>
#include <string>

#include "bitset.h"

using bitset::Bitset;
using std::vector;
using std::string;

const size_t SIGMA_SIZE = 500;

namespace wu_manber {

void WuManber::ProcessFile(const std::string &file_name, bool count_flag) const {
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

WuManber::WuManber(const vector<string> &patterns, size_t max_error = 0) {
  this->pattern_masks_.assign(patterns.size(), vector<Bitset>());
  for (size_t i = 0; i < patterns.size(); i++) {
    this->pattern_masks_[i] = BuildPatternMask(patterns[i]);
  }
  this->max_error_ = max_error;
}

inline int WuManber::Search(const string &text) const {
  int count = 0;
  for (size_t p = 0; p < this->pattern_masks_.size(); p++) {
    size_t pattern_length = this->pattern_masks_[p][0].length();
    vector<Bitset> dp[2];
    dp[0].assign(this->max_error_ + 1, Bitset(pattern_length, true));
    dp[1] = dp[0];
    for (size_t i = 0; i < text.length(); i++) {
      dp[1][0] = dp[0][0];
      dp[1][0] <<= 1;
      dp[1][0] |= this->pattern_masks_[p][(unsigned char) text[i]];
      for (size_t j = 1; j <= this->max_error_; j++) {
        dp[1][j] = dp[0][j - 1];
        dp[1][j] &= (dp[0][j - 1] << 1);
        dp[1][j] &= (dp[1][j - 1] << 1);
        unsigned char cur_ch = static_cast<unsigned char>(text[i]);
        dp[1][j] &= ((dp[0][j] << 1) | this->pattern_masks_[p][cur_ch]);
      }
      if (!dp[1][this->max_error_].at(pattern_length - 1)) {
        count++;
      }
      dp[1].swap(dp[0]);
    }
  }
  return count;
}

}  // namespace wu_manber
