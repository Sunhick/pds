// Copyright (C) 2018 by Sunil

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H

namespace prob {
namespace ds {

// Space efficient implementation of testing wheather a given elements
// belongs in a set or not. It's probabilisitic because if the bloom filter
// says it's not present then it's definately not member of a given set,
// however if it determines is a member then it could be either true positive
// or false negative.
template <typename T>
class BloomFilter {
 public:
  // returns true if the element is proabably present in the set, false
  // otherwise. False definately means element isn't present in the set.
  bool IsMember(T element);

  // Add the given element to the set.
  void Add(T element);
};

template <typename T>
bool BloomFilter<T>::IsMember(T element) {
  // Test for membership of the element.
  return true;
}

template <typename T>
void BloomFilter<T>::Add(T element) {
  // Add the element to the set
}

}  // namespace ds
}  // namespace prob

#endif /* BLOOM_FILTER_H */
