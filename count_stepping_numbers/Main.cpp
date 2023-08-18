#include <cassert>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#define MODULO (1000000000 + 7)

class Solution {
  [[noreturn]] static void fail(std::string Msg) {
    std::cout << Msg << " failed\n";
    std::exit(EXIT_FAILURE);
  }

 public:
  static int countSteppingNumbers(std::string low, std::string high) {
    unsigned long LowSize = low.size(), HighSize = high.size();
    char* Low = static_cast<char*>(std::malloc((LowSize + 1) * sizeof(char)));
    if (Low == nullptr) {
      fail("countSteppingNumbers: std::malloc");
    }
    Low[LowSize] = 0;
    std::memcpy(Low, low.c_str(), LowSize);
    char* High = static_cast<char*>(std::malloc((HighSize + 1) * sizeof(char)));
    if (High == nullptr) {
      fail("countSteppingNumbers: std::malloc");
    }
    High[HighSize] = 0;
    std::memcpy(High, high.c_str(), HighSize);
    std::unordered_map<std::string, long long> Lookup;
    int Res;
    if (LowSize == HighSize) {
      Res = countSameLen(Low, LowSize, High, HighSize, &Lookup) % MODULO;
    } else {
      unsigned long RBoundSize = HighSize - 1;
      char* RBound =
          static_cast<char*>(std::malloc((RBoundSize + 1) * sizeof(char)));
      if (RBound == nullptr) {
        fail("countSteppingNumbers: std::malloc");
      }
      RBound[RBoundSize] = 0;
      std::memset(RBound, '9', RBoundSize);
      long long Cnt = countSameLen(Low, LowSize, RBound, LowSize, &Lookup);
      unsigned long LBoundSize = HighSize;
      char* LBound =
          static_cast<char*>(std::malloc((LBoundSize + 1) * sizeof(char)));
      if (LBound == nullptr) {
        fail("countSteppingNumbers: std::malloc");
      }
      LBound[LBoundSize] = 0;
      LBound[0] = '1';
      std::memset(LBound + 1, '0', LBoundSize - 1);
      for (unsigned long I = LowSize + 1; I < HighSize; ++I) {
        Cnt += countSameLen(LBound, I, RBound, I, &Lookup);
        Cnt %= MODULO;
      }
      Cnt += countSameLen(LBound, LBoundSize, High, HighSize, &Lookup);
      std::free(LBound);
      std::free(RBound);
      Res = Cnt % MODULO;
    }
    std::free(Low);
    std::free(High);
    // std::printf("countSteppingNumbers: returning: %d\n", Res);
    return Res;
  }

  static int countSameLen(const char* Low, unsigned long LowSize,
                          const char* High, unsigned long HighSize,
                          std::unordered_map<std::string, long long>* Lookup) {
    int Res;
    if (LowSize == 1) {
      Res = High[0] - Low[0] + 1;
    } else {
      char* Lower =
          static_cast<char*>(std::malloc((LowSize + 1) * sizeof(char)));
      if (Lower == nullptr) {
        fail("countSteppingNumbers: std::malloc");
      }
      Lower[LowSize] = 0;
      std::memcpy(Lower, Low, LowSize);
      char* Higher =
          static_cast<char*>(std::malloc((LowSize + 1) * sizeof(char)));
      if (Higher == nullptr) {
        fail("countSteppingNumbers: std::malloc");
      }
      Higher[LowSize] = 0;
      std::memcpy(Higher, Low, LowSize);
      long long Cnt = 0;
      for (char I = Low[0]; I <= High[0]; ++I) {
        Lower[0] = I;
        Lower[1] = I - 1;
        Higher[0] = I;
        Higher[1] = I + 1;
        // std::printf("countSameLen: branching left\n");
        Cnt += countSubtree(Lower, LowSize, 1, Low, LowSize, High, HighSize,
                            Lookup);
        // std::printf("countSameLen: branching right\n");
        Cnt += countSubtree(Higher, LowSize, 1, Low, LowSize, High, HighSize,
                            Lookup);
      }
      std::free(Lower);
      std::free(Higher);
      Res = Cnt % MODULO;
    }
    // std::printf("countSameLen: returning: %d\n", Res);
    return Res;
  }

  static int countSubtree(char* Str, unsigned long StrSize,
                          unsigned long CurIdx, const char* Low,
                          unsigned long LowSize, const char* High,
                          unsigned long HighSize,
                          std::unordered_map<std::string, long long>* Lookup) {
    int BiggerThanLow, Res;
    unsigned long RightSize;
    if (Str[CurIdx] < '0' || Str[CurIdx] > '9' ||
        cmp(Str, High, CurIdx + 1) == 1 ||
        (BiggerThanLow = cmp(Str, Low, CurIdx + 1)) == -1) {
      // std::printf("countSubtree: reached leaf node\n");
      Res = 0;
    } else if ((RightSize = StrSize - CurIdx) == 1) {
      // std::printf("countSubtree: reached leaf node\n");
      Res = 1;
    } else {
      std::string Key;
      Key.reserve(2 * RightSize + 1);
      for (std::string::size_type I = CurIdx; I < CurIdx + RightSize; ++I) {
        Key.push_back(Str[I]);
      }
      Key.push_back('?');
      if (RightSize == HighSize) {
        Key.append(&High[HighSize - RightSize]);
      } else {
        Key.append(std::string(RightSize, '9'));
      }
      auto It = Lookup->find(Key);
      if (It != Lookup->end() && cmp(Str, High, HighSize - RightSize) != 0) {
        Res = (*It).second % MODULO;
      } else {
        Str[CurIdx + 1] = Str[CurIdx] - 1;
        long long Cnt = countSubtree(Str, StrSize, CurIdx + 1, Low, LowSize,
                                     High, HighSize, Lookup) %
                        MODULO;
        Str[CurIdx + 1] += 2;
        Cnt += countSubtree(Str, StrSize, CurIdx + 1, Low, LowSize, High,
                            HighSize, Lookup) %
               MODULO;
        --Str[CurIdx + 1];
        if (BiggerThanLow != 0) {
          (*Lookup)[Key] = Cnt;
        }
        Res = Cnt % MODULO;
      }
    }
    // std::printf("countSubtree: returning: %d\n", Res);
    return Res;
  }

  static int cmp(const char* Str1, const char* Str2, unsigned long Len) {
    for (unsigned long I = 0; I < Len; ++I) {
      if (Str1[I] < Str2[I]) {
        return -1;
      } else if (Str1[I] > Str2[I]) {
        return 1;
      }
    }
    return 0;
  }
};
