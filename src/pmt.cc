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

#include "lib/util.h"
#include "lib/parse_args.h"

std::ostream& operator<< (std::ostream& out,
                          const std::vector<std::string>& v) {
  out << "[";
  for (int i = 0; i < static_cast<int>(v.size()); i++) {
    if (i > 0) {
      out << ", ";
    }
    out << '\'' << v[i] << '\'';
  }
  out << ']';
  return out;
}

int main(int argc, char* const* argv) {
  parse_args::InputArguments args = parse_args::ParseArgs(argc, argv);
  std::cout << "max_error  = " << args.max_error << '\n'
            << "patterns   = " << args.patterns << '\n'
            << "text_files = " << args.text_files << '\n'
            << "algorithm  = " << args.algorithm << '\n';
  return EXIT_SUCCESS;
}
