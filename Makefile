SORTING_TARGETS=$(filter-out main,$(subst .c,,$(basename $(wildcard sorting/*.c))))
TARGETS=$(SORTING_TARGETS)

CFLAGS=-g -D_POSIX_C_SOURCE=199309L -std=c99 -I. -Wall -Wextra

.PHONY: all
all: $(SORTING_TARGETS)

sorting/%: sorting/%.c sorting.c common.h
	$(CC) $(CFLAGS) $@.c sorting.c -o $@

.PHONY: clean
clean:
	rm $(TARGETS)

.PHONY: data
data:
	./generate $(TARGETS) > report/data.js
