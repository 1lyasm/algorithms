#include <cassert>
#include <iostream>
#include <string>

class Solution {
 public:
  static int countSteppingNumbers(std::string low, std::string high) {
    if (low.length() < high.length()) {
      leftPad(low, high.length() - low.length());
    }
    int NonZeroIdx = seekNonZero(low);
    int NonSteppingIdx = seekNonStepping(low);
    return 0;
  }

  static void testCountSteppingNumbers() {
    assert(countSteppingNumbers("1", "11") == 10);
    assert(countSteppingNumbers("90", "101") == 2);
  }

  static int seekNonStepping(std::string& Str) {
    for (int i = 0; i < Str.size() - 1; ++i) {
      if (Str[i] - '0' != Str[i + 1] - '0' - 1 &&
          Str[i] - '0' != Str[i + 1] - '0' + 1) {
        std::cout << "res: " << i + 1 << "\n";
        return i + 1;
      }
    }
    std::cout << "res: " << -1 << "\n";
    return -1;
  }

  static void testSeekNonStepping() {
    std::string Str = std::string("102");
    assert(seekNonStepping(Str) == 2);
    Str = std::string("1013");
    assert(seekNonStepping(Str) == 3);
    Str = std::string("19");
    assert(seekNonStepping(Str) == 1);
    Str = std::string("9890");
    assert(seekNonStepping(Str) == 3);
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

  static void leftPad(std::string& Str, unsigned long Cnt) {
    for (unsigned long I = 0; I < Cnt; ++I) {
      Str.insert(0, "0");
    }
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
};

int main() {
  Solution::testLeftPad();
  Solution::testSeekNonZero();
  Solution::testSeekNonStepping();
  Solution::testCountSteppingNumbers();
}
