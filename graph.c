#include <stdlib.h>

#include "graph.h"

struct graph *graph_new(size_t vertices)
{
	struct graph *G = malloc(sizeof(*G));
	if (!G) {
		return NULL;
	}
	G->adjecency = matrix_new(vertices, vertices);
	return G;
}

void graph_free(struct graph *G)
{
	matrix_free(G->adjecency);
	free(G);
}

void graph_connect(struct graph *G, size_t u, size_t v)
{
	matrix_set(G->adjecency, u, v, 1.0f);
	matrix_set(G->adjecency, v, u, 1.0f);
}

void graph_disconnect(struct graph *G, size_t u, size_t v)
{
	matrix_set(G->adjecency, u, v, 0.0f);
	matrix_set(G->adjecency, v, u, 0.0f);
}

int graph_is_connected(const struct graph *G, size_t u, size_t v)
{
	return matrix_get(G->adjecency, u, v) != 0.0f;
}
