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

#ifndef SRC_LIB_PARSE_ARGS_H_
#define SRC_LIB_PARSE_ARGS_H_

#include <string>
#include <vector>

#include "util.h"

namespace parse_args {

struct InputArguments {
  int max_error;
  std::vector<std::string> patterns;
  std::vector<std::string> text_files;
  util::Algorithms algorithm;
  bool count_flag;

  InputArguments();
};

// parse all arguments
InputArguments ParseArgs(int argc, char* const*argv);

}  // namespace parse_args

#endif  // SRC_LIB_PARSE_ARGS_H_
