#include <stdio.h>

int main() {
	char response = 'e';
	char buffer[10000];
	do {
		printf("Kelime: ");
		/* read a line */
		int top = 0;
		do {
			scanf("%c", &buffer[top]);
			++top;
		} while(buffer[top - 1] != '\n');
		/* top = buffer.size */
		--top;
		
		/* print steps */
		int i = 0;
		do {
			/* rotate left */
			char key = buffer[0];
			int j = 1;
			do {
				buffer[j - 1] = buffer[j];
				++j;
			} while(j < top);
			buffer[top - 1] = key;
			
			++i;
			
			/* print buffer */
			printf("%d.Adim: ", i);
			int k = 0;
			do {
				printf("%c", buffer[k]);
				++k;
			} while(k < top);
			printf("\n");
		} while (i < top);
		
		/* take response */
		printf("Devam icin e veya E-ye basin, cikmak icin baska tuslara: ")	;
		scanf("%c", &response);
		/* flush the buffer */
		fflush(stdin);
	} while (response == 'e' || response == 'E');
	
	return 0;
}
