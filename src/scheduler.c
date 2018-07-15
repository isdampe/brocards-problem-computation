#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdbool.h>
#include "scheduler.h"

void brocard_scheduler_init(struct brocard_scheduler *scheduler, const int num_threads, unsigned long long upper_bound)
{
	scheduler->num_threads = num_threads;
	scheduler->upper_bound = upper_bound;
	scheduler->progress = 0;

	scheduler->steps = malloc(num_threads * sizeof(struct brocard_thread));

	for (int i=0; i<num_threads; ++i)
		scheduler->steps[i].busy = false;
}

void brocard_scheduler_free(struct brocard_scheduler *scheduler)
{
	free(scheduler->steps);
}

static void *brocard_scheduler_compute(struct brocard_thread *thread)
{

	unsigned long long end = thread->step.n_init + SCHEDULER_WORK_GROUP_AMOUNT;
	if (thread->step.n_init == 0) {
		thread->step.n_init = 1;
		end -= 1;
	}

	for (int i=thread->step.n_init; i<end; ++i) {
		thread->step.n_init = i;
		brocard_step_process(&thread->step);
	}

	pthread_mutex_lock(&thread->lock);
	thread->busy = false;
	pthread_mutex_unlock(&thread->lock);
}

static void brocard_scheduler_dispatch_thread(struct brocard_scheduler *scheduler)
{
	while (1) {
		for (int i=0; i<scheduler->num_threads; ++i) {
			if (scheduler->steps[i].busy == false) {

				pthread_mutex_lock(&scheduler->steps[i].lock);
				scheduler->steps[i].step.n_init = scheduler->progress * SCHEDULER_WORK_GROUP_AMOUNT;
				scheduler->steps[i].busy = true;
				pthread_create(&scheduler->steps[i].thread_id, NULL, brocard_scheduler_compute, &scheduler->steps[i]);
				pthread_mutex_unlock(&scheduler->steps[i].lock);
				printf("Dispatch: thread %i given range %lli-%lli\n",
					i, (scheduler->progress * SCHEDULER_WORK_GROUP_AMOUNT),
					(scheduler->progress * SCHEDULER_WORK_GROUP_AMOUNT) + SCHEDULER_WORK_GROUP_AMOUNT);

				return;
			}
		}
	}
}

void brocard_scheduler_loop(struct brocard_scheduler *scheduler)
{
	while (scheduler->progress < (scheduler->upper_bound / SCHEDULER_WORK_GROUP_AMOUNT)) {
		brocard_scheduler_dispatch_thread(scheduler);
		scheduler->progress++;
	}

	//Wait for threads to finish.
	printf("Scheduler done. Waiting for threads to finalise...\n");
	for (int i=0; i<scheduler->num_threads; ++i) {
		pthread_join(scheduler->steps[i].thread_id, NULL);
	}

}