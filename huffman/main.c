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

int freqCompare(const void *a, const void *b) {
	int arg1 = ((int**)a)[0][1];
	int arg2 = ((int**)b)[0][1];
	if (arg1 < arg2) {
		return -1;
	}
	else if (arg1 > arg2) {
		return 1;
	}
	else {
		return 0;
	}
}

void fillEncoding(int **encoding, int **freqTable) {
	/* TODO: implement this */;
}

FILE *encode(char *fileName) {
	int symbolCount = 256;
	int **freqTable = malloc(symbolCount * sizeof(int*));
	int i;
	int **encoding;
	int initCodeLength = 4;
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
	qsort(freqTable, symbolCount, sizeof(freqTable[0]), freqCompare);
	encoding = malloc(symbolCount * sizeof(int*));
	if (encoding == 0) {
		printf("\nmalloc failed\n");
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < symbolCount; ++i) {
		/* TODO: 256 * 8 * (1 * 8 + 1 * 8) -> 32 KB 
		 *	allocate space for 256 x (1 + initCodeLength) matrix	
		 *	each word after first will hold a bitmap and bitmap words will be dynamic
		 * */
		encoding[i] = malloc((1 + initCodeLength) * sizeof(int));
		if (encoding[i] == 0) {
			printf("\nmalloc failed\n");
			exit(EXIT_FAILURE);
		}
	}
	fillEncoding(encoding, freqTable);
	for (i = 0; i < symbolCount; ++i) {
		free(freqTable[i]);
		free(encoding[i]);
	}
	free(freqTable);
	free(encoding);
}

int main() {
	return 0;
}

