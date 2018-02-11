// Copyright (C) 2018 by Sunil

#ifndef HYPER_LOG_LOG_H
#define HYPER_LOG_LOG_H

#include "common/hash.h"

namespace pds {

// HyperLogLog data structure counts the number of distinct elements in a set.
template <typename T>
class HyperLogLog {
 public:
  void Add(T element);
  std::size_t Cardinality();
};

template <typename T>
void HyperLogLog<T>::Add(T element) {
  // add element
}

template <typename T>
std::size_t HyperLogLog<T>::Cardinality() {
  return 0;
}

}  // namespace pds

#endif /* HYPER_LOG_LOG_H */
