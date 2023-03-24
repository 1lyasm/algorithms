#include <iostream>
#include "gtest/gtest.h"
#include "dsa.h"

TEST(ReverseInteger, reverse) {
  EXPECT_EQ(ReverseInteger::reverse(123), 321);
  EXPECT_EQ(ReverseInteger::reverse(120), 21);
  EXPECT_EQ(ReverseInteger::reverse(-123), -321);
  EXPECT_EQ(ReverseInteger::reverse(1534236469), 1);
}
