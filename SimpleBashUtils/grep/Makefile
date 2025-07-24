CC = gcc
CFLAGS = -Wall -Werror -Wextra
GG = clang-format -n test1.txt
GGC = clang-format -i test1.txt

all: s21_grep

s21_grep: s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	rm -f s21_grep

rebuild: clean all