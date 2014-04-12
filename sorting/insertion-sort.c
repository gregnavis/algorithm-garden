#include <stdlib.h>
#include "common.h"

void sort(int A[], size_t n)
{
	for (size_t i = 1; i < n; i++) {
		size_t j = i - 1;

		do {
			if (A[j] > A[j + 1]) {
				swap(A[j], A[j + 1]);
			}
		} while(j-- > 0);
	}
}

