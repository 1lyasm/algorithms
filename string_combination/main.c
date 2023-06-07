#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void genCombinations(char *s, int n, int k) {
	int combinationCount = 0;
	int *indices = malloc(k * sizeof(int));
	if (indices == 0) {
		printf("\nmalloc failed\n");
		exit(EXIT_FAILURE);
	}
	memset(indices, 0, k * sizeof(int));
	while (indices[0] != n) {
		int i;
		int incrementedIndex;
		for (i = 0; i < k; ++i)
			putchar(s[indices[i]]);
		putchar('\n');
		for (incrementedIndex = k - 1; ++indices[incrementedIndex] == n && 
				incrementedIndex != 0;) {
			indices[incrementedIndex--] = 0;
		}
		++combinationCount;
	}
	free(indices);
	printf("\n\ncombination count: %d\n", combinationCount);
}

int main() {
	char s[] = "abcdefg"; 
	int n = 7;
	int k = 4;
	clock_t start;
	int bufferSize = 16384;
	char *buffer = malloc(bufferSize * sizeof(char));
	if (buffer == 0) {
		fputs("\nmalloc failed\n", stdout);
		exit(EXIT_FAILURE);
	}
	if (setvbuf(stdout, buffer, _IOFBF, bufferSize) != 0) {
		fputs("\nsetvbuf failed\n", stdout);
		exit(EXIT_FAILURE);
	}
	start = clock();
	genCombinations(s, n, k);
	printf("\n\ngeneration duration: %ld\n", clock() - start);
	fclose(stdout);
	free(buffer);
	return 0;
}
