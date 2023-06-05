#include <stdio.h>

int search(char *s, int sLen, char *t, int tLen) {
	int i, j, pos = -1;
	for (i = 0; i < sLen && pos < 0; ++i) {
		for (j = 0; j < tLen && s[i + j] == t[j]; ++j);
		if (j == tLen) {
			pos = i;
		}
	}
	return pos;
}

int main() {
	{	char s[] = "ilyas";
		char t[] = "yas";
		printf("\n%d\n", search(s, sizeof(s), t, sizeof(t)));
	}
	{	char s[] = "ilyas";
		char t[] = "yal";
		printf("\n%d\n", search(s, sizeof(s), t, sizeof(t)));
	}
	return 0;
}

