typedef float matrix_cell;

#define CELLS_SIZE(rows, columns) (((rows) * (columns)) * sizeof(matrix_cell))
#define MATRIX_SIZE(rows, columns) (2 * sizeof(size_t) + CELLS_SIZE(rows, columns))

struct matrix {
	size_t rows;
	size_t columns;
	matrix_cell cells[];
};

struct matrix *matrix_new(size_t rows, size_t columns);
void matrix_free(struct matrix *M);

matrix_cell matrix_get(const struct matrix *M, size_t row, size_t column);
void matrix_set(struct matrix *M, size_t row, size_t column, matrix_cell value);
