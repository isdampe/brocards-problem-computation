#include <gmp.h>
#include <stdbool.h>
#include <stdio.h>
#include "brocard.h"

static void brocard_step_init(struct brocard_step *step)
{
	mpz_init(step->n);
	mpz_set_ui(step->n, step->n_init);
	mpz_init(step->m);
}

static void brocard_step_free(struct brocard_step *step)
{
	mpz_clear(step->n);
	mpz_clear(step->m);
}

static void brocard_compute_factorial_po(mpz_t n, unsigned long long n_init)
{
	//Compute n! + 1.
	mpz_t factorial_buffer;
	mpz_init(factorial_buffer);

	for (unsigned long long i=(n_init -1); i>0; --i) {
		mpz_set_ui(factorial_buffer, i);
		mpz_mul(n, n, factorial_buffer);
	}
	mpz_add_ui(n, n, 1);

	mpz_clear(factorial_buffer);
}

static bool brocard_compute_sqrt(mpz_t m, mpz_t n)
{
	bool result = false;
	mpz_t counter;
	mpz_init(counter);

	mpz_set_ui(counter, 1);
	mpz_set_ui(m, 0);

	if (mpz_root(m, n, 2) != 0)
		result = true;

	mpz_clear(counter);

	return result;
}

static void brocard_out_result(struct brocard_step *step)
{
	printf("------------------------------\nRESULT: ");
	printf("N = %llu", step->n_init);
	printf(", M = ");
	mpz_out_str(stdout, 10, step->m);
	printf("\n-------------------------------\n");
}

bool brocard_step_process(struct brocard_step *step)
{
	brocard_step_init(step);
	
	brocard_compute_factorial_po(step->n, step->n_init);

	if (brocard_compute_sqrt(step->m, step->n) == true)
		brocard_out_result(step);

//	brocard_step_free(step);
	return false;
}

