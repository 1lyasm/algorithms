#include <iostream>
#include <string>
#include <vector>

void take_inp(int *mtx, int n_row) {
  std::vector<std::string> vec;
  std::string dummy;
  for (int i = 0; i < n_row; i++) {
    std::getline(std::cin, dummy);
    vec.push_back(dummy);
  }

  int mtx_idx = 0;
  for (auto x : vec) {
    mtx[mtx_idx] = x[0] - 48;
    mtx[mtx_idx + 1] = x[2] - 48;
    mtx[mtx_idx + 2] = x[4] - 48;
    mtx_idx += 3;
  }
  return;
}

int solve(int *mtx, int n_row) {
  int result = 0;
  __asm {

	; bx: i
		xor bx, bx
			; cx: j
	L2:			xor cx, cx
				mov ax, bx
				shl ax, 1
				add ax, bx
				mov dx, ax
				; edi: n.of ones
				xor edi, edi
				; find linear offset: 3 * i + j
	L3:			
				mov ax, dx
				add ax, cx
				and eax, 0ffffh
				shl eax, 2
				add eax, mtx
				mov esi, eax
				mov eax, dword ptr[esi]
				cmp eax, 0
				je L1
				inc edi
	L1:  		inc cx
				cmp cx, 3
				jb L3
				jmp L5

	L5:			cmp edi, 2
				jb L7
				inc result
	L7:
				inc bx
				mov ax, bx
				and eax, 0ffffh
				cmp eax, n_row
				jb L2
  }
  return result;
}

int main() {
  int n_col = 3;
  int n_row;
  std::cin >> n_row;
  std::cin.ignore();

  int mtx_size = n_col * n_row;
  int *mtx = nullptr;
  mtx = new int[mtx_size];

  take_inp(mtx, n_row);
  int result = solve(mtx, n_row);
  std::cout << result << "\n";

  return 0;
}
