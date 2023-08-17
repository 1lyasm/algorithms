#include <cassert>
#include <chrono>

#include "Main.cpp"

static void testCountSteppingNumbers() {
  // assert(Solution::countSteppingNumbers("100", "999") == 32);
  // assert(Solution::countSteppingNumbers("1", "11") == 10);
  // assert(Solution::countSteppingNumbers("90", "101") == 2);
  // assert(Solution::countSteppingNumbers("1", "10000000") == 881);
  // assert(Solution::countSteppingNumbers("96", "322") == 9);
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
  testCountSteppingNumbers();
  return 0;
}
