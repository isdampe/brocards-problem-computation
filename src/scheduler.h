#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <pthread.h>
#include <stdbool.h>
#include "brocard.h"

#define SCHEDULER_WORK_GROUP_AMOUNT 10

struct brocard_thread {
	pthread_t thread_id;
	pthread_mutex_t lock;
	volatile bool busy;
	struct brocard_step step;
};

struct brocard_scheduler {
	int num_threads;
	struct brocard_thread *steps;
	unsigned long long upper_bound;
	unsigned long long progress;
};

void brocard_scheduler_init(struct brocard_scheduler *scheduler, const int num_threads, unsigned long long upper_bound);
void brocard_scheduler_free(struct brocard_scheduler *scheduler);
static void brocard_scheduler_dispatch_thread(struct brocard_scheduler *scheduler);
void brocard_scheduler_loop(struct brocard_scheduler *scheduler);

#endif