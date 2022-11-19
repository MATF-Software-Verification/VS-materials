#include <pthread.h>
#include <stdio.h>

int var = 0;

void *child_fn(void *arg)
{
	var = 10;		/* Unprotected relative to parent */
	return NULL;
}

int main(void)
{
	pthread_t child1;

	pthread_create(&child1, NULL, child_fn, NULL);

	var = 20;		/* Unprotected relative to child */

	pthread_join(child1, NULL);
	printf("VAR = %d\n", var);

	return 0;
}
