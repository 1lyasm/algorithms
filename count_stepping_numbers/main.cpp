#include <cassert>
#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define MODULO (1000000000 + 7)

class Solution {
 public:
  static int countSteppingNumbers(std::string low, std::string high) {
    std::unordered_map<std::string, long long> Lookup;
    if (low.size() == high.size()) {
      return static_cast<int>(countSameLen(low, high, &Lookup));
    }
    long long Cnt = 0;
    Cnt += countSameLen(low, std::string(low.size(), '9'), &Lookup);
    for (std::string::size_type I = low.size() + 1; I < high.size(); ++I) {
      std::string LBound = "1";
      LBound.append(I - 1, '0');
      Cnt += countSameLen(LBound, std::string(I, '9'), &Lookup);
    }
    std::string LBound = "1";
    LBound.append(high.size() - 1, '0');
    Cnt += countSameLen(LBound, high, &Lookup);
    return static_cast<int>(Cnt % MODULO);
  }

  static void testCountSteppingNumbers() {
    assert(countSteppingNumbers("100", "999") == 32);
    assert(countSteppingNumbers("1", "11") == 10);
    assert(countSteppingNumbers("90", "101") == 2);
    assert(countSteppingNumbers("1", "10000000") == 881);
    assert(countSteppingNumbers("96", "322") == 9);
    assert(countSteppingNumbers("129", "439") == 10);
    auto Begin = std::chrono::system_clock::now();
    assert(countSteppingNumbers(
               "1",
               "999999999999999999999999999999999999999999999999999999999999999"
               "9999999999999999999999999999999999999") == 125046265);
    auto End = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> Diff = End - Begin;
    std::cout << "Duration: " << Diff.count() << "\n";
  }

  static int countSameLen(const std::string& low, const std::string& high,
                          std::unordered_map<std::string, long long>* Lookup) {
    long long Cnt = 0;
    std::string Str = low;
    for (int I = Str[0] - '0'; I <= high[0] - '0'; ++I) {
      std::string Prefix = "";
      Prefix = Str[0];
      std::string Lower = Str.substr(1, Str.size() - 1),
                  Higher = Str.substr(1, Str.size() - 1);
      Lower[0] = Str[0] - 1;
      Higher[0] = Str[0] + 1;
      //   std::cout << "Prefix: " << Prefix << ", Lower: " << Lower
      //             << ", Higher: " << Higher << ", low: " << low
      //             << ", high: " << high << "\n";
      if (!Lower.empty()) {
        if (Lower[0] >= '0') {
          Cnt += countSubtree(Prefix, Lower, low, high, Lookup);
        }
        if (Higher[0] <= '9') {
          Cnt += countSubtree(Prefix, Higher, low, high, Lookup);
        }
      } else {
        Cnt += 1;
      }
      Str[0] = static_cast<char>(I + 1 + '0');
    }
    // std::cout << "Cnt: " << Cnt << "\n";
    return Cnt % MODULO;
  }

  static void testCountSameLen() {
    std::unordered_map<std::string, long long> Lookup;
    assert(countSameLen("33000000", "37000000", &Lookup) == 61);
    assert(countSameLen("3000000", "7000000", &Lookup) == 234);
    assert(countSameLen("1000000", "8999999", &Lookup) == 404);
    assert(countSameLen("1", "9", &Lookup) == 9);
    assert(countSameLen("100", "999", &Lookup) == 32);
  }

  static int countSubtree(std::string& Prefix, std::string& Str,
                          const std::string& Low, const std::string& High,
                          std::unordered_map<std::string, long long>* Lookup) {
    // std::cout << "Prefix: " << Prefix << ", Str: " << Str << ", Low: " << Low
    //           << ", High: " << High << "\n";
    std::string FullStr = Prefix;
    FullStr.push_back(Str[0]);
    if (cmp(FullStr, High.substr(0, FullStr.size())) == 1 ||
        cmp(FullStr, Low.substr(0, FullStr.size())) == -1) {
      return 0;
    } else if (Str.size() == 1) {
      return 1;
    }
    std::string Key = Str;
    Key.append("?");
    if (Str.size() == High.size()) {
      Key.append(High.substr(High.size() - Str.size(), Str.size()));
    } else {
      Key.append(std::string(Str.size(), '9'));
    }
    auto It = Lookup->find(Key);
    if (It != Lookup->end() &&
        Prefix != High.substr(0, High.size() - Str.size())) {
      //   long long Taken = (*It).second;
      //   std::cout << "Taking " << Key << " from Lookup: " << Taken << "\n";
      return (*It).second % MODULO;
    }
    std::string NewPrefix = Prefix;
    NewPrefix.push_back(Str[0]);
    long long Res = 0;
    if (Str[0] > '0') {
      std::string Lower = Str.substr(1, Str.size() - 1);
      Lower[0] = Str[0] - 1;
      Res += countSubtree(NewPrefix, Lower, Low, High, Lookup);
    }
    if (Str[0] < '9') {
      std::string Higher = Str.substr(1, Str.size() - 1);
      Higher[0] = Str[0] + 1;
      Res += countSubtree(NewPrefix, Higher, Low, High, Lookup);
    }
    if (FullStr[0] != Low[0] && FullStr != Low.substr(0, FullStr.size())) {
      (*Lookup)[Key] = Res;
    }
    // std::cout << "Wrote " << Key << " to Lookup: " << Res << "\n";
    return Res % MODULO;
  }

  static void testCountSubtree() {
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "10", Str = Low, High = "19";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 2);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "100", Str = Low, High = "200";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 3);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "2023", Str = Low, High = "2999";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 7);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "100000", Str = Low, High = "199999";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 20);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "100000", Str = Low, High = "120000";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 6);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "120000", Str = Low, High = "199999";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 14);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "33000000", Str = Low, High = "37000000";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 61);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string Prefix = "", Low = "106", Str = Low, High = "121";
      assert(countSubtree(Prefix, Str, Low, High, &Lookup) == 1);
    }
  }

  static int cmp(const std::string& Str1, const std::string& Str2) {
    for (std::string::size_type I = 0; I < Str1.size(); ++I) {
      if (Str1[I] < Str2[I]) {
        return -1;
      } else if (Str1[I] > Str2[I]) {
        return 1;
      }
    }
    return 0;
  }

  static void testCmp() {
    assert(cmp("123", "124") == -1);
    assert(cmp("124", "123") == 1);
    assert(cmp("123", "123") == 0);
  }
};

int main() {
  Solution::testCmp();
  Solution::testCountSubtree();
  Solution::testCountSameLen();
  Solution::testCountSteppingNumbers();
  return 0;
}
