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

#ifndef SRC_BITSET_H_
#define SRC_BITSET_H_

#include <stdint.h>
#include <stdlib.h>

#include <vector>
#include <string>

namespace bitset {

typedef uint_fast64_t bucket_t;
const size_t BUCKET_SIZE = 8 * sizeof(bucket_t);
const bucket_t NO_BITS = 3 + 3, MOD_MASK = (1 << NO_BITS) - 1;
class Bitset {
 public:
  class BitsetReference;
  Bitset();
  Bitset(size_t length, bool start_value = false);
  void reset();
  void reset(size_t position);
  void set();
  void set(size_t position);
  bool at(size_t position) const;
  size_t length() const;
  bool operator[](size_t position) const;
  BitsetReference operator[](size_t position);
  Bitset operator<<(size_t shift_size) const;
  void operator<<=(size_t shift_size);
  /* Bitset operator>>(size_t shift_size) const;
  Bitset operator>>=(size_t shift_size); */
  Bitset operator|(const Bitset &right_hand) const;
  void operator|=(const Bitset &right_hand);
  Bitset operator&(const Bitset &right_hand) const;
  void operator&=(const Bitset &right_hand);
  std::string to_string() const;

 protected:
  std::vector<bucket_t> buckets_;
  inline void set_mask(bucket_t mask, size_t start_position);
  bucket_t GetLowMask(size_t size);

 private:
  size_t length_;
};

class Bitset::BitsetReference {
 public:
  BitsetReference(bucket_t *bucket_reference, size_t position);
  bool operator=(const bool value);
  operator bool() const;
 private:
  bucket_t * bucket_reference_;
  size_t position_;
};

}  // namespace bitset

#endif  // SRC_BITSET_H_