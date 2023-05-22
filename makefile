CC=gcc
CFLAGS=-Isrc
LDFLAGS=
source_files := $(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c) $(wildcard src/*/*/*/*.c) $(wildcard src/*/*/*/*/*.c) $(wildcard src/*/*/*/*/*/*.c)
header_files := $(wildcard src/*.h) $(wildcardsrc/ */*.h) $(wildcard src/*/*/*.h) $(wildcard src/*/*/*/*.h) $(wildcard src/*/*/*/*/*.h) $(wildcard src/*/*/*/*/*/*.h)

object_files := $(source_files:.c=.o)

%.o: %.c $(header_files)
	$(CC) -c -o $@ $< $(CFLAGS)

build: $(object_files)
	$(CC) -o bin/NeonLang $^ $(LDFLAGS)

run : build
	./bin/NeonLang example.ne