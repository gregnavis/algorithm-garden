#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static void counting_sort(int A[], size_t n, unsigned int k, int B[])
{
	int *C = calloc(k, sizeof(size_t));

	for (size_t i = 0; i < n; i++) {
		C[A[i]]++;
	}

	for (unsigned int i = 1; i < k; i++) {
		C[i] += C[i - 1];
	}

	for (size_t i = n - 1;; i--) {
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--;

		if (!i) {
			break;
		}
	}

	free(C);
}

void sort(int A[], size_t n)
{
	int *B = calloc(n, sizeof(int));
	counting_sort(A, n, MAX_VALUE, B);
	memcpy(A, B, n * sizeof(int));
	free(B);
}
