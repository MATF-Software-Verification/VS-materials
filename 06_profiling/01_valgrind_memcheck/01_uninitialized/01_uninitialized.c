#include <stdio.h>
#include <stdlib.h>

int main()
{
	int x;
	printf("x = %d\n", x);

	int *t = malloc(sizeof(int));
	printf("t = %d\n", *t);

	int y = x;

	return 0;
}
