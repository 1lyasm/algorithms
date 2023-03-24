#include <iostream>
#include "gtest/gtest.h"
#include "dsa.h"

TEST(ReverseInteger, reverse) {
  EXPECT_EQ(ReverseInteger::reverse(123), 321);
  EXPECT_EQ(ReverseInteger::reverse(120), 21);
  EXPECT_EQ(ReverseInteger::reverse(-123), -321);
  EXPECT_EQ(ReverseInteger::reverse(1534236469), 0);
}

TEST(Power4, power_4) {
  std::vector<int> output = Power4::power_4();
  std::vector<int> expected = {95800, 217519, 414560, 422481};
  for (int i = 0; i < 4; ++i) {
    EXPECT_EQ(output[i], expected[i]);
  }
}
