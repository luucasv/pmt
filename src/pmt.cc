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

#include <iostream>

#include "input_parser.h"
#include "algorithm.h"
#include "io_manager.h"

int main(int argc, char* const* argv) {
  input_parser::InputArguments args = input_parser::ParseArgs(argc, argv);
  input_parser::ShowArgs(args);

  algorithm::Algorithm *algorithm = algorithm::GetAlgorithm(args.algorithm,
                                                            args.patterns,
                                                            args.max_error);

  io_manager::ProcessFiles(algorithm, args.text_files, args.count_flag);

  delete algorithm;
  return EXIT_SUCCESS;
}
