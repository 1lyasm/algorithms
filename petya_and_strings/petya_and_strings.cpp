#include <iostream>
#include <string>

int main() {
  std::string line_1, line_2;
  std::getline(std::cin, line_1);
  std::getline(std::cin, line_2);

  int len = line_1.size();
  int arr_len = 2 * len;
  int *arr = nullptr;
  arr = new int[2 * len];

  for (int i = 0; i < len; i++) {
    arr[i] = (int)(line_1[i]);
    arr[len + i] = (int)(line_2[i]);
  }

  int result = 0;
        __asm {
		; for i : [1, len(str))
		xor ecx, ecx
	L0:

		; check if str_1[i] < 97
		mov eax, ecx
		shl eax, 2
		add eax, arr
		mov ebx, eax
		mov esi, dword ptr[ebx]
		cmp esi, 97
		jb L1

		sub esi, 32

	L1:	; check if str_2[i] < 97
		mov eax, ecx
		add eax, len
		shl eax, 2
		add eax, arr
		mov ebx, eax
		mov edi, dword ptr[ebx]
		cmp edi, 97
		jb L2

		sub edi, 32

	L2:	
		cmp esi, edi
		je L3

		jb L4

		inc result
		jmp L5

	L4: dec result 
		jmp L5
		

	L3:	inc ecx
		cmp ecx, len
		jb L0
	L5: 
	}

        std::cout << result << "\n";

        return 0;
}
