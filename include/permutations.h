#ifndef PERMUTATIONS_H
#define PERMUTATIONS_H

#include <stdlib.h>

typedef struct Permutation permutation_t;
typedef struct PermutationIterator iterator_t;

// Объявления функций
void iterator_init(iterator_t *i, unsigned n);
const permutation_t *iterator_value(const iterator_t *i);
int iterator_has_next(const iterator_t *i);
void iterator_next(iterator_t *i);
void iterator_destroy(iterator_t *i);
void print_permutation(const permutation_t *perm);

#endif
