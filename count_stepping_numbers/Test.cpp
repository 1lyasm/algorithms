#include <cassert>
#include <chrono>

#include "Main.cpp"

static void testCmp() {
  std::string Str1 = "123", Str2 = "124";
  assert(Solution::cmp(&Str1, &Str2, 3) == -1);
  Str1 = "124";
  Str2 = "123";
  assert(Solution::cmp(&Str1, &Str2, 3) == 1);
  Str1 = "123";
  Str2 = "123";
  assert(Solution::cmp(&Str1, &Str2, 3) == 0);
}

static void testCountSubtree() {
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "10", High = "19";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 2);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "100", High = "200";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 3);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "2023", High = "2999";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 7);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "100000", High = "199999";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 20);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "100000", High = "120000";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 6);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "120000", High = "199999";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 14);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "33000000", High = "37000000";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 61);
  }
  {
    std::unordered_map<std::string, long long> Lookup;
    std::string Low = "106", High = "121";
    assert(Solution::countSubtree(&Low, 0, Low, High, &Lookup) == 1);
  }
}

static void testCountSameLen() {
  std::unordered_map<std::string, long long> Lookup;
  assert(Solution::countSameLen("33000000", "37000000", &Lookup) == 61);
  assert(Solution::countSameLen("3000000", "7000000", &Lookup) == 234);
  assert(Solution::countSameLen("1000000", "8999999", &Lookup) == 404);
  assert(Solution::countSameLen("1", "9", &Lookup) == 9);
  assert(Solution::countSameLen("100", "999", &Lookup) == 32);
}

static void testCountSteppingNumbers() {
  assert(Solution::countSteppingNumbers("100", "999") == 32);
  assert(Solution::countSteppingNumbers("1", "11") == 10);
  assert(Solution::countSteppingNumbers("90", "101") == 2);
  assert(Solution::countSteppingNumbers("1", "10000000") == 881);
  assert(Solution::countSteppingNumbers("96", "322") == 9);
  assert(Solution::countSteppingNumbers("129", "439") == 10);
  auto Begin = std::chrono::system_clock::now();
  assert(Solution::countSteppingNumbers(
             "1",
             "999999999999999999999999999999999999999999999999999999999999999"
             "9999999999999999999999999999999999999") == 125046265);
  auto End = std::chrono::system_clock::now();
  std::chrono::duration<double, std::milli> Diff = End - Begin;
  std::cout << "Duration: " << Diff.count() << "\n";
}

int main() {
  // testCmp();
  // testCountSubtree();
  // testCountSameLen();
  testCountSteppingNumbers();
  return 0;
}
