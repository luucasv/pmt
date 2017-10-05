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

#include <assert.h>

#include <string>

namespace bitset {

// Bitset Reference

Bitset::BitsetReference::BitsetReference(
    bucket_t *bucket_reference,
    size_t position) {
  this->bucket_reference_ = bucket_reference;
  this->position_ = position;
}

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
bucket_t Bitset::GetLowMask(size_t size) {
  assert(size <= BUCKET_SIZE && size > 0);
  if (size == size_t(1)) {
    return bucket_t(1);
  }
  size -= 2;
  bucket_t ans = (bucket_t(1) << size) - 1;
  ans |= bucket_t(1) << (size + 1);
  return ans;
}

Bitset::Bitset() {
  this->length_ = 0;
}

Bitset::Bitset(size_t length, bool start_value) {
  this->length_ = length;
  size_t qtd_buckets = (length + BUCKET_SIZE - 1) / BUCKET_SIZE;
  this->buckets_.resize(qtd_buckets);

  if (start_value) {
    this->set();
  } else {
    this->reset();
  }
}

void Bitset::reset() {
  std::fill(this->buckets_.begin(), this->buckets_.end(), bucket_t(0));
}

void Bitset::reset(size_t position) {
  size_t bucket_id = position / BUCKET_SIZE,
  bucket_position  = position % BUCKET_SIZE;
  this->buckets_[bucket_id] &= ~(bucket_t(1) << bucket_position);
}

void Bitset::set() {
  std::fill(this->buckets_.begin(), this->buckets_.end(), ~(bucket_t(0)));
  size_t qtd_buckets = this->buckets_.size();
  if (this->length_ % BUCKET_SIZE != 0) {
    bucket_t mask = this->GetLowMask(this->length_ % BUCKET_SIZE);
    this->buckets_[qtd_buckets - 1] = mask;
  }
}

void Bitset::set(size_t position) {
  size_t bucket_id = position / BUCKET_SIZE,
  bucket_position  = position % BUCKET_SIZE;
  this->buckets_[bucket_id] |= (bucket_t(1) << bucket_position);
}

bool Bitset::at(size_t position) const {
  size_t bucket_id = position / BUCKET_SIZE,
  bucket_position  = position % BUCKET_SIZE;
  return bool((this->buckets_[bucket_id] >> bucket_position) & bucket_t(1)); 
}

size_t Bitset::length() const {
  return this->length_;
}

bool Bitset::operator[](size_t position) const {
  return this->at(position);
}

Bitset::BitsetReference Bitset::operator[](size_t position) {
  size_t bucket_id = position / BUCKET_SIZE,
  bucket_position  = position % BUCKET_SIZE;
  return Bitset::BitsetReference(&this->buckets_[bucket_id], bucket_position);
}

// places a bit mask currectly buckts_ vector
// first bit will be in start_position
inline void Bitset::set_mask(bucket_t mask, size_t start_position) {
  size_t bucket_id = start_position / BUCKET_SIZE,
  bucket_position  = start_position % BUCKET_SIZE;
  if (bucket_id < this->buckets_.size()) {
    bucket_t first_bits = (mask >> (BUCKET_SIZE - 1 - bucket_position)),
    reset_mask = ~(this->GetLowMask(bucket_position + 1));
    this->buckets_[bucket_id] &= reset_mask;
    this->buckets_[bucket_id] |= first_bits;
  }
  if (bucket_id - 1 >= 0 && bucket_position + 1 != BUCKET_SIZE) {
    bucket_t last_bits = (mask << (bucket_position + 1)),
    reset_mask = this->GetLowMask(BUCKET_SIZE - bucket_position - 1);
    reset_mask <<= (bucket_position + 1);
    reset_mask = ~reset_mask;
    this->buckets_[bucket_id] &= reset_mask;    
    this->buckets_[bucket_id - 1] |= last_bits;
  }
}

// TODO(lvcs): implement shift left and test right shift
Bitset Bitset::operator<<(size_t shift_size) const {
  Bitset res(this->length_, false);
  for (size_t i = this->buckets_.size(); i > 0; i--) {
    res.set_mask(this->buckets_[i-1], i * BUCKET_SIZE - 1 + shift_size);
  }
  return res;
}

Bitset Bitset::operator<<=(size_t shift_size) {
  for (size_t i = this->buckets_.size(); i > 0; i--) {
    bucket_t bucket = this->buckets_[i-1];
    this->buckets_[i-1] = bucket_t(0);
    this->set_mask(bucket, i * BUCKET_SIZE - 1 + shift_size);
  }
  return *this;
}

Bitset Bitset::operator>>(size_t shift_size) const {
  return Bitset();
}

Bitset Bitset::operator>>=(size_t shift_size) {
  return *this;
}

Bitset Bitset::operator|(const Bitset &right_hand) const {
  assert(this->length_ == right_hand.length());
  Bitset ans(this->length_);
  for (size_t i = 0; i < this->buckets_.size(); i++) {
    ans.buckets_[i] = this->buckets_[i] | right_hand.buckets_[i];
  }
  return ans;
}

Bitset Bitset::operator|=(const Bitset &right_hand) {
  assert(this->length_ == right_hand.length());
  for (size_t i = 0; i < this->buckets_.size(); i++) {
    this->buckets_[i] |= right_hand.buckets_[i];
  }
  return *this;
}

Bitset Bitset::operator&(const Bitset &right_hand) const {
  assert(this->length_ == right_hand.length());
  Bitset ans(this->length_);
  for (size_t i = 0; i < this->buckets_.size(); i++) {
    ans.buckets_[i] = this->buckets_[i] & right_hand.buckets_[i];
  }
  return ans;
}

Bitset Bitset::operator&=(const Bitset &right_hand) {
  assert(this->length_ == right_hand.length());
  for (size_t i = 0; i < this->buckets_.size(); i++) {
    this->buckets_[i] &= right_hand.buckets_[i];
  }
  return *this;
}

std::string Bitset::to_string() const {
  std::string ans(this->length_, '0');
  for (size_t i = 0; i < this->length_; i++) {
    ans[i] = this->at(this->length_ - i - 1) ? '1' : '0';
  }
  return ans;
}

}  // namespace bitset
