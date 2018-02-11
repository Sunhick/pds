// Copyright (C) 2018 by Sunil

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

#include <bitset>

namespace prob {
namespace ds {

// Space efficient implementation of testing wheather a given elements
// belongs in a set or not. It's probabilisitic because if the bloom filter
// says it's not present then it's definately not member of a given set,
// however if it determines is a member then it could be either true positive
// or false negative.
template <typename T, const std::size_t N, template <typename T> class hash>
class BloomFilter {
 private:
  std::bitset<N> filter;
  std::size_t getIndex(T element) const;

 public:
  // returns true if the element is proabably present in the set, false
  // otherwise. False definately means element isn't present in the set.
  bool IsMember(T element);

  // Add the given element to the set.
  void Add(T element);
};

template <typename T, const std::size_t N, template <typename T> class hash>
bool BloomFilter<T, N, hash>::IsMember(T element) {
  // Test for membership of the element.
  auto index = getIndex(element);
  return filter.test(index);
}

template <typename T, const std::size_t N, template <typename T> class hash>
void BloomFilter<T, N, hash>::Add(T element) {
  // std::hash supports only standard types. If you are using custom types
  // then override the std::hash as mentioned in
  // http://en.cppreference.com/w/cpp/utility/hash.
  auto index = getIndex(element);
  filter.set(index);
}

template <typename T, const std::size_t N, template <typename T> class hash>
std::size_t BloomFilter<T, N, hash>::getIndex(T element) const {
  return static_cast<std::size_t>(hash<T>{}(element) % N);
}

}  // namespace ds
}  // namespace prob

#endif /* BLOOM_FILTER_H */
