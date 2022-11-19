#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x = 123;
	printf("x = %d\n", x);

	int *t = calloc(1, sizeof(int));
	printf("t = %d\n", *t);

	int y = x;

	return 0;
}
