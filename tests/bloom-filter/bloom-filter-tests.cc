// Copyright (C) 2018 by Sunil

#include "bloom-filter/bloom-filter.h"

#include "gtest/gtest.h"

TEST(BloomFilterTests, Present) {
  // test for present
  prob::ds::BloomFilter<int> bf;
  bf.Add(90);
  ASSERT_TRUE(bf.IsMember(90));
}

TEST(BloomFilterTests, Absent) {
  // test for absent
}
