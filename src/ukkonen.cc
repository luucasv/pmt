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

#include "ukkonen.h"

#include <string.h>

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <fstream>

using std::queue;
using std::vector;
using std::string;

namespace ukkonen {

Ukkonen::NodeTernaryTree::NodeTernaryTree() {
  memset(this->children_, -1, sizeof this->children_);
  this->id_ = this->step_ = -1;
}

Ukkonen::NodeFsm::NodeFsm(bool accept) {
  this->accept_ = accept;
}

void Ukkonen::ProcessFile(const std::string &file_name, bool count_flag) const {
  std::ifstream text_file(file_name.c_str());
  std::string text_line;
  int total_count = 0, lines_count = 0;

  std::cout << "\nFor " << file_name << ": \n";
  while (getline(text_file, text_line)) {
    int line_count = this->Search(text_line);
    if (line_count > 0) {
      if (count_flag) {
        lines_count++;
        total_count += line_count;
      } else {
        std::cout << text_line << '\n';
      }
    }
  }
  if (count_flag) {
    std::cout << total_count << " occurrences in " << lines_count << " lines\n";
  }
}

Ukkonen::Ukkonen(const vector<string> &patterns, int max_error) {
  this->ternary_tree_.assign(1, NodeTernaryTree());
  this->fsm_.assign(patterns.size(), vector<NodeFsm>(0, false));
  for (size_t i = 0; i < patterns.size(); i++) {
    this->BuildFsm(static_cast<int>(i), patterns[i], max_error);
  }
  this->ternary_tree_.clear();
}

void Ukkonen::BuildFsm(int fsm_id, const string &pattern, const int max_error) {
  vector<int> state(pattern.size() + 1, 0), next_state(pattern.size() + 1, 0);
  for (size_t i = 0; i <= pattern.size(); i++) {
    state[i] = std::min(static_cast<int>(i), max_error + 1);
  }
  queue<vector<int>> state_queue;
  state_queue.push(state);
  int root_id = this->InsertState(state);
  this->fsm_[fsm_id].emplace_back(state[pattern.size()] <= max_error);
  this->ternary_tree_[root_id].id_ = 0;
  this->ternary_tree_[root_id].step_ = fsm_id;
  while (!state_queue.empty()) {
    state = state_queue.front();
    state_queue.pop();
    int state_id = this->ternary_tree_[this->InsertState(state)].id_;
    
    for (size_t ch = 0; ch < SIGMA_SIZE; ch++) {
      //========================= calc next_state =============================
      next_state[0] = 0;
      for (size_t j = 1; j <= pattern.size(); j++) {
        unsigned char cur_ch = static_cast<unsigned char>(pattern[j-1]);
        int d = ch == cur_ch ? 0 : 1;
        next_state[j] = d + state[j-1];
        next_state[j] = std::min(next_state[j], 1 + next_state[j-1]);
        next_state[j] = std::min(next_state[j], 1 + state[j]);
        next_state[j] = std::min(next_state[j], max_error + 1);
      }
      
      //======================== insert next_state ============================
      int node_id = this->InsertState(next_state);
      
      //======================= if next_state is new ==========================
      if (this->ternary_tree_[node_id].step_ != fsm_id) {
        this->ternary_tree_[node_id].step_ = fsm_id;
        this->ternary_tree_[node_id].id_ = static_cast<int>(this->fsm_[fsm_id].size());
        this->fsm_[fsm_id].emplace_back(next_state[pattern.size()] <= max_error);
        state_queue.push(next_state);
      }
      
      // ===================== adding link ===================================
      int next_id = this->ternary_tree_[node_id].id_;
      this->fsm_[fsm_id][state_id].children_[ch] = next_id;
    }
  }
}

int Ukkonen::InsertState(const vector<int> &state) {
  int cur = 0;
  for (size_t i = 1; i < state.size(); i++) {
    int child = state[i] - state[i-1] + 1;
    if (this->ternary_tree_[cur].children_[child] == -1) {
      this->ternary_tree_[cur].children_[child] = static_cast<int>(this->ternary_tree_.size());
      this->ternary_tree_.emplace_back();
    }
    cur = this->ternary_tree_[cur].children_[child];
  }
  return cur;
}

inline int Ukkonen::Search(const string &text) const {
  int count = 0;
  for (size_t fsm_id = 0; fsm_id < this->fsm_.size(); fsm_id++) {
    int cur_state = 0;  
    for (size_t i = 0; i < text.size(); i++) {
      unsigned char ch = static_cast<unsigned char>(text[i]);
      cur_state = this->fsm_[fsm_id][cur_state].children_[ch];
      count += this->fsm_[fsm_id][cur_state].accept_;
    }
  }
  return count;
}

}  // namespace ukkonen
