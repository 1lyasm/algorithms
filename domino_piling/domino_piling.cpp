#include <iostream>
#include <string>
#include <vector>

int solve(int n, int k) {
  /*
   * divide n x k by 2
   */
  int result;
  __asm {
		mov eax, n
		mov ebx, k
		mul ebx
		shr eax, 1
		mov result, eax
  }
  return result;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::cin.ignore();

  int result = solve(n, k);
  std::cout << result << "\n";

  return 0;
}
