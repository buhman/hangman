CFLAGS = -Wall -Wextra -Werror -ggdb
CFLAGS += $(shell pkg-config --cflags freetype2)
LDFLAGS = $(shell pkg-config --libs freetype2)

all: otb-convert word-convert

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%: %.o
	$(CC) $(LDFLAGS) $< -o $@

.SUFFIXES:
