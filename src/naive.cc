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

#include "naive.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using std::vector;
using std::string;

namespace naive {

void Naive::ProcessFile(const std::string &file_name, bool count_flag) const {
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
  
Naive::Naive(const vector<string> &patterns) {
  this->patterns_ = patterns;
}

// return the number of occorencies of the patterns_ in the text
inline int Naive::Search(const string &text) const {
  const int text_size = static_cast<int>(text.size());
  int count = 0;
  for (const string &pattern : this->patterns_) {
    const int pattern_size = static_cast<int>(pattern.size());
    for (int pos = 0; pos < text_size; pos++) {
      int len = 0;
      while (pos + len < text_size && len < pattern_size) {
        if (text[pos + len] != pattern[len]) {
          break;
        } else {
          len++;
        }
      }
      if (len == pattern_size) {
        count++;
      }
    }
  }
  return count;
}

}  // namespace naive
