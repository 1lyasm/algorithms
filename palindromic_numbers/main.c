#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void genPalindromicNumbers(int digitCount) {
	int firstHalf = pow(10, digitCount / 2 - 1), count = 0;
	for (int limit = firstHalf * 10, duplicateCount = 1 + 9 * (digitCount % 2 == 1);
		firstHalf < limit;
		++firstHalf) {
		for (int i = 0, extendedFirstHalf = firstHalf * duplicateCount;
			i < duplicateCount;
			++i, ++count) {
			printf("%d", extendedFirstHalf + i);
			for (int j = firstHalf; j != 0; j /= 10) putchar('0' + j % 10);
			putchar('\n');
		}
	}
	printf("\ncount: %d\n\n", count);
}

int main() {
	size_t bufferSize = pow(2, 17) * sizeof(char);
	printf("\n%llu\n", bufferSize);
	char* buffer = malloc(bufferSize);
	if (!buffer) {
		fputs("\nmalloc failed\n", stdout);
		exit(EXIT_FAILURE);
	}
	printf("\nhey\n");
	if (setvbuf(stdout, buffer, _IOFBF, bufferSize)) {
		fputs("\nsetvbuf failed\n", stdout);
		exit(EXIT_FAILURE);
	}
	genPalindromicNumbers(6);
	genPalindromicNumbers(7);
	fclose(stdout);
	free(buffer);
	return 0;
}
