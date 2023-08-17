#include <iostream>
#include <string>

class Solution {
 public:
  static int countSubtree(std::string Low, std::string High,
                          bool HasReachedNonZero, bool isFirst) {
    if (Low[0] != '0') {
      HasReachedNonZero = true;
    }
    if (Low[0] < '0' || Low[0] > '9') {
      return 0;
    } else if (Low.size() == 1) {
      return 1;
    }
    std::cout << "Low: \"" << Low << "\", High: \"" << High << "\"\n";
    int Cnt = 0;
    std::string Lower = Low.substr(1, Low.size() - 1), Higher = Lower;
    Lower[0] = Low[0] - 1;
    Higher[0] = Low[0] + 1;
    std::string UpperBound = High.substr(1, High.size() - 1);
    bool countHigher = false, countLower = !isFirst;
    if (isFirst) {
      isFirst = false;
      countLower = Lower[0] >= Low[1];
    }
    if (countLower) {
      Cnt += countSubtree(Lower, UpperBound, HasReachedNonZero, isFirst);
    }
    if (Low[0] == '0' && !HasReachedNonZero) {
      Cnt += countSteppingNumbers(Low.substr(1, Low.size() - 1),
                                  std::string(High.size() - 1, '9'));
    } else {
      if (Low[0] == High[0]) {
        if (Higher[0] >= Low[1] && Higher[0] <= High[1]) {
          countHigher = true;
        }
      } else {
        countHigher = true;
      }
      if (countHigher) {
        Cnt += countSubtree(Higher, UpperBound, HasReachedNonZero, isFirst);
      }
    }
    std::cout << "countSubtree: Cnt: " << Cnt << "\n";
    return Cnt;
  }

  static int countSteppingNumbers(std::string Low, std::string High) {
    int Cnt = 0;
    // if (Low.size() == 1) {
    //   Cnt += 10 - (Low[0] - '0');
    //   Low = "10";
    // }
    Low.insert(0, std::string(High.size() - Low.size(), '0'));
    for (int I = Low[0] - '0'; I <= High[0] - '0'; ++I) {
      if (I == High[0] - '0') {
        Cnt += countSubtree(Low, High, Low[0] != '0', I == Low[0] - '0');
      } else {
        int ZeroCnt = 0;
        for (int i = 0; i < Low.size(); ++i) {
          if (Low[i] != '0') {
            break;
          }
          ++ZeroCnt;
        }
        std::string UpperBound = std::string(ZeroCnt, '0');
        UpperBound.append(std::string(Low.size() - ZeroCnt, '9'));
        Cnt += countSubtree(Low, UpperBound, Low[0] != '0', I == Low[0] - '0');
      }
      ++Low[0];
    }
    std::cout << "countSteppingNumbers: Cnt: " << Cnt << "\n";
    return Cnt;
  }
};
