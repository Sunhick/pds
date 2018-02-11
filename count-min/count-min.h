// Copyright (C) 2018 by Sunil

#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <vector>

#include "common/hash.h"

namespace prob {
namespace ds {

auto CountMinWidth = [](float epsilon) { return (int)std::ceil(2 / epsilon); };

auto CountMinDepth = [](float delta) {
  return (int)std::ceil(-std::log(1 - delta) / std::log(2));
};

// Probabilisitic data structure for keeping track of the count of items
// in the set in a space efficient manner. It's probabalisitic because it
// gives you only a rough count of the element in the set.
template <typename T>
class CountMinSketch {
 private:
  const int width;
  const int depth;
  std::vector<std::vector<std::size_t>> table;
  std::vector<hash<T>> hashes;

 public:
  CountMinSketch(int width, std::initializer_list<hash<T>> hashes);
  void Add(T element);
  std::size_t RoughCount(T element);
};

template <typename T>
CountMinSketch<T>::CountMinSketch(int width,
                                  std::initializer_list<hash<T>> hashes)
    : width(width), depth(hashes.size()), hashes(hashes) {
  if ((std::size_t)depth > hashes.size())
    std::runtime_error(
        "Too few hash functions passed! Should be atleast the size of depth");
  table.reserve(depth);
  for (auto i = 0; i < depth; i++) {
    table.push_back(std::vector<std::size_t>(width));
    for (auto j = 0; j < width; j++) {
      table[i][j] = 0;
    }
  }
}

template <typename T>
std::size_t CountMinSketch<T>::RoughCount(T element) {
  std::vector<std::size_t> values(depth);
  for (auto i = 0; i < depth; i++) {
    auto& hash = hashes[i];
    auto index = hash(element);
    auto row = index % depth;
    auto col = index % width;
    values[i] = table[row][col];
  }

  auto it = std::min_element(values.begin(), values.end());
  return it != values.end() ? *it : -1;
}

template <typename T>
void CountMinSketch<T>::Add(T element) {
  for (auto i = 0; i < depth; i++) {
    auto& hash = hashes[i];
    auto index = hash(element);
    auto row = index % depth;
    auto col = index % width;
    table[row][col]++;
  }
}

}  // namespace ds
}  // namespace prob

#endif /* COUNT_MIN_SKETCH_H */
