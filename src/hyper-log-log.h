// Copyright (C) 2018 by Sunil

#ifndef HYPER_LOG_LOG_H
#define HYPER_LOG_LOG_H

#include <cmath>
#include <vector>

#include "hash.h"

namespace pds {

// HyperLogLog data structure counts the number of distinct elements in a set.
template <typename T>
class HyperLogLog {
 private:
  const std::size_t reglimit = sizeof(std::size_t) * 8;
  const hash<T> func;
  const int regBits;
  const int bucketBits;
  std::vector<std::size_t> registers;

 public:
  HyperLogLog(int regBits, hash<T> func);
  void Add(T element);
  std::size_t Count();
  void Merge();
};

template <typename T>
HyperLogLog<T>::HyperLogLog(int regBits, hash<T> func)
    : func(func), regBits(regBits), bucketBits(std::log2(regBits)) {
  registers.reserve(regBits);
  for (auto i = 0; i < regBits; i++) registers[i] = 0;
}

template <typename T>
void HyperLogLog<T>::Add(T element) {
  auto h = func(element);
  auto index = (h >> (reglimit - bucketBits)) + 1;
  auto pos = clz(h << bucketBits);
  registers[index] = std::max(registers[index], pos);
}

template <typename T>
std::size_t HyperLogLog<T>::Count() {
  // TODO: Yet to be implemented.
  return 0;
}

template <typename T>
void HyperLogLog<T>::Merge() {}

namespace {

std::size_t clz(std::size_t num) {
  std::size_t zcount = 0;
  const std::size_t bits = sizeof(num) * 8;
  for (std::size_t i = 1; i < bits; i++) {
    if (num < 0) break;
    zcount++;
    num <<= 1;
  }
  return zcount;
}

}  // Namespace

}  // namespace pds

#endif /* HYPER_LOG_LOG_H */
