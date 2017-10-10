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

#include "io_manager.h"

#include <string>
#include <fstream>
#include <iostream>

#include "algorithm.h"

namespace io_manager {

inline void ProcessFile(
    algorithm::Algorithm *search_algorithm,
    const std::string &file_name,
    bool count_flag) {

  std::ifstream text_file(file_name.c_str());
  std::string text_line;
  int total_count = 0, lines_count = 0;

  std::cout << "\nFor " << file_name << ": \n";
  while (getline(text_file, text_line)) {
    int line_count = search_algorithm->Search(text_line);
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

void ProcessFiles(
    algorithm::Algorithm *search_algorithm,
    const std::vector<std::string> &file_names,
    bool count_flag) {
  
  for (const std::string &file_name : file_names) {
    ProcessFile(search_algorithm, file_name, count_flag);
  }
}

}  // namespace io_manager
