#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(void)
{
	char *arr = calloc(20, 1);
	scanf("%s", arr);
	char *arr1 = calloc(20, 1);
	memcpy(arr1, arr, strlen(arr));
	printf("%s\n", arr1);

	free(arr);
	free(arr1);
	return 0;
}
