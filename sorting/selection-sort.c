#include <stdlib.h>
#include "common.h"

void sort(int A[], size_t n)
{
	for (size_t i = 0; i + 1 < n; i++) {
		size_t m = i;

		for (size_t j = i + 1; j < n; j++) {
			if (A[j] < A[m]) {
				m = j;
			}
		}

		swap(A[i], A[m]);
	}
}
