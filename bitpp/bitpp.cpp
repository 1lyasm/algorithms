#include <iostream>
#include <string>
#include <vector>

void take_inp(int* arr, int n, int n_char) {
    std::string dummy;
	for (int i = 0; i < n; i++) {
        std::getline(std::cin, dummy);
		arr[n_char * i] = dummy[0];
		arr[n_char * i + 1] = dummy[1];
		arr[n_char * i + 2] = dummy[2];
	} 
	return;
}


int solve(int* arr, int n) {
	/*
	* for i : [1, n]
	*	if there is 43 (+), increment result
	*	if there is 45 (-), decrement result
	* 
	*/
	int result = 0;
	__asm {
		xor edx, edx
		xor ecx, ecx
	L3:	mov ebx, edx
		shl ebx, 2
		add ebx, arr
		mov eax, dword ptr[ebx]
		cmp eax, 43
		je L1
		cmp eax, 45
		je L2
		mov eax, dword ptr[ebx + 4]
		cmp eax, 43
		je L1
		cmp eax, 45
		je L2
		mov eax, dword ptr[ebx + 8]
		cmp eax, 43
		je L1
		cmp eax, 45
		je L2

		jmp L4
	L1:
		inc result
		jmp L4
	L2 :
		dec result
	L4:	add edx, 3
		inc ecx
		cmp ecx, n
		jb L3
	}
	return result;
}

int main()
{
	int n_char = 3;
	int n;
	std::cin >> n;
	std::cin.ignore();

	int* arr = nullptr;
	arr = new int[n * n_char];

	take_inp(arr, n, n_char);

	int result = solve(arr, n);
	std::cout << result << "\n";

	return 0;
}

