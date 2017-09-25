/* Copyright (C) Lucas Santana and Tiago Gonçalves - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lucas Santana <lvcs@cin.ufpe.br> and
 *  Tiago Gonçalves <tfg@cin.ufpe.br>
 * September-Octuber 2017
 */

#ifndef PMT_SRC_LIB_PARSE_ARGS_H
#define PMT_SRC_LIB_PARSE_ARGS_H

#include "util.h"
#include <string>
#include <vector>

namespace parse_args {

struct InputArguments {
  int max_error;
  std::vector<std::string> patterns;
  std::vector<std::string> text_files;
  util::Algorithms algorithm;
  bool count_flag;

  InputArguments(){
    max_error = 0;
    count_flag = false;
    algorithm = util::KMP;
  }
};
// reads all arguments 
InputArguments ParseArgs(int argc, char* const*argv);

}

#endif
