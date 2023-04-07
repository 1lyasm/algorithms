#include <iostream>
#include <string>
#include <vector>

void take_inp(int* mtx, int n_row, int n_col) {
	std::string dummy;
	for (int i = 0; i < n_row; i++) {
		std::getline(std::cin, dummy);
		for (int j = 0; j < n_row; j++){
			mtx[n_col * i + j] = dummy[2 * j] - 48;
		}
	}
	return;
}


int solve(int* mtx, int n_row, int n_col) {
	/*
	* first find one
	* (2 - row) + (2 - col), where (row, col) is position of one
	*
	*/
	int result = 0;
	__asm {
		mov edx, mtx
		xor ecx, ecx
		L2:
		mov edi, 0
		cmp dword ptr [edx], 1
		je L1
		mov edi, 4
		cmp dword ptr[edx + 4], 1
		je L1
		mov edi, 8
		cmp dword ptr[edx + 8], 1
		je L1
		mov edi, 12
		cmp dword ptr[edx + 12], 1
		je L1
		mov edi, 16
		cmp dword ptr[edx + 16], 1
		je L1
		jmp L4
	L1:
		mov eax, edx
		add eax, edi
		sub eax, mtx
		shr eax, 2
		mov ebx, n_col
		div bl

		mov cl, 2
		sub cl, al
		cmp cl, 0
		jge L5
		neg cl
	L5: mov bl, 2
		sub bl, ah
		cmp bl, 0
		jge L6
		neg bl
	L6: 
		add cl, bl
		and ecx, 00ffh
		mov result, ecx
		jmp L3
	L4:
		mov eax, n_col
		shl eax, 2
		add edx, eax
		inc ecx
		cmp ecx, n_row
		jbe L2
	L3:
	}
	return result;
}

int main()
{
	// TODO: TAKE ABSOLUTE VALUES OF COORDINATE DIFFERENCES


	int n_row = 5, n_col = 5;

	int* mtx = nullptr;
	mtx = new int[n_row * n_col];

	take_inp(mtx, n_row, n_col);

	int result = solve(mtx, n_row, n_col);
	std::cout << result << "\n";

	return 0;
}

