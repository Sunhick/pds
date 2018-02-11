// Copyright (C) 2018 by Sunil

#include <iostream>

#include "bloom-filter/bloom-filter.h"
#include "gtest/gtest.h"

// Data is complex type. std::hash doesn't provide a
// override to compute hash for derived types. So provide one.
struct Data {
  std::string name;
  int value;
};

// custom specialization of std::hash can be injected in namespace std
namespace std {
template <>
struct hash<Data> {
  std::size_t operator()(Data const& s) const noexcept {
    std::size_t const h1(std::hash<std::string>{}(s.name));
    std::size_t const h2(std::hash<int>{}(s.value));
    return h1 ^ (h2 << 1);
  }
};
}  // namespace std

TEST(BloomFilterTests, Simple_Present) {
  // test for present
  prob::ds::BloomFilter<int, 100> bf;
  bf.Add(90);
  ASSERT_TRUE(bf.IsMember(90));
}

TEST(BloomFilterTests, Complex_Present_Absent) {
  Data d = {"jack", 121};
  prob::ds::BloomFilter<Data, 100> bf;
  bf.Add(d);

  ASSERT_TRUE(bf.IsMember(d));
  ASSERT_FALSE(bf.IsMember(Data()));
}

TEST(BloomFilterTests, String_Present_Absent) {
  prob::ds::BloomFilter<std::string, 10> bf;
  bf.Add("hello");
  ASSERT_TRUE(bf.IsMember("hello"));
  ASSERT_FALSE(bf.IsMember("Not present"));
}
