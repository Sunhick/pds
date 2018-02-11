// Copyright (C) 2018 by Sunil

#include <iostream>

#include "hyper-log-log/hyper-log-log.h"
#include "gtest/gtest.h"

TEST(HyperLogLogTest, Cardinality) {
  prob::ds::HyperLogLog<int> hll;      
  ASSERT_EQ((std::size_t)0, hll.Cardinality());
}
