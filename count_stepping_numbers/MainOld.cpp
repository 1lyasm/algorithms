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
    std::string *LowPtr = &low, *HighPtr = &high;
    if (low.size() == high.size()) {
      return static_cast<int>(countSameLen(LowPtr, HighPtr, &Lookup));
    }
    long long Cnt = 0;
    Cnt += countSameLen(LowPtr, new std::string(low.size(), '9'), &Lookup);
    for (std::string::size_type I = low.size() + 1; I < high.size(); ++I) {
      std::string LBound = "1";
      LBound.append(I - 1, '0');
      Cnt += countSameLen(&LBound, new std::string(I, '9'), &Lookup);
      if (Cnt >= MODULO) {
        Cnt %= MODULO;
      }
    }
    std::string LBound = "1";
    LBound.append(high.size() - 1, '0');
    Cnt += countSameLen(&LBound, HighPtr, &Lookup);
    if (Cnt >= MODULO) {
      Cnt %= MODULO;
    }
    return static_cast<int>(Cnt);
  }

  static void testCountSteppingNumbers() {
    assert(countSteppingNumbers("100", "999") == 32);
    assert(countSteppingNumbers("1", "11") == 10);
    assert(countSteppingNumbers("90", "101") == 2);
    assert(countSteppingNumbers("1", "10000000") == 881);
    assert(countSteppingNumbers("96", "322") == 9);
    assert(countSteppingNumbers("129", "439") == 10);
    // auto Begin = std::chrono::system_clock::now();
    // assert(countSteppingNumbers(
    //            "1",
    //            "999999999999999999999999999999999999999999999999999999999999999"
    //            "9999999999999999999999999999999999999") == 125046265);
    // auto End = std::chrono::system_clock::now();
    // std::chrono::duration<double, std::milli> Diff = End - Begin;
    // std::cout << "Duration: " << Diff.count() << "\n";
  }

  static long long countSameLen(
      std::string* Low, std::string* High,
      std::unordered_map<std::string, long long>* Lookup) {
    long long Cnt = 0;
    std::string Str = *Low;
    for (int I = Str[0] - '0'; I <= (*High)[0] - '0'; ++I) {
      std::string Prefix = std::string(1, Str[0]);
      std::string Lower = Str.substr(1, Str.size() - 1),
                  Higher = Str.substr(1, Str.size() - 1);
      Lower[0] = Str[0] - 1;
      Higher[0] = Str[0] + 1;
      if (!Lower.empty()) {
        if (Lower[0] >= '0') {
          Cnt += countSubtree(&Prefix, &Lower, Low, High, Lookup);
          if (Cnt >= MODULO) {
            Cnt %= MODULO;
          }
        }
        if (Higher[0] <= '9') {
          Cnt += countSubtree(&Prefix, &Higher, Low, High, Lookup);
          if (Cnt >= MODULO) {
            Cnt %= MODULO;
          }
        }
      } else {
        Cnt += 1;
        if (Cnt >= MODULO) {
          Cnt %= MODULO;
        }
      }
      Str[0] = static_cast<char>(I + 1 + '0');
    }
    return Cnt;
  }

  static void testCountSameLen() {
    std::unordered_map<std::string, long long> Lookup;
    assert(countSameLen(new std::string("33000000"),
                        new std::string("37000000"), &Lookup) == 61);
    assert(countSameLen(new std::string("3000000"), new std::string("7000000"),
                        &Lookup) == 234);
    assert(countSameLen(new std::string("1000000"), new std::string("8999999"),
                        &Lookup) == 404);
    long long Cnt =
        countSameLen(new std::string("1"), new std::string("9"), &Lookup);
    std::cout << "Cnt: " << Cnt << "\n";
    assert(Cnt == 9);
    assert(countSameLen(new std::string("100"), new std::string("999"),
                        &Lookup) == 32);
  }

  static long long countSubtree(
      std::string* Prefix, std::string* Str, std::string* Low,
      std::string* High, std::unordered_map<std::string, long long>* Lookup) {
    std::string FullStr = *Prefix;
    FullStr.push_back((*Str)[0]);
    if (cmp(&FullStr, High, FullStr.size()) == 1 ||
        cmp(&FullStr, Low, FullStr.size()) == -1) {
      return 0;
    } else if ((*Str).size() == 1) {
      return 1;
    }
    std::string Key = *Str;
    Key.append("?");
    if (Str->size() == High->size()) {
      Key.append(High->substr(High->size() - Str->size(), Str->size()));
    } else {
      Key.append(std::string(Str->size(), '9'));
    }
    auto It = Lookup->find(Key);
    if (It != Lookup->end() &&
        cmp(Prefix, High, High->size() - Str->size() != 0)) {
      long long Taken = (*It).second;
      //   std::cout << "Taking " << Key << " from Lookup: " << Taken << "\n";
      return Taken;
    }
    long long Res = 0;
    if ((*Str)[0] > '0') {
      std::string Lower = Str->substr(1, Str->size() - 1);
      Lower[0] = (*Str)[0] - 1;
      Res += countSubtree(&FullStr, &Lower, Low, High, Lookup);
      if (Res >= MODULO) {
        Res %= MODULO;
      }
    }
    if ((*Str)[0] < '9') {
      std::string Higher = Str->substr(1, Str->size() - 1);
      Higher[0] = (*Str)[0] + 1;
      Res += countSubtree(&FullStr, &Higher, Low, High, Lookup);
      if (Res >= MODULO) {
        Res %= MODULO;
      }
    }
    if (cmp(&FullStr, Low, FullStr.size()) != 0) {
      (*Lookup)[Key] = Res;
    }
    // std::cout << "Wrote " << Key << " to Lookup: " << Res << "\n";
    return Res;
  }

  static void testCountSubtree() {
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "10", Str = Low,
                  High = "19";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 2);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "100", Str = Low,
                  High = "200";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 3);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "2023", Str = Low,
                  High = "2999";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 7);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "100000", Str = Low,
                  High = "199999";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 20);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "100000", Str = Low,
                  High = "120000";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 6);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "120000", Str = Low,
                  High = "199999";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 14);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "33000000", Str = Low,
                  High = "37000000";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 61);
    }
    {
      std::unordered_map<std::string, long long> Lookup;
      std::string *Prefix = new std::string(), Low = "106", Str = Low,
                  High = "121";
      assert(countSubtree(Prefix, &Str, &Low, &High, &Lookup) == 1);
    }
  }
  static int cmp(std::string* Str1, std::string* Str2,
                 std::string::size_type Size) {
    for (std::string::size_type I = 0; I < Size; ++I) {
      if ((*Str1)[I] < (*Str2)[I]) {
        return -1;
      } else if ((*Str1)[I] > (*Str2)[I]) {
        return 1;
      }
    }
    return 0;
  }

  static void testCmp() {
    assert(cmp(new std::string("123"), new std::string("124"), 3) == -1);
    assert(cmp(new std::string("124"), new std::string("123"), 3) == 1);
    assert(cmp(new std::string("123"), new std::string("123"), 3) == 0);
  }
};

int main() {
  Solution::testCmp();
  Solution::testCountSubtree();
  Solution::testCountSameLen();
  Solution::testCountSteppingNumbers();
  return 0;
}
