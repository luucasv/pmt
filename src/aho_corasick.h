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

#ifndef SRC_AHO_CORASICK_H_
#define SRC_AHO_CORASICK_H_

#include <stdlib.h>
#include <string.h>

#include <string>
#include <vector>

#include "algorithm_base.h"

namespace aho_corasick {

const size_t SIGMA_SIZE = 256;

class AhoCorasick : public algorithm::Algorithm {
 public:
  AhoCorasick(const std::vector<std::string> &patterns);
  ~AhoCorasick();
  int Search(const std::string &text) const;
 private:
  struct Node;
  std::vector<Node> trie;
};

struct AhoCorasick::Node {
  size_t children[SIGMA_SIZE];
  size_t occurences;
  size_t fail;
  Node() {
    fail = 0;
    occurences = 0;
    memset(children, -1, sizeof children);
  }
}

}  // namespace aho_corasick

#endif  // SRC_AHO_CORASICK_H_
