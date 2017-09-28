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

#ifndef SRC_ALGORITHM_H
#define SRC_ALGORITHM_H

#include <string>
#include <vector>
#include <iostream>

namespace algorithm {

enum Algorithms {
  KMP,
  AHO_CORASICK,
  SHIFT_OR,
  UKKONEN,
  NO_ALGORITHM
};

std::ostream& operator<< (std::ostream& out, Algorithms algorithm);
Algorithms GetAlgorithm(std::string algorithm_name);

class Algorithm {
public:
  Algorithm();
  virtual void Build(const std::vector<std::string> &patterns);
  virtual int Search(const std::string &text);
protected:
  std::vector<std::string> patterns_;
};

}  // namespace algorithm

#endif  // SRC_ALGORITHM_H
