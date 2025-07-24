CC = gcc
CFLAGS = -Wall -Werror -Wextra
GG = clang-format -n myfile.txt
GGC = clang-format -i myfile.txt

all: s21_cat

s21_cat: s21_cat.c
	$(CC) $(CFLAGS) -o s21_cat $^

clean:
	rm -f s21_cat