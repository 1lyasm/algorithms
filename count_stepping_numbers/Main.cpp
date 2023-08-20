#include <string>
#include <vector>

// #define DEBUG

#ifdef DEBUG
#include <iostream>
#define debug(x) x
#else
#define debug(x)
#endif

#define cnt countSteppingNumbers
#define MOD static_cast<int>(1e9 + 7)

class Solution {
  debug(template <typename T> static void printTable(T Table) {
    for (const auto &R : Table) {
      for (const auto &V : R) {
        std::cout << V << " ";
      }
      std::cout << "\n";
    }
  });

 public:
  static void fillTable(long long **Table, std::size_t RowCnt,
                        std::size_t ColCnt) {
    for (std::size_t I = 0; I < RowCnt; ++I) {
      Table[I][0] = 1;
    }
    for (std::size_t J = 1; J < ColCnt; ++J) {
      Table[0][J] = Table[1][J - 1];
      for (std::size_t I = 1; I < RowCnt - 1; ++I) {
        Table[I][J] = Table[I - 1][J - 1] + Table[I + 1][J - 1];
        Table[I][J] %= MOD;
      }
      Table[RowCnt - 1][J] = Table[RowCnt - 2][J - 1];
    }
  }

  static long long pruneL(const std::string &low, long long **Table) {
    long long PrunedCnt = 0;
    if (low.size() != 1) {
      for (std::size_t I = 1; I < low.size(); ++I) {
        if (low[I] >= low[I - 1] && low[I - 1] != '0') {
          PrunedCnt += Table[static_cast<std::size_t>(low[I - 1] - '0') - 1]
                            [low.size() - I - 1];
        }
        if (low[I] > low[I - 1] + 1) {
          PrunedCnt += Table[static_cast<std::size_t>(low[I - 1] - '0') + 1]
                            [low.size() - I - 1];
        }
        if (low[I] < low[I - 1] - 1 || low[I] == low[I - 1] ||
            low[I] > low[I - 1] + 1) {
          break;
        }
      }
    }
    debug(std::cout << "pruneL: returning: " << PrunedCnt << "\n");
    return PrunedCnt;
  }

  static long long pruneR(const std::string &high, long long **Table) {
    long long PrunedCnt = 0;
    if (high.size() != 1) {
      for (std::size_t I = 1; I < high.size(); ++I) {
        if (high[I] <= high[I - 1] && high[I - 1] != '9') {
          PrunedCnt += Table[static_cast<std::size_t>(high[I - 1] - '0') + 1]
                            [high.size() - I - 1];
        }
        if (high[I] < high[I - 1] - 1) {
          PrunedCnt += Table[static_cast<std::size_t>(high[I - 1] - '0') - 1]
                            [high.size() - I - 1];
        }
        if (high[I] == high[I - 1] || high[I] > high[I - 1] + 1 ||
            high[I] < high[I - 1] - 1) {
          break;
        }
      }
    }
    debug(std::cout << "pruneR: returning: " << PrunedCnt << "\n");
    return PrunedCnt;
  }

  static long long cntRaw(std::string low, std::string high, long long **Table,
                          std::size_t RowCnt) {
    long long Cnt = 0;
    std::size_t LowFirst = static_cast<std::size_t>(low[0] - '0'),
                HighFirst = static_cast<std::size_t>(high[0] - '0');
    if (low.size() == high.size()) {
      for (std::size_t I = LowFirst; I <= HighFirst; ++I) {
        Cnt += Table[I][low.size() - 1];
      }
    } else {
      for (std::size_t I = LowFirst; I < RowCnt; ++I) {
        Cnt += Table[I][low.size() - 1];
      }
      for (std::size_t J = low.size(); J < high.size() - 1; ++J) {
        for (std::size_t I = 1; I < RowCnt; ++I) {
          Cnt += Table[I][J];
        }
      }
      for (std::size_t I = 1; I <= HighFirst; ++I) {
        Cnt += Table[I][high.size() - 1];
      }
    }
    debug(std::cout << "cntRaw: returning: " << Cnt << "\n");
    return Cnt;
  }

  static int cnt(std::string low, std::string high) {
    const unsigned long RowCnt = 10, ColCnt = std::max(low.size(), high.size());
    long long **Table = new long long *[RowCnt];
    for (unsigned long I = 0; I < RowCnt; ++I) {
      Table[I] = new long long[ColCnt];
    }
    fillTable(Table, RowCnt, ColCnt);
    int Res = (cntRaw(low, high, Table, RowCnt) + 2 * MOD - pruneL(low, Table) -
               pruneR(high, Table)) %
              MOD;
    for (unsigned long I = 0; I < RowCnt; ++I) {
      delete[] Table[I];
    }
    delete[] Table;
    debug(std::cout << "cnt: returning: " << Res << "\n");
    return Res;
  }
};
