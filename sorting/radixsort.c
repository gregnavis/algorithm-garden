#include <stdlib.h>
#include "common.h"

static int key(int x, size_t I)
{
	return (x >> (4 * I)) & 0x0F;
}

static void insertion_sort(int A[], size_t n, size_t I)
{
	for (size_t i = 1; i < n; i++) {
		size_t j = i - 1;

		do {
			if (key(A[j], I) > key(A[j + 1], I)) {
				swap(A[j], A[j + 1]);
			}
		} while(j-- > 0);
	}
}

void sort(int A[], size_t n)
{
	for (size_t I = 0; I < 8 * sizeof(*A) / 4; I++) {
		insertion_sort(A, n, I);
	}
}
