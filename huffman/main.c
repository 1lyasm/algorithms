#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fillFreqs(int **freqTable, int tableSize, char *fileName) {
	FILE *f = fopen(fileName, "r");
	int current;
	int i;
	if (f == 0) {
		printf("\nfopen failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < tableSize; ++i) {
		freqTable[i][0] = i;
	}
	while ((current = fgetc(f)) != EOF) {
		++freqTable[current][1];
	}
	if (ferror(f)) {
		printf("\nfgetc failed\n");
		exit(EXIT_FAILURE);
	}
	fclose(f);
}

FILE *encode(char *fileName) {
	int symbolCount = 256;
	int **freqTable = malloc(symbolCount * sizeof(int*));
	int i;
	if (freqTable == 0) {
		printf("\nmalloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < symbolCount; ++i) {
		freqTable[i] = malloc(2 * sizeof(int));
		if (freqTable[i] == 0) {
			printf("\nmalloc failed\n");
			exit(EXIT_FAILURE);
		}
	}
	memset(freqTable, 0, 2 * symbolCount * sizeof(int));
	fillFreqs(freqTable, symbolCount, fileName);
	for (i = 0; i < symbolCount; ++i) {
		free(freqTable[i]);
	}
	free(freqTable);
}

int main() {
	return 0;
}

