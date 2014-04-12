#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include <time.h>

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
	return result % range;
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

static double nsec2sec(long nsec)
{
	return nsec / 1000000000.0;
}

static double timestamp()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC_RAW, &now);
	return nsec2sec(now.tv_nsec) + now.tv_sec;
}

int main()
{
	for (size_t size = 1; size < 1000; size += 1) {
		printf("%zi\n", size);

		for (int i = 0; i < 10; i++) {
			int *array = random_array(size, 100);
			double start, end;

			start = timestamp();
			sort(array, size);
			end = timestamp();

			printf("%f ", end - start);

			if (!is_sorted(array, size)) {
				fprintf(stderr, "Unsorted array:\n");
				print_array(stderr, array, size);
				return 1;
			}
		}

		printf("\n");
	}
	return 0;
}
