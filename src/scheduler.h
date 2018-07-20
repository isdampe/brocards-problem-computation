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
	FILE *prg_fh;
	int results;
};

void brocard_scheduler_init(struct brocard_scheduler *scheduler, const int num_threads, const unsigned long long upper_bound, const unsigned long long start_at);
static void brocard_auto_restore(struct brocard_scheduler *scheduler);
void brocard_scheduler_free(struct brocard_scheduler *scheduler);
static void brocard_scheduler_dispatch_thread(struct brocard_scheduler *scheduler);
static void brocard_write_progress_persist(const struct brocard_scheduler *scheduler);
void brocard_scheduler_loop(struct brocard_scheduler *scheduler);

#endif