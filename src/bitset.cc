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

#include "bitset.h"

namespace bitset {

// Bitset Reference

bool Bitset::BitsetReference::operator=(const bool value) {
  if (value) {
    (*bucket_reference_) |= (bucket_t(1) << position_);
  } else {
    (*bucket_reference_) &= ~(bucket_t(1) << position_);
  }
  return value;
}

Bitset::BitsetReference::operator bool() const {
   return bool( ((*bucket_reference_) >> position_) & bucket_t(1) );
}

// Bitset
Bitset::Bitset() {
  this->length = 0;
}
Bitset::Bitset(size_t length, bool start_value = true) {
  this->length = length;
  size_t qtd_buckets = (length + BUCKET_SIZE - 1) / BUCKET_SIZE;
  bucket_t bucket_value;
  if (start_value) {
    bucket_value = ~(bucket_t(0));
  } else {
    bucket_value = bucket_t(0);
  }
  this->buckets_.assign(qtd_buckets, bucket_value);
  if (length % BUCKET_SIZE != 0) {
    this->buckets_[qtd_buckets - 1] &= (bucket_t(1) << );
  }
}
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



}  // namespace bitset
