#include <iostream>
#include <string>
#include <vector>

void take_inp(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    std::cin >> arr[i];
  }
  return;
}

void print_inp(int *arr, int n) {
  for (int i = 0; i < n; i++) {
    std::cout << arr[i] << " ";
  }
  return;
}

int solve(int *arr, int n, int k) {
  /*
   * go to k-th element
   * zero?
   * if yes, count number of zeros to the left of that element, and return (k -
   * count) if not, count number of elements to the right that have equal value,
   * and return (k + count)
   */
  int result = k;
  __asm {
		mov esi, -1
		; zero ?
		mov eax, k
		dec eax
		shl eax, 2
		add eax, arr
		mov ebx, eax
		mov eax, dword ptr[ebx]
		cmp eax, 0
		je L5
	L2:	
		inc esi
		add ebx, 4
		cmp eax, dword ptr[ebx]
		je L2
		add result, esi
		jmp L4
	L5:
		inc esi
		sub ebx, 4
		cmp dword ptr[ebx], 0
		je L5
		inc esi
		sub result, esi
	L4:
  }
  return result;
}

int main() {
  int n, k;
  std::cin >> n >> k;
  std::cin.ignore();

  int *arr = nullptr;
  arr = new int[n];

  take_inp(arr, n);

  int result = solve(arr, n, k);
  std::cout << result << "\n";

  return 0;
}
