#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>

#include "common.h"

void sort(int[], size_t);

static bool is_sorted(int A[], size_t n)
{
	for (size_t i = 1; i < n; i++) {
		if (A[i - 1] > A[i]) {
			return false;
		}
	}
	return true;
}

static int random_int(int range)
{
	FILE *urandom = fopen("/dev/urandom", "r");
	int result;
	fread(&result, sizeof(result), 1, urandom);
	fclose(urandom);
	return abs(result % range);
}

static int *random_array(size_t size, int range)
{
	int *array = calloc(size, sizeof(int));
	for (size_t i = 0; i < size; i++) {
		array[i] = random_int(range);
	}
	return array;
}

static void print_array(FILE *f, int array[], size_t size)
{
	for (size_t i = 0; i < size; i++) {
		fprintf(f, "%d\n", array[i]);
	}
}

static double nsec2usec(long nsec)
{
	return nsec / 1000.0;
}

static double timestamp()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	return nsec2usec(now.tv_nsec) + now.tv_sec;
}

#define EXPECTED_ARGC 4

int main(int argc, char *argv[])
{
	if (argc != EXPECTED_ARGC) {
		fprintf(stderr, "Usage: %s from to step\n", argv[0]);
		return 2;
	}

	size_t from = atoi(argv[1]);
	size_t to = atoi(argv[2]);
	size_t step = atoi(argv[3]);

	for (size_t size = from; size <= to; size += step) {
		printf("%zi ", size);

		int *array = random_array(size, MAX_VALUE);
		double start, end;

		start = timestamp();
		sort(array, size);
		end = timestamp();

		printf("%.1f\n", end - start);

		if (!is_sorted(array, size)) {
			fprintf(stderr, "Unsorted array:\n");
			print_array(stderr, array, size);
			return 1;
		}
	}

	return 0;
}
