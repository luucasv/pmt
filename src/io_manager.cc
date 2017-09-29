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
#include <iomanip>

#include "algorithm.h"

namespace io_manager {
  
void ProcessFile(
    const std::string &file_name, 
    algorithm::Algorithm *search_algorithm,
    bool count_flag) {
  std::ifstream text_file(file_name.c_str());
  std::cout << "\nFor " << file_name << ": \n";
  std::string text_line;
  long long total_count = 0;
  while (getline(text_file, text_line)) {
    int line_count = search_algorithm->Search(text_line);
    if (line_count > 0 && !count_flag) {
      std::cout << text_line << '\n';
    } else {
      total_count += line_count;
    }
  }
  if (count_flag) {
    std::cout << "Total number of occurences = " << total_count << '\n';
  }
}

}  // namespace io_manager
