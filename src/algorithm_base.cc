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

#include "algorithm_base.h"

#include <assert.h>

#include <vector>
#include <string>

namespace algorithm {

// Implements virtual functions to do nothing
// It needs to be done or we'll get "undefined reference to typeinfo" error
// at compilation time
// this code should never run
Algorithm::Algorithm() {}

Algorithm::~Algorithm() {}

void Algorithm::ProcessFile(const std::string &file_name, bool count_flag) const {
  assert(false);
}

// int Algorithm::Search(const std::string &text) const {
//   assert(false);
//   return 0;
// }


}  // namespace algorithm
