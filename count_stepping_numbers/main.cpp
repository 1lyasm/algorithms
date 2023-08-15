#include <cassert>
#include <iostream>
#include <string>

class Solution {
 public:
  static int countSteppingNumbers(std::string low, std::string high) {
    long long int Cnt = 0;
    for (int i = low[0] - '0'; i <= high[0] - '0'; ++i) {
    //   std::string Substr = low.substr(1, low.size() - 1);
    //   std::string Lower = std::string(Substr), Higher = std::string(Substr);
    //   Lower[0] = Lower[0] - 1;
    //   Higher[0] = Higher[0] + 1;
    //   Cnt += countSubtree(Lower, high) + countSubtree(Higher, high);
      low[0] = static_cast<char>(i + 1 + '0');
    }
    return 0;
  }

  static void testCountSteppingNumbers() {
    assert(countSteppingNumbers("1", "11") == 10);
    assert(countSteppingNumbers("90", "101") == 2);
  }

  static int countSubtree(std::string Prefix, std::string &Str, std::string &High) {
    std::string FullStr = std::string(Prefix);
    FullStr.append(Str);
    if ((Str.size() > 0 && (Str[0] < '0' || Str[0] > '9')) ||
        cmp(FullStr, High) == 1) {
      return 0;
    } else if (Str.size() == 1) {
      return 1;
    }
    std::string Substr = Str.substr(1, Str.size() - 1);
    std::string Lower = std::string(Substr), Higher = std::string(Substr);
    std::string NewPrefix = std::string(Prefix);
    NewPrefix.push_back(Str[0]);
    Lower[0] = Str[0] - 1;
    Higher[0] = Str[0] + 1;
    int Res = countSubtree(NewPrefix, Lower, High) + countSubtree(NewPrefix, Higher, High);
    return Res;
  }

  static void testCountSubtree() {
    std::string Str = std::string("100"), High = std::string("200"),    
        Prefix = std::string();
    int Res = countSubtree(Prefix, Str, High);
    std::cout << "Res: " << Res << "\n";
    assert(Res == 3);
    Str = std::string("2023");
    High = std::string("2999");
    Res = countSubtree(Prefix, Str, High);
    std::cout << "Res: " << Res << "\n";
    assert(Res == 7);
    Str = std::string("100000");
    High = std::string("199999");
    Res = countSubtree(Prefix, Str, High);
    std::cout << "Res: " << Res << "\n";
    assert(Res == 20);
    Str = std::string("100000");
    High = std::string("120000");
    Res = countSubtree(Prefix, Str, High);
    std::cout << "Res: " << Res << "\n";
    assert(Res == 6);
  }

  static int seekNonStepping(std::string &Str) {
    for (std::string::size_type i = 0; i < Str.size() - 1; ++i) {
      if (Str[i] - '0' != Str[i + 1] - '0' - 1 &&
          Str[i] - '0' != Str[i + 1] - '0' + 1) {
        return static_cast<int>(i + 1);
      }
    }
    return -1;
  }

  static int cmp(std::string &Str1, std::string &Str2) {
    std::cout << "cmp called with: " << Str1 << " and " << Str2 << "\n";
    if (Str1.size() < Str2.size()) {
        return -1;
    } else if (Str1.size() > Str2.size()) {
        return 1;
    }
    for (std::string::size_type i = 0; i < Str1.size(); ++i) {
      if (Str1[i] < Str2[i]) {
        return -1;
      } else if (Str1[i] > Str2[i]) {
        return 1;
      }
    }
    return 0;
  }

  static void testCmp() {
    std::string Str1 = std::string("123"), Str2 = std::string("124");
    assert(cmp(Str1, Str2) == -1);
    assert(cmp(Str2, Str1) == 1);
    Str2 = std::string("123");
    assert(cmp(Str1, Str2) == 0);
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

  static int seekNonZero(const std::string &Str) {
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

  static void leftPad(std::string &Str, unsigned long Cnt) {
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
  Solution::testCmp();
  Solution::testCountSubtree();
  //   Solution::testCountSteppingNumbers();
}
