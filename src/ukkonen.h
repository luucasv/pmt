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

#ifndef SRC_UKKONEN_H_
#define SRC_UKKONEN_H_

#include <stdint.h>

#include <string>
#include <vector>

#include "algorithm_base.h"

namespace ukkonen {

const size_t SIGMA_SIZE = 256;

class Ukkonen : public algorithm::Algorithm {
 public:
  Ukkonen(const std::vector<std::string> &patterns, int max_error);
  int Search(const std::string &text) const;

 private:
  void BuildFsm(int fsm_id, const std::string &pattern, const int max_error);
  int InsertState(const std::vector<int> &state);
  struct NodeTernaryTree;
  struct NodeFsm;
  std::vector<NodeTernaryTree> ternary_tree_;
  // each vector is a fsm for a distinct pattern.
  std::vector<std::vector<NodeFsm>> fsm_;
};

struct Ukkonen::NodeTernaryTree {
  int children_[3];
  int id_;
  int step_;
  NodeTernaryTree();
};

struct Ukkonen::NodeFsm {
  int children_[SIGMA_SIZE];
  bool accept_;
  NodeFsm(bool accept);
};

}  // namespace ukkonen

#endif  // SRC_UKKONEN_H_
