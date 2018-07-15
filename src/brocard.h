#ifndef BROCARD_H
#define BROCARD_H
#include <stdbool.h>
#include <gmp.h>

struct brocard_step {
	mpz_t n;
	mpz_t m;
	unsigned long long n_init;
};

static void brocard_step_init(struct brocard_step *step);
static void brocard_step_free(struct brocard_step *step);
static void brocard_compute_factorial_po(mpz_t n, unsigned long long n_init);
static bool brocard_compute_sqrt(mpz_t m, mpz_t n);
static void brocard_out_result(struct brocard_step *step);
bool brocard_step_process(struct brocard_step *step);

#endif