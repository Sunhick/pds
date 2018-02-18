// Copyright (C) 2018 by Sunil

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <bitset>
#include <vector>

#include "hash.h"

namespace pds {

template <typename T>
using hash = std::function<std::size_t(T)>;

// Space efficient implementation of testing wheather a given elements
// belongs in a set or not. It's probabilisitic because if the bloom filter
// says it's not present then it's definately not member of a given set,
// however if it determines is a member then it could be either true positive
// or false negative.
template <typename T, const std::size_t N>
class BloomFilter {
 private:
  std::vector<hash<T>> hashes;
  std::bitset<N> filter;
  std::size_t getIndex(T element, hash<T>& hash) const;

 public:
  BloomFilter(std::initializer_list<hash<T>> hashes);

  // returns true if the element is proabably present in the set, false
  // otherwise. False definately means element isn't present in the set.
  bool IsMember(T element);

  // Add the given element to the set.
  void Add(T element);
};

template <typename T, const std::size_t N>
BloomFilter<T, N>::BloomFilter(std::initializer_list<hash<T>> hashes)
    : hashes(hashes) {}

template <typename T, const std::size_t N>
bool BloomFilter<T, N>::IsMember(T element) {
  // Test for membership of the element.
  for (auto& hash : hashes) {
    auto index = getIndex(element, hash);
    if (!filter.test(index)) return false;
  }

  return true;
}

template <typename T, const std::size_t N>
void BloomFilter<T, N>::Add(T element) {
  for (auto& hash : hashes) {
    auto index = getIndex(element, hash);
    filter.set(index);
  }
}

template <typename T, const std::size_t N>
std::size_t BloomFilter<T, N>::getIndex(T element, hash<T>& hash) const {
  return static_cast<std::size_t>(hash(element) % N);
}

}  // namespace pds

#endif /* BLOOM_FILTER_H */
