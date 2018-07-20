#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../src/brocard.h"
#include "../src/scheduler.h"

void usage() {
	printf("Usage: ./timed [num_threads]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	struct timespec start_time;
	struct timespec end_time;
	int thread_count;
	if (argc < 2)
		usage();

	thread_count = atoi(argv[1]);
	if (thread_count == 0)
		usage();

	struct brocard_scheduler scheduler;
	brocard_scheduler_init(&scheduler, thread_count, 10000, 0);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	brocard_scheduler_loop(&scheduler);
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	brocard_scheduler_free(&scheduler);

	double t_ns = ((double)(end_time.tv_nsec - start_time.tv_nsec) / 1000000000);

	printf("Took %f seconds\n", t_ns);

	return 0;
}
