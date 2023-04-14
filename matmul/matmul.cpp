#include <iostream>

void matmul(int *a, int n_a, int m_a, int *b, int n_b, int m_b, int *c) {
  /*
   *	for all rows row_i in matrix a
   *		for all columns col_j in matrix b
   *			c[i, j] = 0
   *			for k : [0, len(row_i))
   *				c[i, j] += a[i, k] * b[k, j]
   */
  __asm {
		; dl: i
		xor dl, dl

		; bl: j
	L2:	xor bl, bl
	L3:	; c[i, j] = 0
		xor eax, eax
		mov al, dl
		mov ecx, m_b
		mul cl
		add al, bl
		shl ax, 2
		add eax, c
		mov esi, eax
		mov dword ptr [esi], 0

		; edi: k
		xor edi, edi
	L4:
		xor eax, eax
		mov al, dl
		mov dh, bl
		mov ebx, m_a
		shl ebx, 8
		mov bl, dh
		mul bh
		add eax, edi
		shl eax, 2
		add eax, a
		xchg eax, esi
;int 3
		mov ecx, dword ptr[esi]
		xchg eax, esi
		push esi

		mov eax, edi
		mov dh, bl
		mov ebx, m_b
		shl ebx, 8
		mov bl, dh
		mul bh
		add al, bl
		shl al, 2
		add eax, b
		mov esi, eax
;int 3
		mov eax, dword ptr[esi]

		mul cl
		pop esi
		add dword ptr [esi], eax

		inc edi
		cmp edi, m_a
		jb L4

		inc bl
		and ebx, 00ffh
		cmp ebx, m_b
		jb L3

		inc dl
		and edx, 00ffh
		cmp edx, n_a
		jb L2


	L1: ; exit
  }
}

int main() {
  int n_a = 2, m_a = 3;
  int n_b = 3, m_b = 4;
  int *a = nullptr;
  int *b = nullptr;
  int *c = nullptr;
  a = new int[n_a * m_a];
  b = new int[n_b * m_b];
  c = new int[n_a * m_b];

  for (int i = 0; i < n_a * m_a; i++) {
    a[i] = i;
  }

  for (int j = 0; j < n_b * m_b; j++) {
    b[j] = n_b * m_b - j;
  }

  // for (int i = 0; i < n_a * m_a; i++) {
  // 	std::cout << a[i] << " ";
  // }

  // for (int j = 0; j < n_b * m_b; j++) {
  // 	std::cout << b[j] << " ";
  // }

  matmul(a, n_a, m_a, b, n_b, m_b, c);

  for (int i = 0; i < n_a; i++) {
    for (int j = 0; j < m_b; j++) {
      std::cout << c[m_b * i + j] << " ";
    }
    std::cout << "\n";
  }
  return 0;
}
