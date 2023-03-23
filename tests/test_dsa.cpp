#include "gtest/gtest.h"
#include "dsa.h"

TEST(testname, testtestname) {
  EXPECT_EQ(ReverseInteger::reverse(123), 321);
  EXPECT_EQ(ReverseInteger::reverse(120), 21);
  EXPECT_EQ(ReverseInteger::reverse(-123), -321);
  EXPECT_EQ(ReverseInteger::reverse(1534236469), 0);
}
