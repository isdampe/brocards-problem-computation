#include <stdio.h>
#include <stdlib.h>
#include "brocard.h"
#include "scheduler.h"

void usage() {
	printf("Usage: ./brocard [num_threads] [max_number] [start_number=0]\n");
	exit(1);
}

int main(int argc, char **argv)
{
	int thread_count;
	unsigned long long max_number, start_at = 0;
	if (argc < 3)
		usage();

	thread_count = atoi(argv[1]);
	if (thread_count == 0)
		usage();

	max_number = atoll(argv[2]);
	if (max_number == 0)
		usage();

	if (argc >= 4)
		start_at = atoll(argv[3]);

	struct brocard_scheduler scheduler;
	brocard_scheduler_init(&scheduler, thread_count, max_number, start_at);
	printf("Here\n");
	brocard_scheduler_loop(&scheduler);
	brocard_scheduler_free(&scheduler);
	return 0;
}

