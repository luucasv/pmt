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

#include "aho_corasick.h"

#include <stdlib.h>

#include <queue>
#include <vector>
#include <string>

using std::string;
using std::vector;

namespace aho_corasick {

AhoCorasick::Node::Node() {
  this->fail = 0;
  this->occurences = 0;
  memset(this->children, -1, sizeof this->children);
}

void AhoCorasick::InsertPattern(const string &pattern) {
  size_t cur = 0;
  for (const char ch : pattern) {
    const unsigned char uch = ch;
    if (this->trie[cur].children[uch] == -1) {
      this->trie[cur].children[uch] = static_cast<int>(this->trie.size());
      this->trie.emplace_back();
    }
    cur = this->trie[cur].children[uch];
  }
  this->trie[cur].occurences++;
}

void AhoCorasick::SetFailure() {
  std::queue<int> state_queue;
  for (size_t ch = 0; ch < SIGMA_SIZE; ch++) {
    if (trie[0].children[ch] != -1) {
      state_queue.push(trie[0].children[ch]);
      trie[trie[0].children[ch]].fail = 0;
    } else {
      trie[0].children[ch] = 0;
    }
  }
  while (!state_queue.empty()) {
    int state = state_queue.front();
    state_queue.pop();
    for (size_t ch = 0; ch < SIGMA_SIZE; ch++) {
      int fail = trie[trie[state].fail].children[ch];
      if (trie[state].children[ch] != -1) {
        int next_state = trie[state].children[ch];
        state_queue.push(next_state);
        trie[next_state].fail = fail;
        trie[next_state].occurences += trie[fail].occurences;
      } else {
        trie[state].children[ch] = fail;
      }
    }
  }
}

void AhoCorasick::BuildTrie() {
  for (const string &pattern : this->patterns_) {
    this->InsertPattern(pattern);
  }
}

AhoCorasick::AhoCorasick(const vector<string> &patterns) {
  this->patterns_ = patterns;
  this->trie.assign(1, Node());
  this->BuildTrie();
  this->SetFailure();
}

int AhoCorasick::Search(const string &text) const {
  size_t cur_state = 0;
  int count = this->trie[cur_state].occurences;
  for (size_t i = 0; i < text.size(); i++) {
    const unsigned char ch = static_cast<unsigned char>(text[i]);
    cur_state = this->trie[cur_state].children[ch];
    count += this->trie[cur_state].occurences;
  }
  return count;
}

}  // namespace aho_corasick
