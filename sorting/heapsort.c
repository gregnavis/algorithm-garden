#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static size_t left(size_t i)
{
	return 2 * i + 1;
}

static size_t right(size_t i)
{
	return left(i) + 1;
}

static size_t parent(size_t i)
{
	assert(i > 0);
	return ((i + 1) >> 1) - 1;
}

static void max_heapify(int A[], size_t n, size_t i)
{
	size_t m;

	if (left(i) < n && A[i] < A[left(i)]) {
		m = left(i);
	} else {
		m = i;
	}

	if (right(i) < n && A[m] < A[right(i)]) {
		m = right(i);
	}

	if (m == i) {
		return;
	}

	swap(A[m], A[i]);

	max_heapify(A, n, m);
}

static int extract_max(int A[], size_t n)
{
	int max = A[0];
	A[0] = A[n - 1];
	max_heapify(A, n - 1, 0);
	return max;
}

static void build_max_heap(int A[], size_t n)
{
	if (!n) {
		return;
	}
	
	size_t i = n - 1;

	do {
		max_heapify(A, n, i);
	} while(i-- > 0);
}

void sort(int A[], size_t n)
{
	build_max_heap(A, n);

	for (size_t i = 0; i < n; i++) {
		int max = extract_max(A, n - i);
		A[n - i - 1] = max;
	}
}
