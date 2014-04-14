#include <stdbool.h>
#include <stdlib.h>
#include "common.h"

void sort(int A[], size_t n)
{
	bool is_sorted;

	do {
		is_sorted = true;

		for (size_t i = 0; i + 1 < n; i++) {
			if (A[i] > A[i + 1]) {
				swap(A[i], A[i + 1]);
				is_sorted = false;
			}
		}
	} while (!is_sorted);
}
