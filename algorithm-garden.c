// Algorithm Garden
// ================

// The goal of the Algorithm Garden is to demonstrate simple implementations
// of the core compute science algorithms. The implementation language is C
// because it gives great control over the machine and is simple to write and
// understand.

// Includes
// ========

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Helpers
// =======

// A macro to swap the values of two `int`s.
#define swap(x, y) do { int t = (x); x = (y); y = t; } while (0);

// Minimum and maximum
// ===================

// Finding a minimum and a maximum of an array of numbers are operations that
// can be completed in linear time. The implementations are very similar to each
// other. In fact one can implement a general `min` procedure that finds a
// minimum of any totally ordered set. Here we take a more direct approach and
// assume the natural ordering of integers.

// Index of minimum
// ----------------

// The procedure stores the index of an element with minimum value in `result`
// and returns `1`.  If the minimum doesn't exist then `0` is returned.
int min_index(int A[], size_t n, size_t *result)
{
	// An empty array doesn't have a minimum thus an error is reported.
	if (!n) {
		return 0;
	}

	// The minimum of a subarray `A[0..i]`. Initially `i = 0` so `m = 0`.
	size_t m = 0;

	// We iterate over the remaining elements and update the minimum in each
	// iteration.
	for (size_t i = 1; i < n; i++) {
		// If the current `i`-th element is lower than the current
		// minimum then it becomes the new minimum.
		if (A[i] < A[m]) {
			m = i;
		}
	}

	// Save the result and return success.
	*result = m;
	return 1;
}

// Minimum
// -------

// The procedure stores the value of a minimum in `result` and returns `1`. If
// the minimum doesn't exist then `0` is returned.
int min(int A[], size_t n, int *result)
{
	// The index of a minimum (if it exists).
	size_t index;

	// Find the index of a minimum. If it doesn't exist then return an
	// error.
	if (!min_index(A, n, &index)) {
		return 0;
	}

	// Save the value of the minimum and return success.
	*result = A[index];
	return 1;
}

// Index of maximum
// ----------------

// This is identical to `min_index` with the exception of `>`
int max_index(int A[], size_t n, size_t *result)
{
	if (!n) {
		return 0;
	}

	size_t m = 0;

	for (size_t i = 1; i < n; i++) {
		// `>` below is the only difference between `min_index`.
		if (A[i] > A[m]) {
			m = i;
		}
	}

	*result = m;
	return 1;
}

// maximum
// -------

// Again this is identical to `min` with the exception of using `max_index`
// instead of `min_index`.
int max(int A[], size_t n, int *result)
{
	size_t index;

	if (!max_index(A, n, &index)) {
		return 0;
	}

	*result = A[index];
	return 1;
}

// Sorting
// =======

// Selection sort
// --------------
// Selection sort sorts an array by iterating over the elements of an array in
// search for an element appropriate for the current position. It *selects* an
// element to place in the current position.
void selection_sort(int A[], size_t n)
{
	// `i` is the index of the current position.
	size_t i;

	// Iterate over all positions except the last one.
	for (i = 0; i + 1 < n; i++) {
		// `m` is the index of a minimum of `A[i..n - 1]`.
		size_t m;

		// Find the right value of `m`. No need to check for errors
		// because the array is non-empty if the loop is iterating.
		min_index(A + i, n - i, &m);

		// Place the discovered element into its correct position.
		swap(A[i], A[m]);
	}
}

// Insertion sort
// --------------
// Insertion sort sorts by iterating over positions of the array in order to
// find the right one for the current element. The algorithm *inserts* an
// element into the right place.
void insertion_sort(int A[], size_t n)
{
	// `i` is the index of an element that we're placing into the right
	// position.
	size_t i;

	// Iterate over all elements.
	for (size_t i = 1; i < n; i++) {
		// Move the current element to the left
		for (size_t j = i; j > 0; j--) {
			// If the element to the left is greater than the
			// current element then swap them. This brings us closer
			// to the sorted order.
			if (A[j - 1] > A[j]) {
				swap(A[j], A[j + 1]);
			} else {
				// If the elements are in the correct relative
				// order then we found the right position for
				// the `i`-th element.
				break;
			}
		}
	}
}

// Quicksort
// ---------

// The procedure `partition` places the last element of `A` into the correct
// position. It's a building block of the Quicksort algorithm.
size_t partition(int A[], size_t n)
{
	// `x` is the so called pivot - the element to place in the right
	// position.
	int x = A[n - 1];
	// The elements `L = A[0..p - 1]` are `< x`.
	size_t p = 0;
	// The elements `R = A[p..q - 1]` are `> x`.
	size_t q = 0;

	// Iterate over all elements of the array except the last.
	for (size_t i = 0; i + 1 < n; i++) {
		if (A[i] < x) {
			// Add the `i`-th element to `L` and shift `R` to the
			// right.
			swap(A[p], A[i]);
			p++;
			q++;
		} else {
			// Add the `i`-th element to `R`.
			swap(A[q], A[i]);
			q++;
		}
	}

	// Put the pivot into the right place and return its index.
	swap(A[n - 1], A[p]);

	return p;
}

// The quicksort algorithm sorts by putting the pivot into the right place and
// sorting the two subarrays recursively. Note that this is a randomised variant
// of the algorithm.
void quicksort(int A[], size_t n)
{
	// Nothing to do for an empty array.
	if (!n) {
		return;
	}

	// Randomise the pivot.
	swap(A[rand() % n], A[n - 1]);

	// Place the pivot into the correct position `p`.
	size_t p = partition(A, n);

	// Sort the left and right subarrays.
	quicksort(A, p);
	quicksort(A + p + 1, n - p - 1);
}

// Bubble sort
// -----------

// Bubble sort sorts by moving elements to the right unless a sorted order is
// achieved.

void bubble_sort(int A[], size_t n)
{
	bool is_sorted;

	do {
		// We assume that the array is sorted unless we make a swap (see
		// below).
		is_sorted = true;

		// Bubble all elements to the right.
		for (size_t i = 0; i + 1 < n; i++) {
			// Move the element to the right until a greater element
			// is found.
			if (A[i] > A[i + 1]) {
				swap(A[i], A[i + 1]);

				// Another iteration of the outer loop is
				// required!
				is_sorted = false;
			}
		}
	} while (!is_sorted);
}

// Counting sort
// -------------

// Counting sort is an example of linear time sorting algorithms. It assumes
// that the keys are small integers and sorts by counting the occurences of each
// key.

// The procedure below is a helper used by the main procedure. Here `A` and `n`
// is the input array and its size, `k` is the maximum value of an element in
// `A` and `B` is the output array (of size `n`).
static void do_counting_sort(int A[], size_t n, unsigned int k, int B[])
{
	// `C` is an array used to count the number of occurences of the keys.
	int *C = calloc(k, sizeof(size_t));

	// Count the occurences of the keys.
	for (size_t i = 0; i < n; i++) {
		C[A[i]]++;
	}

	// Count the number of elements less or equal to a particular element.
	for (unsigned int i = 1; i < k; i++) {
		C[i] += C[i - 1];
	}

	// Place the results into `B`.
	for (size_t i = n - 1;; i--) {
		// Insert the element `A[i]` into `B`.
		B[C[A[i]] - 1] = A[i];

		// Updated the counter - one less element to sort.
		C[A[i]]--;

		// Stop when the beginning of `A` is reached.
		if (!i) {
			break;
		}
	}

	// Free the counters array.
	free(C);
}

// Counting sort `A`.
void counting_sort(int A[], size_t n, int k)
{
	// The temporary output.
	int *B = calloc(n, sizeof(int));

	// Sort `A` and place the result into `B`.
	do_counting_sort(A, n, k, B);

	// Copy `B` to `A` and free `B`.
	memcpy(A, B, n * sizeof(int));
	free(B);
}

// Heap sort
// ---------

// Return the left child of `i`.
static size_t left(size_t i)
{
	return 2 * i + 1;
}

// Return the right child of `i`.
static size_t right(size_t i)
{
	return left(i) + 1;
}

// Return the parent of `i`.
static size_t parent(size_t i)
{
	return ((i + 1) >> 1) - 1;
}

// Satisfy the max-heap property on a tree rooted in `A[0]` where the subtrees
// at `A[1]` and `A[2]` are max-heaps.
static void max_heapify(int A[], size_t n, size_t i)
{
	// The index of the greatest element from `A[0..2]`.
	size_t M;

	// Compare the root with the left child.
	if (left(i) < n && A[i] < A[left(i)]) {
		M = left(i);
	} else {
		M = i;
	}

	// Compare the previous maximum with the right child.
	if (right(i) < n && A[M] < A[right(i)]) {
		M = right(i);
	}

	// At this point `M` is the index of a maximum in `A[0..2]`. If `M == 0`
	// then `A` has the max-heap property and there's nothing to do.
	if (M == i) {
		return;
	}

	// Push the root element of `A` down the heap in the right direction and
	// recursively turn the subtree into a max-heap.
	swap(A[M], A[i]);

	max_heapify(A, n, M);
}

// Remove the maximum element of a heap and return it.
static int extract_max(int A[], size_t n)
{
	// The maximum of a max-heap is by definition the root element.
	int max = A[0];

	// Replace the root with the last element and fix the max-heap property.
	A[0] = A[n - 1];
	max_heapify(A, n - 1, 0);

	// Return the maximum.
	return max;
}

// Build a max-heap in-place given an array.
static void build_max_heap(int A[], size_t n)
{
	// Nothing to do for an empty array.
	if (!n) {
		return;
	}
	
	// `i` is the index of the root of a sub-heap. We start from the right
	// end of the array. This is equivalent to the bottom of the heap.
	size_t i = n - 1;

	do {
		// Fix the max-heap property of a subtree rooted in `A[i]` and
		// move to the element to the next element.
		max_heapify(A, n, i);
	} while(i-- > 0);
}

// Sort an array using max-heaps.
void heap_sort(int A[], size_t n)
{
	// Turn the input array into a max-heap.
	build_max_heap(A, n);

	// Repeatedly extract the maximum element and put it at the end of the
	// array. The elements `A[0..n - i - 1]` are the max-heap while
	// `A[n - i..n - 1]` are the sorted output array.
	for (size_t i = 0; i < n; i++) {
		int max = extract_max(A, n - i);
		A[n - i - 1] = max;
	}
}

// Radix sort
// ----------

// Return the `I`-th hexadecimal digit of `x`.
static int key(int x, size_t I)
{
	return (x >> (4 * I)) & 0x0F;
}

// A variant of insertion sort that uses hexadecimal digits as keys. Production
// code should have a single insertion sort with parametrised key but this
// isn't production, is it?
static void radix_insertion_sort(int A[], size_t n, size_t I)
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

// Sort `A` using radix sort. The algorithm relies on the fact that insertion
// sort is stable. We sort multiple times using more significant digits in each
// iteration of the loop. Insertion sort can be replaced with any other stable
// sorting algorithm (i.e. preserving the order of elements with equal keys).
void radix_sort(int A[], size_t n)
{
	for (size_t I = 0; I < 8 * sizeof(*A) / 4; I++) {
		radix_insertion_sort(A, n, I);
	}
}

// Number theory
// =============

// Power Modulo n
// --------------

// Return `b^n mod m`. In order to avoid overflows the procedure reduces `b`
// modulo `m` before entering the loop and after each iteration.
int pow_mod(int b, int n, int m)
{
	int result = 1;
	for (b = b % m; n; n--) {
		result = (result * b) % m;
	}
	return result;
}

// Greatest Common Divisor
// -----------------------

// Return the greatest common divisor of `a` and `b`. The procedure implements
// the recursive Euclidean algorithm.
int recursive_euclidean_gcd(int a, int b)
{
	// Ignore the signs and ensure that `a` is greater than `b`.
	a = abs(a);
	b = abs(b);
	if (b > a) {
		swap(a, b);
	}

	// If `b` divides `a` then `b` is the GCD.
	int r = a % b;
	if (r == 0) {
		return b;
	}

	// An expression of a mathematical fact that GCD(a, b) = GCD(b, r).
	return recursive_euclidean_gcd(b, r);
}

int iterative_euclidean_gcd(int a, int b)
{
	// Ignore the signs and ensure that `a` is greater than `b`.
	a = abs(a);
	b = abs(b);
	if (a < b) {
		swap(a, b);
	}

	int r;

	while ((r = a % b) != 0) {
		a = b;
		b = r;
	}

	return b;
}

// Least Common Multiple
// ---------------------

// Return the least common multiple of `a` and `b`. The implementation uses the
// fact that LCM(a, b) GCD(a, b) = ab.
int lcm(int a, int b)
{
	return abs(a * b / recursive_euclidean_gcd(a, b));
}

// Fermat Primarility Test
// -----------------------

// The test uses the fact that `a^p = a` modulo `p` if `p` is a prime number.
// Therefore if the equality above doesn't hold for some `a` then `p` is not
// a prime. However even when the equality holds for all `a`s it *does not*
// mean that `p` is a prime. Composite numbers that pass the test are called
// Carmichael numbers. The first such number is 561.

// Return `true` if there's a chance that `p` is prime, `false` if it's
// certainly not a prime.
bool fermat_prime(int p, int tests)
{
	while (tests) {
		int a = rand();
		if (pow_mod(a, p - 1, p) != 1) {
			return false;
		}
	}
	return true;
}
