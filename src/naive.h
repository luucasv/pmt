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

#ifndef SRC_NAIVE_H_
#define SRC_NAIVE_H_

#include <string>
#include <vector>

#include "algorithm_base.h"

namespace naive {

class Naive : public algorithm::Algorithm {
 public:
  Naive(const std::vector<std::string> &patterns);
  void ProcessFile(const std::string &file_name, bool count_flag) const;

 private:
  int Search(const std::string &text) const;
};

}  // namespace naive

#endif  // SRC_NAIVE_H_
