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

#include "util.h"

#include <algorithm>
#include <utility>
#include <iostream>

namespace util {

std::pair<bool, int> StringToInt(const char *str) {
  if (str[0] == '\0' || (!isdigit(str[0]) && str[0] != '-' && str[0] != '-')) {
    return std::make_pair(false, 0);
  }
  char *end;
  int ans = static_cast<int>(strtol(str, &end, 10L));
  return std::make_pair(*end == '\0', ans);
}

void StringToLower(std::string *str) {
  std::transform((*str).begin(), (*str).end(), (*str).begin(), ::tolower);
}

}  // namespace util
