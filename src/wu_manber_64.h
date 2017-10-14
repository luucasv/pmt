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

#ifndef SRC_WU_MANBER_64_H_
#define SRC_WU_MANBER_64_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "algorithm_base.h"

namespace wu_manber_64 {

class WuManber64 : public algorithm::Algorithm {
 public:
  WuManber64(const std::vector<std::string> &patterns, size_t max_error);
  void ProcessFile(const std::string &file_name, bool count_flag) const;

 private:
  int Search(const std::string &text) const;
  std::vector<std::vector<uint_fast64_t>> pattern_masks_;
  std::vector<size_t> lengths_;
  size_t max_error_;
};

}  // namespace wu_manber_64

#endif  // SRC_WU_MANBER_64_H_
