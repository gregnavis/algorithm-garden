#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "matrix.h"

static inline size_t cell(const struct matrix *M, size_t row, size_t column)
{
	return row * M->columns + column;
}

struct matrix *matrix_new(size_t rows, size_t columns)
{
	struct matrix *M = malloc(MATRIX_SIZE(rows, columns));
	M->rows = rows;
	M->columns = columns;
	memset(M->cells, 0, CELLS_SIZE(rows, columns));
	return M;
}

void matrix_free(struct matrix *M)
{
	free(M);
}

matrix_cell matrix_get(const struct matrix *M, size_t row, size_t column)
{
	assert(row < M->rows);
	assert(column < M->columns);
	return M->cells[cell(M, row, column)];
}

void matrix_set(struct matrix *M, size_t row, size_t column, matrix_cell value)
{
	assert(row < M->rows);
	assert(column < M->columns);
	M->cells[cell(M, row, column)] = value;
}
