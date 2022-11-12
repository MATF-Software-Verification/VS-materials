#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	int n;
	int i;
	double *a = NULL;
	int allocated = 1;
	int memory = 0;

	scanf("%d", &n);

	for (i = 0; i < n; i++) {
		allocated *= 2;
		memory = allocated * sizeof(double);
		printf("sada je i = %d\t allocated = %dB\n", i, memory);

		a = malloc(memory);
		if (a == NULL) {
			fprintf(stderr, "Realloc failed!\n");
			exit(EXIT_FAILURE);
		}

		printf("sada je i = %d\t allocated = %d\n", i, memory);
		free(a);
	}

	return 0;
}
