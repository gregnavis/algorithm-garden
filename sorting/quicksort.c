#include <stdlib.h>
#include "common.h"

static size_t partition(int A[], size_t n)
{
	int x = A[n - 1];
	size_t p = 0, q = 0;

	for (size_t i = 0; i + 1 < n; i++) {
		if (A[i] < x) {
			swap(A[p], A[q]);
			p++;
			q++;
		} else {
			swap(A[q], A[i]);
			q++;
		}
	}

	swap(A[n - 1], A[p]);

	return p;
}

void sort(int A[], size_t n)
{
	if (!n) {
		return;
	}

	swap(A[rand() % n], A[n - 1]);

	size_t p = partition(A, n);
	sort(A, p);
	sort(A + p + 1, n - p - 1);
}
