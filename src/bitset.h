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

#ifndef SRC_BITSET_H
#define SRC_BITSET_H

#include <stdint.h>

#include <vector>

namespace bitset {

class Bitset {
 public:
  class BitsetReference;
  Bitset();
  Bitset(size_t length, bool start_value = true);
  void reset();
  void reset(size_t position);
  void set();
  void set(size_t position);
  bool at(size_t position) const;
  BitsetReference operator[](size_t position) const;
  Bitset operator<<(size_t shift_size) const;
  Bitset operator<<=(size_t shift_size);
  Bitset operator>>(size_t shift_size) const;
  Bitset operator>>=(size_t shift_size);
  Bitset operator|(const Bitset &right_hand) const;
  Bitset operator|=(const Bitset &right_hand);
  Bitset operator&(const Bitset &right_hand) const;
  Bitset operator&=(const Bitset &right_hand);

 private:
  typedef uint32_t bucket_t; 
  const size_t BUCKET_SIZE = 8 * sizeof(bucket_t);
  std::vector<bucket_t> buckets_;
  size_t length_;
};

class Bitset::BitsetReference {
 public:
  bool operator=(const bool value);
  operator bool() const;
 private:
  bucket_t * bucket_reference_;
  size_t position_;
};

}  // namespace bitset

#endif  // SRC_BITSET_H