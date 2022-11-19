/* Naive dining philosophers with inconsistent lock acquisition
   ordering. */

#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>

static pthread_t phil[5];
static struct {
	pthread_mutex_t m;
	char pad[120 - sizeof(pthread_mutex_t)];
} chop[5];

void *dine(void *arg)
{
	int i;
	long n = (long)arg;
	long left = (long)arg;
	long right = (left + 1) % 5;

	printf("Philosopher %ld is thinking\n", n);

	if (left > right) {
		long tmp = left;
		left = right;
		right = tmp;
	}

	for (i = 0; i < 1000 /*arbitrary */ ; i++) {
		pthread_mutex_lock(&chop[left].m);
		pthread_mutex_lock(&chop[right].m);

		/* eating */
		printf("Philosopher %ld is eating\n", n);
		usleep(15);

		pthread_mutex_unlock(&chop[right].m);
		pthread_mutex_unlock(&chop[left].m);

		printf("Philosopher %ld finished eating\n", n);

	}
	return NULL;
}

int main(void)
{
	long i;
	assert(sizeof(pthread_mutex_t) <= 120);

	for (i = 0; i < 5; i++)
		pthread_mutex_init(&chop[i].m, NULL);

	for (i = 0; i < 5; i++)
		pthread_create(&phil[i], NULL, dine, (void *)i);

	sleep(1);

	for (i = 0; i < 5; i++)
		pthread_join(phil[i], NULL);

	for (i = 0; i < 5; i++)
		pthread_mutex_destroy(&chop[i].m);

	return 0;
}
