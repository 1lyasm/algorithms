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
    std::size_t InitSize = 10000;
    std::unordered_map<std::string, long long> Lookup(InitSize);
    if (low.size() == high.size()) {
      return static_cast<int>(countSameLen(low, high, &Lookup));
    }
    long long Cnt = 0;
    Cnt += countSameLen(low, std::string(low.size(), '9'), &Lookup);
    for (std::string::size_type I = low.size() + 1; I < high.size(); ++I) {
      std::string LBound = "1";
      LBound.append(I - 1, '0');
      Cnt += countSameLen(LBound, std::string(I, '9'), &Lookup);
      if (Cnt >= MODULO) {
        Cnt %= MODULO;
      }
    }
    std::string LBound = "1";
    LBound.append(high.size() - 1, '0');
    Cnt += countSameLen(LBound, high, &Lookup);
    if (Cnt >= MODULO) {
      Cnt %= MODULO;
    }
    return static_cast<int>(Cnt);
  }

  static int countSameLen(const std::string& low, const std::string& high,
                          std::unordered_map<std::string, long long>* Lookup) {
    if (low.size() == 1) {
      return high[0] - low[0] + 1;
    }
    long long Cnt = 0;
    std::string Str = low;
    for (int I = Str[0] - '0'; I <= high[0] - '0'; ++I) {
      std::string Lower = Str, Higher = Str;
      Lower[1] = Str[0] - 1;
      Higher[1] = Str[0] + 1;
      if (!Lower.empty()) {
        Cnt += countSubtree(Lower, 1, low, high, Lookup) +
               countSubtree(Higher, 1, low, high, Lookup);
      } else {
        Cnt += 1;
      }
      Str[0] = static_cast<char>(I + 1 + '0');
    }
    return Cnt % MODULO;
  }

  static int countSubtree(std::string& Str, std::string::size_type CurIdx,
                          const std::string& Low, const std::string& High,
                          std::unordered_map<std::string, long long>* Lookup) {
    int BiggerThanLow;
    std::string::size_type RightSize;
    if (Str[CurIdx] < '0' || Str[CurIdx] > '9' ||
        cmp(&Str, &High, CurIdx + 1) == 1 ||
        (BiggerThanLow = cmp(&Str, &Low, CurIdx + 1)) == -1) {
      return 0;
    } else if ((RightSize = Str.size() - CurIdx) == 1) {
      return 1;
    }
    std::string Key = Str.substr(CurIdx, RightSize);
    Key.append("?");
    if (RightSize == High.size()) {
      Key.append(High.substr(High.size() - RightSize, RightSize));
    } else {
      Key.append(std::string(RightSize, '9'));
    }
    auto It = Lookup->find(Key);
    if (It != Lookup->end() && cmp(&Str, &High, High.size() - RightSize) != 0) {
      return (*It).second % MODULO;
    }
    std::string Lower = Str, Higher = Str;
    Lower[CurIdx + 1] = Str[CurIdx] - 1;
    Higher[CurIdx + 1] = Str[CurIdx] + 1;
    long long Res =
        countSubtree(Lower, CurIdx + 1, Low, High, Lookup) % MODULO +
        countSubtree(Higher, CurIdx + 1, Low, High, Lookup) % MODULO;
    if (BiggerThanLow != 0) {
      (*Lookup)[Key] = Res;
    }
    return Res % MODULO;
  }

  static int cmp(const std::string* Str1, const std::string* Str2, std::string::size_type Len) {
    for (std::string::size_type I = 0; I < Len; ++I) {
      if ((*Str1)[I] < (*Str2)[I]) {
        return -1;
      } else if ((*Str1)[I] > (*Str2)[I]) {
        return 1;
      }
    }
    return 0;
  }
};
