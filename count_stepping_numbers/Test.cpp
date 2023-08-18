#include <cassert>
#include <chrono>

#include "Main.cpp"

static void testCmp() {
  std::string Str1 = "123", Str2 = "124";
  assert(Solution::cmp(Str1.c_str(), Str2.c_str(), 3) == -1);
  Str1 = "124";
  Str2 = "123";
  assert(Solution::cmp(Str1.c_str(), Str2.c_str(), 3) == 1);
  Str1 = "123";
  Str2 = "123";
  assert(Solution::cmp(Str1.c_str(), Str2.c_str(), 3) == 0);
}

// static void testCountSubtree() {
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "10", High = "19";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 2);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "100", High = "200";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 3);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "2023", High = "2999";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 7);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "100000", High = "199999";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 20);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "100000", High = "120000";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 6);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "120000", High = "199999";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 14);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "33000000", High = "37000000";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 61);
//   }
//   {
//     std::unordered_map<std::string, long long> Lookup;
//     std::string Low = "106", High = "121";
//     assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 1);
//   }
// }

static void testCountSameLen() {
  std::unordered_map<std::string, long long> Lookup;
  std::string Low = "33000000", High = "37000000";
  assert(Solution::countSameLen(Low.c_str(), Low.size(), High.c_str(),
                                High.size(), &Lookup) == 61);
  Low = "3000000";
  High = "7000000";
  assert(Solution::countSameLen(Low.c_str(), Low.size(), High.c_str(),
                                High.size(), &Lookup) == 234);
  Low = "1000000";
  High = "8999999";
  assert(Solution::countSameLen(Low.c_str(), Low.size(), High.c_str(),
                                High.size(), &Lookup) == 404);
  Low = "1";
  High = "9";
  assert(Solution::countSameLen(Low.c_str(), Low.size(), High.c_str(),
                                High.size(), &Lookup) == 9);
  Low = "100";
  High = "999";
  assert(Solution::countSameLen(Low.c_str(), Low.size(), High.c_str(),
                                High.size(), &Lookup) == 32);
}

static void testCountSteppingNumbers() {
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
}

static void profCountSteppingNumbers() {
  int RunCnt = 100;
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
  std::printf("profCountSteppingNumbers: duration: %f\n", AvgDur);
}

int main() {
  // testCmp();
  // testCountSubtree();
  // testCountSameLen();
  testCountSteppingNumbers();
  profCountSteppingNumbers();
  return 0;
}
