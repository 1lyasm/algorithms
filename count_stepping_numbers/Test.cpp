#include <cassert>
#include <chrono>
#include <iostream>

#include "Main.cpp"

static void pass(std::string FuncName) {
  std::cout << FuncName << ": passed\n";
}

// static void testPruneL() {
//   auto Table = Solution::makeTable(MOD, 100);
//   assert(Solution::pruneL("100", Table) == 0);
//   assert(Solution::pruneL("101", Table) == 0);
//   assert(Solution::pruneL("102", Table) == 1);
//   assert(Solution::pruneL("103", Table) == 1);
//   assert(Solution::pruneL("109", Table) == 1);
//   assert(Solution::pruneL("110", Table) == 1);
//   assert(Solution::pruneL("111", Table) == 1);
//   assert(Solution::pruneL("112", Table) == 1);
//   assert(Solution::pruneL("113", Table) == 1);
//   assert(Solution::pruneL("114", Table) == 1);
//   assert(Solution::pruneL("119", Table) == 1);
//   assert(Solution::pruneL("120", Table) == 1);
//   assert(Solution::pruneL("121", Table) == 1);
//   assert(Solution::pruneL("122", Table) == 2);
//   assert(Solution::pruneL("123", Table) == 2);
//   assert(Solution::pruneL("124", Table) == 3);
//   assert(Solution::pruneL("125", Table) == 3);
//   assert(Solution::pruneL("129", Table) == 3);
//   assert(Solution::pruneL("130", Table) == 3);
//   assert(Solution::pruneL("198", Table) == 3);
//   assert(Solution::pruneL("10", Table) == 0);
//   assert(Solution::pruneL("11", Table) == 1);
//   assert(Solution::pruneL("5", Table) == 0);
//   assert(Solution::pruneL("1", Table) == 0);
//   assert(Solution::pruneL("9", Table) == 0);
//   assert(Solution::pruneL("12", Table) == 1);
//   assert(Solution::pruneL("13", Table) == 2);
//   assert(Solution::pruneL("14", Table) == 2);
//   assert(Solution::pruneL("19", Table) == 2);
//   assert(Solution::pruneL("201", Table) == 0);
//   assert(Solution::pruneL("210", Table) == 0);
//   assert(Solution::pruneL("211", Table) == 1);
//   assert(Solution::pruneL("212", Table) == 1);
//   assert(Solution::pruneL("213", Table) == 2);
//   assert(Solution::pruneL("215", Table) == 2);
//   assert(Solution::pruneL("220", Table) == 2);
//   assert(Solution::pruneL("221", Table) == 2);
//   assert(Solution::pruneL("222", Table) == 2);
//   assert(Solution::pruneL("230", Table) == 2);
//   assert(Solution::pruneL("232", Table) == 2);
//   assert(Solution::pruneL("233", Table) == 3);
//   assert(Solution::pruneL("234", Table) == 3);
//   assert(Solution::pruneL("235", Table) == 4);
//   assert(Solution::pruneL("100000", Table) == 0);
//   assert(Solution::pruneL("987654321", Table) == 0);
//   pass("testPruneL");
// }

// static void testPruneR() {
//   auto Table = Solution::makeTable(MOD, 100);
//   assert(Solution::pruneR("100", Table) == 3);
//   assert(Solution::pruneR("101", Table) == 2);
//   assert(Solution::pruneR("102", Table) == 2);
//   assert(Solution::pruneR("103", Table) == 2);
//   assert(Solution::pruneR("109", Table) == 2);
//   assert(Solution::pruneR("110", Table) == 2);
//   assert(Solution::pruneR("111", Table) == 2);
//   assert(Solution::pruneR("112", Table) == 2);
//   assert(Solution::pruneR("113", Table) == 2);
//   assert(Solution::pruneR("114", Table) == 2);
//   assert(Solution::pruneR("119", Table) == 2);
//   assert(Solution::pruneR("120", Table) == 2);
//   assert(Solution::pruneR("121", Table) == 1);
//   assert(Solution::pruneR("122", Table) == 1);
//   assert(Solution::pruneR("123", Table) == 0);
//   assert(Solution::pruneR("124", Table) == 0);
//   assert(Solution::pruneR("125", Table) == 0);
//   assert(Solution::pruneR("129", Table) == 0);
//   assert(Solution::pruneR("130", Table) == 0);
//   assert(Solution::pruneR("198", Table) == 0);
//   assert(Solution::pruneR("10", Table) == 1);
//   assert(Solution::pruneR("11", Table) == 1);
//   assert(Solution::pruneR("5", Table) == 0);
//   assert(Solution::pruneR("1", Table) == 0);
//   assert(Solution::pruneR("9", Table) == 0);
//   assert(Solution::pruneR("12", Table) == 0);
//   assert(Solution::pruneR("13", Table) == 0);
//   assert(Solution::pruneR("14", Table) == 0);
//   assert(Solution::pruneR("19", Table) == 0);
//   assert(Solution::pruneR("201", Table) == 4);
//   assert(Solution::pruneR("210", Table) == 3);
//   assert(Solution::pruneR("211", Table) == 3);
//   assert(Solution::pruneR("212", Table) == 2);
//   assert(Solution::pruneR("213", Table) == 2);
//   assert(Solution::pruneR("215", Table) == 2);
//   assert(Solution::pruneR("220", Table) == 2);
//   assert(Solution::pruneR("221", Table) == 2);
//   assert(Solution::pruneR("222", Table) == 2);
//   assert(Solution::pruneR("230", Table) == 2);
//   assert(Solution::pruneR("232", Table) == 1);
//   assert(Solution::pruneR("233", Table) == 1);
//   assert(Solution::pruneR("234", Table) == 0);
//   assert(Solution::pruneR("235", Table) == 0);
//   assert(Solution::pruneR("99999", Table) == 0);
//   assert(Solution::pruneR("123456789", Table) == 0);
//   assert(Solution::pruneR("200", Table) == 4);
//   pass("testPruneR");
// }

// static void testCntRaw() {
//   auto Table = Solution::makeTable(MOD, 100);
//   assert(Solution::cntRaw("100", "999", Table) == 32);
//   assert(Solution::cntRaw("1", "9", Table) == 9);
//   assert(Solution::cntRaw("1", "99", Table) == 26);
//   assert(Solution::cntRaw("1", "999", Table) == 58);
//   assert(Solution::cntRaw("30", "99", Table) == 13);
//   assert(Solution::cntRaw("30", "79", Table) == 10);
//   assert(Solution::cntRaw("1", "49", Table) == 17);
//   assert(Solution::cntRaw(
//              "1",
//              "999999999999999999999999999999999999999999999999999999999999999"
//              "9999999999999999999999999999999999999",
//              Table) == 125046265);
//   pass("testCntRaw");
// }

static void testCnt() {
  assert(Solution::cnt("100", "999") == 32);
  assert(Solution::cnt("1", "11") == 10);
  assert(Solution::cnt("90", "101") == 2);
  assert(Solution::cnt("1", "10000000") == 881);
  assert(Solution::cnt("96", "322") == 9);
  assert(Solution::cnt("129", "439") == 10);
  assert(Solution::cnt("2", "40") == 14);
  assert(Solution::cnt("99", "200") == 3);
  assert(Solution::cnt("149", "160") == 0);
  assert(Solution::cnt("1", "1") == 1);
  assert(Solution::cnt("9999999999999999999999999999999999999999999999999999999"
                       "99999999999999999999999999999999999",
                       "9999999999999999999999999999999999999999999999999999999"
                       "999999999999999999999999999999999999") == 705298990);
  assert(Solution::cnt(
             "1",
             "999999999999999999999999999999999999999999999999999999999999999"
             "9999999999999999999999999999999999999") == 125046265);
  assert(Solution::cnt("4777151832123893594603912184102647750886581638454062882"
                       "3553703379973973374976021909186485563776056",
                       "5267144055329453476845598490077325117111896155350045515"
                       "152421482060338688466687508314627537686720152") ==
         683315344);
  pass("testCnt");
}

static void profCnt() {
  int RunCnt = 500;
  double Dur = 0;
  for (int I = 0; I < RunCnt; ++I) {
    auto Begin = std::chrono::system_clock::now();
    assert(Solution::cnt(
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
  // testPruneL();
  // testPruneR();
  // testCntRaw();
  testCnt();
  profCnt();
  return 0;
}
