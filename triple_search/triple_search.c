#include <stdio.h>

int main() {
	int a = 1, b, c;
	int found = 0;
	while (a < 1000 && !found) {
		b = 1;
		while (b < 1000 && !found) {
			c = 1;
			while (c < 1000 && !found) {
				if (a + b + c == 1000 && a * a + b * b == c * c) {
					printf("\n(%d, %d, %d)\n", a, b, c);
					found = 1;
				}
				else {
					++c;
				}
			}
			if (!found) {
				++b;
			}
		}
		if (!found) {
			++a;
		}
	}	
	if (!found) {
		printf("\nnot found\n");
	}
	return 0;
}
