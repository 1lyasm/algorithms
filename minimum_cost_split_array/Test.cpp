#include <cassert>
#include <iostream>

#include "Main.cpp"

void testMinCost() {
  {
    std::vector<int> nums{1, 2, 1, 2, 1, 3, 3};
    int k = 2;
    assert(Solution::minCost(nums, k) == 8);
  }
  std::cout << "testMinCost: passed\n";
}

int main() { testMinCost(); }
