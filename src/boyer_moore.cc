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

#include "boyer_moore.h"

#include <string>
#include <vector>
#include <algorithm>

using std::vector;
using std::string;

namespace boyer_moore {

inline int Search(const string &text, const string &pattern, const vector<int> &bad, const vector<int> &good) {
  int m = static_cast<int>(pattern.size());
  int n = static_cast<int>(text.size());
  int count = 0;
  int i = 0;
  while (i + m <= n) {
    int j = m - 1;
    while (j >= 0 && text[i + j] == pattern[j]) {
      j--;
    }
    if (j < 0) {
      count++;
      i += good[0];
    } else {
      i += std::max(good[j + 1], j - bad[(unsigned char)(text[i + j])]);
    }
  }
  return count;
}

vector<int> getBorder(const string &pattern) {
  int len = static_cast<int>(pattern.size());
  int i = 1;
  int j = 0;
  vector<int> border(len + 1, 0);
  while (i + j < len) {
    while (i + j < len && pattern[i + j] == pattern[j]) {
      j++;
      border[i + j] = j;
    }
    i += std::max(1, (j - border[j]));
    j = border[j];
  }
  return border;
}

vector<int> getBadChar(const string &pattern) {
  vector<int> bad(256, -1);
  for (int i = 0; i < static_cast<int>(pattern.size()); i++) {
    bad[(unsigned char)(pattern[i])] = i;
  }
  return bad;
}

vector<int> getGoodSuffix(const string &pattern) {
  int len = static_cast<int>(pattern.size());
  string reverse = pattern;
  std::reverse(reverse.begin(), reverse.end());
  vector<int> b = getBorder(pattern);
  vector<int> r = getBorder(reverse);
  vector<int> good(len + 1, len - b[len]);
  for (int i = 1; i <= len; i++) {
    int j = len - r[i];
    if (i - r[i] < good[j]) {
      good[j] = i - r[i];
    }
  }
  return good;
}

BoyerMoore::BoyerMoore(const vector<string> &patterns) {
  this->patterns_ = patterns;
  this->bad_char_.resize(patterns.size());
  this->good_suffix_.resize(patterns.size());
  for (size_t i = 0; i < patterns.size(); i++) {
    this->bad_char_[i] = getBadChar(patterns[i]);
    this->good_suffix_[i] = getGoodSuffix(patterns[i]);
  }
}

// return the number of occorencies of the patterns_ in the text
int BoyerMoore::Search(const string &text) const {
  // const int text_size = static_cast<int>(text.size());
  int count = 0;
  for (size_t i = 0; i < patterns_.size(); i++) {
    count += boyer_moore::Search(
      text,
      this->patterns_[i],
      this->bad_char_[i],
      this->good_suffix_[i]
      );
  }
  return count;
}

}  // namespace boyer_moore
