#include <cassert>
#include <chrono>
#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

// #define DEBUG

#define MODULO (1000000000 + 7)

class Solution {
 public:
#ifdef DEBUG
  template <typename K, typename V>
  static void printMap(std::unordered_map<K, V>* Map) {
    for (const std::pair<K, V>& Kv : *Map) {
      std::cout << "Key: [" << Kv.first << "], Value: [" << Kv.second << "]\n";
    }
  }
#endif

  static void fillLookupFast(std::vector<std::vector<long long>>* Lookup,
                             unsigned long MaxGapCnt) {
    for (unsigned long I = 0; I <= 9; ++I) {
      long long Val = 0;
      if (I > 0) {
        ++Val;
      }
      if (I < 9) {
        ++Val;
      }
      (*Lookup)[I][1] = Val;
    }
    for (unsigned long I = 2; I <= MaxGapCnt; ++I) {
      for (unsigned long J = 0; J <= 9; ++J) {
        long long Val = 0;
        if (J >= 1) {
          Val += (*Lookup)[J - 1][I - 1];
          Val %= MODULO;
        }
        if (J <= 8) {
          Val += (*Lookup)[J + 1][I - 1];
          Val %= MODULO;
        }
        (*Lookup)[J][I] = Val;
      }
    }
#ifdef DEBUG
    std::printf("fillLookupFast: Lookup: \n");
    printMap<int, long long>(Lookup);
#endif
  }

  static int cmp(const char* Str1, const char* Str2,
                 std::string::size_type Len) {
    for (std::string::size_type I = 0; I < Len; ++I) {
      if (Str1[I] < Str2[I]) {
        return -1;
      } else if (Str1[I] > Str2[I]) {
        return 1;
      }
    }
    return 0;
  }

  static int countSubtree(std::string& Str, std::string::size_type CurIdx,
                          const std::string& Low, const std::string& High,
                          std::unordered_map<std::string, long long>* Lookup) {
    int BiggerThanLow;
    std::string::size_type RightSize;
    if (Str[CurIdx] < '0' || Str[CurIdx] > '9' ||
        cmp(Str.c_str(), High.c_str(), CurIdx + 1) == 1 ||
        (BiggerThanLow = cmp(Str.c_str(), Low.c_str(), CurIdx + 1)) == -1) {
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
    if (It != Lookup->end() &&
        cmp(Str.c_str(), High.c_str(), High.size() - RightSize) != 0) {
      return It->second % MODULO;
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

  static int countSameLen(const std::string& low, const std::string& high,
                          std::unordered_map<std::string, long long>* Lookup) {
    if (low.size() == 1) {
      return high[0] - low[0] + 1;
    }
    long long Cnt = 0;
    std::string Lower = low, Higher = low;
    for (char I = low[0]; I <= high[0]; ++I) {
      Lower[0] = I;
      Higher[0] = I;
      Lower[1] = I - 1;
      Higher[1] = I + 1;
      if (!Lower.empty()) {
        Cnt += countSubtree(Lower, 1, low, high, Lookup) +
               countSubtree(Higher, 1, low, high, Lookup);
      } else {
        Cnt += 1;
      }
    }
    return Cnt % MODULO;
  }

  static int countSameLenFast(unsigned long Len,
                              std::vector<std::vector<long long>>* Lookup) {
    long long Cnt = 0;
    for (unsigned long I = 1; I <= 9; ++I) {
      Cnt += (*Lookup)[I][Len - 1];
      Cnt %= MODULO;
    }
    int Res = static_cast<int>(Cnt);
#ifdef DEBUG
    std::printf("countSameLenFast: returning %d\n", Res);
#endif
    return Res;
  }

  static int countSteppingNumbers(std::string low, std::string high) {
    std::unordered_map<std::string, long long> Lookup;
    std::vector<std::vector<long long>> LookupFast(10,
                                                   std::vector<long long>(100));
    if (low.size() == high.size()) {
      return countSameLen(low, high, &Lookup) % MODULO;
    }
    long long Cnt = 0;
    Cnt += countSameLen(low, std::string(low.size(), '9'), &Lookup);
    for (std::string::size_type I = low.size() + 1; I < high.size(); ++I) {
      if (I == low.size() + 1) {
        fillLookupFast(&LookupFast, high.size() - 1);
      }
      Cnt += countSameLenFast(I, &LookupFast);
      Cnt %= MODULO;
    }
    std::string LBound = "1";
    LBound.append(high.size() - 1, '0');
    Cnt += countSameLen(LBound, high, &Lookup);
    return Cnt % MODULO;
  }
};
