// Copyright (C) 2018 by Sunil

#include <iostream>

#include "count-min/count-min.h"
#include "gtest/gtest.h"

TEST(CountMinTests, Counter) {
  auto width = prob::ds::CountMinWidth(0.1);
  auto depth = prob::ds::CountMinDepth(0.9);
  std::cout << "width: " << width << std::endl;
  std::cout << "depth: " << depth << std::endl;
}
