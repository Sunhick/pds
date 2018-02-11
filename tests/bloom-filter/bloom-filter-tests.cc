// Copyright (C) 2018 by Sunil

#include <functional>
#include <iostream>

#include "bloom-filter/bloom-filter.h"
#include "gtest/gtest.h"

namespace {
// Data is complex type. std::hash doesn't provide a
// override to compute hash for derived types. So provide one.
struct Data {
  std::string name;
  int value;
};

struct hashData {
  std::size_t operator()(Data const& s) const noexcept {
    std::size_t const h1(std::hash<std::string>{}(s.name));
    std::size_t const h2(std::hash<int>{}(s.value));
    return h1 ^ (h2 << 1);
  }
};

struct hashDataAlt {
  std::size_t operator()(Data const& s) const noexcept {
    std::size_t const h1(std::hash<std::string>{}(s.name));
    std::size_t const h2(std::hash<int>{}(s.value));
    return h1 ^ h2;
  }
};
}  // namespace

TEST(BloomFilterTests, Simple_Present) {
  // test for present
  pds::BloomFilter<int, 100> bf({std::hash<int>{}});
  bf.Add(90);
  ASSERT_TRUE(bf.IsMember(90));
}

TEST(BloomFilterTests, Complex_Present_Absent) {
  Data d = {"jack", 121};
  pds::BloomFilter<Data, 100> bf({hashData{}, hashDataAlt{}});
  bf.Add(d);

  ASSERT_TRUE(bf.IsMember(d));
  ASSERT_FALSE(bf.IsMember(Data()));
  ASSERT_FALSE(bf.IsMember({"sunil", 121}));
}

TEST(BloomFilterTests, String_Present_Absent) {
  pds::BloomFilter<std::string, 10> bf({std::hash<std::string>{}});
  bf.Add("hello");
  ASSERT_TRUE(bf.IsMember("hello"));
  ASSERT_FALSE(bf.IsMember("Not present"));
  ASSERT_FALSE(bf.IsMember("Hello"));
  ASSERT_FALSE(bf.IsMember("helo"));
}
