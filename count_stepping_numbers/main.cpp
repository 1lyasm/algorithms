#include <cassert>
#include <iostream>
#include <string>

class Solution {
  static void leftPad(std::string& Str, unsigned long Cnt) {
    for (unsigned long I = 0; I < Cnt; ++I) {
      Str.insert(0, "0");
    }
  }

  static int seekNonZero(const std::string& Str) {
    std::string::size_type I;
    for (I = 0; I < Str.size(); ++I) {
      if (Str[I] != '0') {
        break;
      }
    }
    if (I != Str.size()) {
      return static_cast<int>(I);
    } else {
      return -1;
    }
  }

 public:
  static int countSteppingNumbers(std::string low, std::string high) {
    if (low.length() < high.length()) {
      leftPad(low, high.length() - low.length());
    }
    int NonZeroIdx = seekNonZero(low);
    return 0;
  }

  static void testCountSteppingNumbers() {
    assert(countSteppingNumbers("1", "11") == 10);
    assert(countSteppingNumbers("90", "101") == 2);
  }

  static void testLeftPad() {
    std::string Str = std::string("1");
    leftPad(Str, 2);
    assert(Str == "001");
    leftPad(Str, 0);
    assert(Str == "001");
    leftPad(Str, 1);
    assert(Str == "0001");
  }

  static void testSeekNonZero() {
    std::string Str = std::string("01");
    assert(seekNonZero(Str) == 1);
    Str = std::string("001");
    assert(seekNonZero(Str) == 2);
    Str = std::string("000");
    assert(seekNonZero(Str) == -1);
    Str = std::string("10");
    assert(seekNonZero(Str) == 0);
  }
};

int main() {
  Solution::testLeftPad();
  Solution::testSeekNonZero();
  // Solution::testCountSteppingNumbers();
}
