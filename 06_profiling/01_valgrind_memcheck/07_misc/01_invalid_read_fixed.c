#include <stdlib.h>
#include <stdint.h>

int main()
{
	char *destination = calloc(27, sizeof(char));
	char *source = malloc(27 * sizeof(char));

	for (int i = 0; i < 27; i++) {
		*(destination + i) = *(source + i);
	}

	free(destination);
	free(source);
	return 0;
}
