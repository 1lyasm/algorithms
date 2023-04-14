#include <iostream>

const int mtx_size = 16;

void MatrixMul(int *result, int *a, int *b) {
        __asm {

	; outer loop, i = cl
		xor cl, cl
		; inner loop, j = ch
			xor ch, ch
			; c[i, j] : = 0
			mov al, cl
			mov bl, 4
			mul bl
			add al, ch
			and eax, 00ffh
			add eax, result
			mov ebx, eax
			push ebx
			mov dword ptr [ebx], 0
			; for k : = 0 to 3 do, dl = k
				xor dl, dl
				; c[i, j] : = c[i, j] + a[i, k] * b[k, j];
				mov al, cl
				mov bl, 4
				mul bl
				add al, dl
				and eax, 00ffh
				add eax, a
				mov ebx, eax
				mov eax, dword ptr[ebx]

				mov al, dl
				mov bl, 4
				mul bl
				add al, ch
				 eax, 00ffh
				add eax, a
				mov ebx, eax
				mov bl, dl
				mul dword ptr[ebx]
				pop edx
				add eax, dword ptr [edx]
				push edx
				mov dword ptr[edx], eax
	}
        return;
}

int main() {
        int a[mtx_size] = {1, 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 8};
        int b[mtx_size] = {1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 5, 4, 3, 2, 1};
        int result[mtx_size];

        MatrixMul(result, a, b);

        for (int i = 0; i < 4; i++) {
          for (int j = 0; j < 4; j++) {
            std::cout << result[i * 4 + j] << " "
                      << "\n";
          }
          std::cout << "\n";
        }

        return 0;
}
