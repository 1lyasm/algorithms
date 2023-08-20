#include <iostream>
#include <string>
#include <vector>

#define DEBUG
#define cnt countSteppingNumbers
#define MOD static_cast<int>(1e9 + 7)

class Solution {
#ifdef DEBUG
  template <typename T>
  static void printTable(T Table) {
    for (const auto &R : Table) {
      for (const auto &V : R) {
        std::cout << V << " ";
      }
      std::cout << "\n";
    }
  }
#endif
 public:
  static std::vector<std::vector<long long>> makeTable(int Mod) {
    std::size_t RowCnt = 10, ColCnt = 100;
    std::vector<std::vector<long long>> Table(RowCnt,
                                              std::vector<long long>(ColCnt));
    for (std::size_t I = 0; I < RowCnt; ++I) {
      Table[I][0] = 1;
    }
    for (std::size_t J = 1; J < ColCnt; ++J) {
      Table[0][J] = Table[1][J - 1];
      for (std::size_t I = 1; I < RowCnt - 1; ++I) {
        Table[I][J] = Table[I - 1][J - 1] + Table[I + 1][J - 1];
        Table[I][J] %= Mod;
      }
      Table[RowCnt - 1][J] = Table[RowCnt - 2][J - 1];
    }
    return Table;
  }

  static long long pruneLeft(const std::string &low,
                             const std::vector<std::vector<long long>> &Table) {
    if (low.size() == 1) {
      return low[0] - '0' - 1;
    }
    long long PrunedCnt = 0;
    for (std::size_t I = 1; I < low.size(); ++I) {
      if (low[I] >= low[I - 1] && low[I - 1] != '0') {
        PrunedCnt += Table[low[I - 1] - '0' - 1][low.size() - I - 1];
      }
      if (low[I] > low[I - 1] + 1) {
        PrunedCnt += Table[low[I - 1] - '0' + 1][low.size() - I - 1];
      }
      if (low[I] < low[I - 1] - 1 || low[I] == low[I - 1]) {
        break;
      }
    }
    return PrunedCnt;
  }

  static int cnt(std::string low, std::string high) {
    auto Table = makeTable(MOD);
    long long PrunedCnt = pruneLeft(low, Table);
    return 0;
  }
};
