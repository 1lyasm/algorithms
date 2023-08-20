#include <cassert>
#include <chrono>

#include "Main.cpp"

static void pass(std::string FuncName) {
  std::cout << FuncName << ": passed\n";
}

static void testPruneLeft() {
  auto Table = Solution::makeTable(MOD);
  assert(Solution::pruneLeft("100", Table) == 0);
  assert(Solution::pruneLeft("101", Table) == 0);
  assert(Solution::pruneLeft("102", Table) == 1);
  assert(Solution::pruneLeft("103", Table) == 1);
  assert(Solution::pruneLeft("109", Table) == 1);
  assert(Solution::pruneLeft("110", Table) == 1);
  assert(Solution::pruneLeft("111", Table) == 1);
  assert(Solution::pruneLeft("112", Table) == 1);
  assert(Solution::pruneLeft("113", Table) == 1);
  assert(Solution::pruneLeft("114", Table) == 1);
  assert(Solution::pruneLeft("119", Table) == 1);
  assert(Solution::pruneLeft("120", Table) == 1);
  assert(Solution::pruneLeft("121", Table) == 1);
  assert(Solution::pruneLeft("122", Table) == 2);
  assert(Solution::pruneLeft("123", Table) == 2);
  assert(Solution::pruneLeft("124", Table) == 3);
  assert(Solution::pruneLeft("125", Table) == 3);
  assert(Solution::pruneLeft("129", Table) == 3);
  assert(Solution::pruneLeft("130", Table) == 3);
  assert(Solution::pruneLeft("198", Table) == 3);
  assert(Solution::pruneLeft("10", Table) == 0);
  assert(Solution::pruneLeft("11", Table) == 1);
  assert(Solution::pruneLeft("5", Table) == 4);
  assert(Solution::pruneLeft("1", Table) == 0);
  assert(Solution::pruneLeft("9", Table) == 8);
  assert(Solution::pruneLeft("12", Table) == 1);
  assert(Solution::pruneLeft("13", Table) == 2);
  assert(Solution::pruneLeft("14", Table) == 2);
  assert(Solution::pruneLeft("19", Table) == 2);
  assert(Solution::pruneLeft("201", Table) == 0);
  assert(Solution::pruneLeft("210", Table) == 0);
  assert(Solution::pruneLeft("211", Table) == 1);
  assert(Solution::pruneLeft("212", Table) == 1);
  assert(Solution::pruneLeft("213", Table) == 2);
  assert(Solution::pruneLeft("215", Table) == 2);
  assert(Solution::pruneLeft("220", Table) == 2);
  assert(Solution::pruneLeft("221", Table) == 2);
  assert(Solution::pruneLeft("222", Table) == 2);
  assert(Solution::pruneLeft("230", Table) == 2);
  assert(Solution::pruneLeft("232", Table) == 2);
  assert(Solution::pruneLeft("233", Table) == 3);
  assert(Solution::pruneLeft("234", Table) == 3);
  assert(Solution::pruneLeft("235", Table) == 4);
  assert(Solution::pruneLeft("100000", Table) == 0);
  assert(Solution::pruneLeft("987654321", Table) == 0);
  pass("testPruneLeft");
}

static void testCnt() {
  assert(Solution::countSteppingNumbers("100", "999") == 32);
  assert(Solution::countSteppingNumbers("1", "11") == 10);
  assert(Solution::countSteppingNumbers("90", "101") == 2);
  assert(Solution::countSteppingNumbers("1", "10000000") == 881);
  assert(Solution::countSteppingNumbers("96", "322") == 9);
  assert(Solution::countSteppingNumbers("129", "439") == 10);
  assert(Solution::countSteppingNumbers(
             "1",
             "999999999999999999999999999999999999999999999999999999999999999"
             "9999999999999999999999999999999999999") == 125046265);
  pass("testCnt");
}

static void profCnt() {
  int RunCnt = 500;
  double Dur = 0;
  for (int I = 0; I < RunCnt; ++I) {
    auto Begin = std::chrono::system_clock::now();
    assert(Solution::countSteppingNumbers(
               "1",
               "999999999999999999999999999999999999999999999999999999999999999"
               "9999999999999999999999999999999999999") == 125046265);
    auto End = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> Diff = End - Begin;
    Dur += Diff.count();
  }
  double AvgDur = Dur / RunCnt;
  std::printf("profCnt: duration: %f\n", AvgDur);
}

int main() {
  testPruneLeft();
  testCnt();
  profCnt();
  return 0;
}
