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

#include "kmp.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;

namespace kmp {

void KMP::ProcessFile(const std::string &file_name, bool count_flag) const {
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

vector<int> getBorder(const string &pattern) {
  int m = static_cast<int>(pattern.size());
  vector<int> border(m + 1, -1);
  if (m == 1 || (m > 1 && pattern[0] != pattern[1])) {
    border[1] = 0;
  }
  int i = 1;
  int j = 0;
  while (i < m) {
    while (i + j < m && pattern[i + j] == pattern[j]) {
      j++;
      if (i + j == m || pattern[j] != pattern[i + j]) {
        border[i + j] = j;
      } else {
        border[i + j] = border[j];
      }
    }
    if (j == 0 && (i == m - 1 || pattern[0] != pattern[i + 1])) {
      border[i + 1] = 0;
    }
    i = i + j - border[j];
    j = std::max(0, border[j]);
  }
  return border;
}

inline int Search(const string &text, const vector<int> &border, const string &pattern) {
  int count = 0;
  int n = static_cast<int>(text.size());
  int m = static_cast<int>(pattern.size());
  int i = 0;
  int j = 0;
  while (i <= n - m) {
    while (j < m && text[i + j] == pattern[j]) {
      j++;
    }
    if (j == m) {
      count++;
    }
    i += std::max(1, (j - border[j]));
    j = std::max(0, border[j]);
  }
  return count;
}

KMP::KMP(const vector<string> &patterns) {
  this->patterns_ = patterns;
  this->borders_.resize(patterns.size());
  for (size_t i = 0; i < patterns.size(); i++) {
    this->borders_[i] = getBorder(patterns[i]);
  }
}

// return the number of occorencies of the patterns_ in the text
inline int KMP::Search(const string &text) const {
  int count = 0;
  for (size_t i = 0; i < patterns_.size(); i++) {
    count += kmp::Search(text, this->borders_[i], this->patterns_[i]);
  }
  return count;
}

}  // namespace kmp
