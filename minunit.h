/* file: minunit.h taken from by Jera design - https://jera.com/techinfo/jtns/jtn002 and modified */

#ifndef MINUNIT_H
#define MINUNIT_H
///string.h = libreria dove è possibile inserire stringhe, caratteri.
#include <string.h>

/**extern = viene definita una variabile esterna in un programma, la variabile è modificabile da qualsiasi funzione del programma. Presenti nel file game.c*/
extern int tests_run;
extern int tests_passed;

int run_all_tests(int argc, char **argv);

#define mu_assert(message, test) do \
{ \
	if (!(test)) \
		printf("%s\n",message); \
	else \
		tests_passed++; \
	} \
while (0)

#define mu_run_test(test) do \
{ \
	test(); \
	tests_run++; \
} \
while (0)

#endif
