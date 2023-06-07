#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void genCombinations(char *s, int n, int k, int *indices, int *combinationCount) {
	int i;
	int incrementedIndex = k - 1;
	++*combinationCount;
	for (i = 0; i < k; ++i) {
		printf("%c", s[indices[i]]);
	}
	printf("\n");
	while (++indices[incrementedIndex] == n && incrementedIndex != 0) {
		indices[incrementedIndex--] = 0;
	}
	if (indices[0] == n) {
		return;
	}
	genCombinations(s, n, k, indices, combinationCount);
}

int main() {
	char s[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g'}; 
	int n = sizeof(s);
	int k = 4;
	int *indices = malloc(k * sizeof(int));
	int combinationCount = 0;
	clock_t start;
	memset(indices, 0, k * sizeof(int));
	if (indices == 0) {
		printf("\nmalloc failed\n");
		exit(EXIT_FAILURE);
	}
	start = clock();
	genCombinations(s, n, k, indices, &combinationCount);
	printf("\n\ngeneration duration: %ld\n", clock() - start);
	printf("\n\ncombination count: %d\n", combinationCount);
	free(indices);
	return 0;
}
