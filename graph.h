#include "matrix.h"

struct graph {
	struct matrix *adjecency;
};

struct graph *graph_new(size_t vertices);
void graph_free(struct graph *G);

void graph_connect(struct graph *G, size_t u, size_t v);
void graph_disconnect(struct graph *G, size_t u, size_t v);
int graph_is_connected(const struct graph *G, size_t u, size_t v);
