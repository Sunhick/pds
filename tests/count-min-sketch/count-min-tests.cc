// Copyright (C) 2018 by Sunil

#include <iostream>

#include "count-min/count-min.h"
#include "gtest/gtest.h"

TEST(CountMinTests, Counter) {
  auto width = prob::ds::CountMinWidth(0.1);  // 20
  auto depth = prob::ds::CountMinDepth(0.9);  // 4

  ASSERT_EQ(width, 20);
  ASSERT_EQ(depth, 4);

  prob::ds::CountMinSketch<int> cms(
      width,
      {
        std::hash<int>{},
        [](int e) { return (std::hash<int>{}(e) ^ 9) * 18; },
        [](int e) { return (std::hash<int>{}(e) ^ 7) * 71; },
        [](int e) { return (std::hash<int>{}(e) ^ 1) * 83; }
      });
  cms.Add(10);
  cms.Add(10);
  cms.Add(20);

  // assert with some tolerance
  ASSERT_EQ((std::size_t)2, cms.RoughCount(10));
  ASSERT_EQ((std::size_t)0, cms.RoughCount(99));
  
  // 90 & 10 collides. use an elegant hash function.
  // ASSERT_EQ((std::size_t)0, cms.RoughCount(90));
}
