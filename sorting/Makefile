TARGETS=$(filter-out main,$(subst .c,,$(basename $(wildcard *.c))))

CFLAGS=-g -D_POSIX_C_SOURCE=199309L -std=c99 -I.. -Wall -Wextra

.PHONY: all
all: $(TARGETS)

.PHONY: clean
clean:
	rm $(TARGETS)

%: %.c main.c
	$(CC) $(CFLAGS) $@.c main.c -o $@
