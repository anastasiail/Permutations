#include "permutations.h"
#include <stdio.h>

// Для n = 0
void test_n0() {
    printf("Для n=0:\n");
    iterator_t it;
    iterator_init(&it, 0);

    long long count = 0;
    while (iterator_has_next(&it)) {
        const permutation_t *p = iterator_value(&it);
        print_permutation(p);
        iterator_next(&it);
        count++;
    }

    printf("Число перестановок: %lld\n", count);

    iterator_destroy(&it);
}

// Для n = 1
void test_n1() {
    printf("Для n=1:\n");
    iterator_t it;
    iterator_init(&it, 1);

    long long count = 0;
    while (iterator_has_next(&it)) {
        const permutation_t *p = iterator_value(&it);
        print_permutation(p);
        iterator_next(&it);
        count++;
    }

    printf("Число перестановок: %lld\n", count);

    iterator_destroy(&it);
}

// Для n = 3
void test_n3() {
    printf("Для n=3:\n");
    iterator_t it;
    iterator_init(&it, 3);
    
    long long count = 0;
    while (iterator_has_next(&it)) {
        const permutation_t *p = iterator_value(&it);
        print_permutation(p);
        iterator_next(&it);
        count++;
    }

    printf("Число перестановок: %lld\n", count);

    iterator_destroy(&it); 
}

int main() {

    test_n0();
    test_n1();
    test_n3();

    unsigned n;
    printf("Введите n: ");
    scanf("%u", &n);

    iterator_t it;
    iterator_init(&it, n);

    long long count = 0;
    while (iterator_has_next(&it)) {
        const permutation_t *p = iterator_value(&it);
        print_permutation(p);
        iterator_next(&it);
        count++;
    }

    if (n == 0) {
        printf("{ }\n"); 
    }
    
    printf("Число перестановок: %lld\n", count);

    iterator_destroy(&it);
}