#include <stdio.h>
#include <stdlib.h>
#include "brocard.h"
#include "scheduler.h"

void usage() {
	printf("Usage: ./brocard [num_threads]\n");
	exit(1);
}

int main(int argc, char **argv)
{

	if (argc < 2)
		usage();

	struct brocard_scheduler scheduler;
	brocard_scheduler_init(&scheduler, 4, 1000000);
	brocard_scheduler_loop(&scheduler);
	brocard_scheduler_free(&scheduler);
	return 0;
}