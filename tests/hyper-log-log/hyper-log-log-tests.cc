// Copyright (C) 2018 by Sunil

#include <iostream>

#include "gtest/gtest.h"
#include "hyper-log-log/hyper-log-log.h"

TEST(HyperLogLogTest, Cardinality) {
  pds::HyperLogLog<int> hll(5, std::hash<int>{});
  ASSERT_EQ((std::size_t)0, hll.Count());
}
