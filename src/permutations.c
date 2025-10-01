#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct Permutation {
    unsigned *nums;
    unsigned n;
} permutation_t;

typedef struct PermutationIterator {
    permutation_t value;
    int next_perm_exist;
} iterator_t;

// Обмен местами элементов
static void swap(unsigned *a, unsigned *b) {
    unsigned temp = *a;
    *a = *b;
    *b = temp;
}

// Для разворота части массива
void reverse(unsigned *arr, size_t first, size_t last) {
    while (first < last) {
        swap(&arr[first], &arr[last]);
        first++;
        last--;
    }
}

void iterator_init(iterator_t *i, unsigned n) {
    i->value.nums = (unsigned *)malloc(n * sizeof(unsigned));
    i->value.n = n;

    // Начальная перестановка от 0 до n-1 по возрастанию
    for (unsigned j = 0; j < n; ++j) {
        i->value.nums[j] = j;
    }

    i->next_perm_exist = (n > 0);
}

const permutation_t *iterator_value(const iterator_t *i) {
    return &i->value;
}

int iterator_has_next(const iterator_t *i) {
    return i->next_perm_exist;
}

void iterator_next(iterator_t *i) {
    if (!i->next_perm_exist) {
        return;
    }

    // Алгоритм Нарайаны

    // Находим самый правый индекс, для которого nums[k] < nums[k+1]
    int k = -1;
    for (int j = i->value.n - 2; j >= 0; --j) {
        if (i->value.nums[j] < i->value.nums[j + 1]) {
            k = j;
            break;
        }
    }

    if (k == -1) {
        i->next_perm_exist = 0;
        return;
    }

    // Находим самый правый индекс, элемент по которому больше k-го элемента
    int l = -1;
    for (int j = i->value.n - 1; j > k; --j) {
        if (i->value.nums[k] < i->value.nums[j]) {
            l = j;
            break;
        }
    }

    // Меняем местами элементы k и l
    swap(&i->value.nums[k], &i->value.nums[l]);

    // Разворачиваем часть массива после k
    reverse(i->value.nums, k + 1, i->value.n - 1);
}

void iterator_destroy(iterator_t *i) {
    free(i->value.nums);
    i->value.nums = NULL;
    i->value.n = 0;
    i->next_perm_exist = 0;
}

void print_permutation(const permutation_t *perm) {
    printf("{ ");
    for (unsigned i = 0; i < perm->n; ++i) {
        if (i < perm->n-1) {printf("%u, ", perm->nums[i]);}
        else printf("%u ", perm->nums[i]);
    }
    printf("}\n");
}