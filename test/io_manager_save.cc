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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <string>
#include <fstream>
#include <iostream>

#include "algorithm.h"

namespace io_manager {

const size_t BUFFER_SIZE = 1 << 26;
char file_buffer[BUFFER_SIZE];
char *line_buffer = NULL;
size_t line_buffer_size = 0;

inline void ProcessFile(
    algorithm::Algorithm *search_algorithm,
    const std::string &file_name,
    bool count_flag) {

  int file_descriptor = open(file_name.c_str(), O_RDONLY);
  if (file_descriptor == -1) {
    std::cerr << "pmt: Error while processing file\n";
    exit(EXIT_FAILURE);
  }

  posix_fadvise(file_descriptor, 0, 0, POSIX_FADV_SEQUENTIAL);

  line_buffer[0] = 0;
  char *line_pos = line_buffer;
  size_t num_bytes;

  std::cout << "\nFor " << file_name << ": \n";
  int lines_count = 0, total_count = 0, line_count;

  while (num_bytes = read(file_descriptor, file_buffer, BUFFER_SIZE), num_bytes > 0) {
    if (num_bytes == static_cast<size_t>(-1)) {
      std::cerr << "pmt: Error while processing file\n";
      exit(EXIT_FAILURE);
    }
    // std::cout << "file_buffer: \n";// << file_buffer << std::endl;
    char *end_pos, *start = file_buffer;
    char *text_line;
    while (end_pos = (char *) memchr(start, '\n', (file_buffer + BUFFER_SIZE) - start),
           end_pos != NULL) {
      *end_pos = 0;
      if (line_pos != line_buffer) {
        size_t length = (end_pos - start);
        if ((line_pos + length) >= (line_buffer + line_buffer_size)) {
          size_t off = line_pos - line_buffer;
          line_buffer_size <<= 1;
          line_buffer = (char *) realloc(line_buffer, sizeof(char) * line_buffer_size);
          line_pos = line_buffer + off;
        }
        strcat(line_pos, start);
        line_pos = line_buffer;
        text_line = line_buffer;
      } else {
        text_line = start;
      }

      // std::cout << "text_line: " << text_line << std::endl;

      line_count = search_algorithm->Search2(text_line);
      if (line_count > 0) {
        if (count_flag) {
          lines_count++;
          total_count += line_count;
        } else {
          std::cout << text_line << '\n';
        }
      }


      start = end_pos + 1;
      *line_pos = 0;
    }

    size_t length = BUFFER_SIZE - (start - file_buffer);
    if ((line_pos + length) >= (line_buffer + line_buffer_size)) {
      size_t off = line_pos - line_buffer;
      line_buffer_size <<= 1;
      line_buffer = (char *) realloc(line_buffer, sizeof(char) * line_buffer_size);
      line_pos = line_buffer + off;
    }
    strcat(line_pos, start);
    line_pos += length;
    // std::cout << "line_buffer: " << line_buffer << " sz = " << line_buffer_size << '\n';
  }

  if (line_pos != line_buffer) {
    line_count = search_algorithm->Search2(line_buffer);
    if (line_count > 0) {
      if (count_flag) {
        lines_count++;
        total_count += line_count;
      } else {
        std::cout << line_buffer << '\n';
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
  
  line_buffer = static_cast<char*>(malloc(BUFFER_SIZE * sizeof(char)));
  line_buffer_size = BUFFER_SIZE;
  for (const std::string &file_name : file_names) {
    ProcessFile(search_algorithm, file_name, count_flag);
  }
  free(line_buffer);
  line_buffer_size = 0;
}

}  // namespace io_manager
