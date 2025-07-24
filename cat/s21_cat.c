#include "s21_cat.h"

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_FILES 100
#define MAX_LINE_LENGTH 4096

Flags process_flags(int argc, char **argv) {
  Flags flags = {0};
  int opt;
  int option_index = 0;
  static struct option long_options[] = {
      {"number", no_argument, 0, 'n'},
      {"number-nonblank", no_argument, 0, 'b'},
      {"squeeze-blank", no_argument, 0, 's'},
      {0, 0, 0, 0}};

  while ((opt = getopt_long(argc, argv, "nbsvetET", long_options,
                            &option_index)) != -1) {
    switch (opt) {
      case 'n':
        flags.pN = 1;
        break;
      case 'b':
        flags.pB = 1;
        break;
      case 's':
        flags.pS = 1;
        break;
      case 'v':
        flags.pV = 1;
        break;
      case 'e':
        flags.pE = 1;
        flags.pV = 1;
        break;
      case 't':
        flags.pT = 1;
        flags.pV = 1;
        break;
      case 'E':
        flags.pE = 1;
        break;
      case 'T':
        flags.pT = 1;
        break;
      default:
        printf("Неизвестный флаг: %c\n", opt);
        exit(EXIT_FAILURE);
    }
  }
  return flags;
}

void print_chars(int ch, Flags flags) {
  if (flags.pV || flags.pT || flags.pE) {
    if (flags.pT && ch == '\t') {
      printf("^I");
    } else if ((ch < 32 && ch != '\n' && ch != '\t') || ch == 127) {
      printf("^%c", ch ^ 0b01000000);
    } else if (ch >= 128 && ch < 160) {
      printf("^%c", ch ^ 0b11000000);
    } else if (flags.pE && ch == '\n') {
      printf("$\n");
    } else {
      putchar(ch);
    }
  } else {
    putchar(ch);
  }
}

int main(int argc, char **argv) {
  if (argc < 2) {
    fprintf(
        stderr,
        "Использование: %s "
        "[-n|-b|-s|-v|-e|-t|-E|-T|--number|--number-nonblank|--squeeze-blank] "
        "<имя файла> [<имя файла> ...]\n",
        argv[0]);
  } else {
    Flags flags = process_flags(argc, argv);

    const char *fileNames[MAX_FILES];
    int fileCount = 0;
    int error_flag = 0;
    for (int i = optind; i < argc && !error_flag; i++) {
      if (fileCount < MAX_FILES) {
        fileNames[fileCount++] = argv[i];
      } else {
        fprintf(
            stderr,
            "Предупреждение: превышено максимальное количество файлов (%d). "
            "Остальные файлы будут проигнорированы.\n",
            MAX_FILES);
        error_flag = 1;
      }
    }

    if (fileCount == 0) {
      printf("Ошибка: имя файла не указано\n");
      error_flag = 1;
    }
    if (!error_flag) {
      Cat_func(fileNames, flags, fileCount);
    }
  }
  return 0;
}

void Cat_func(const char *fileNames[MAX_FILES], Flags flags, int fileCount) {
  char line[MAX_LINE_LENGTH];
  int lineNumber = 1;
  int compressionLine = 0;
  int is_empty = 0;
  int error = 0;
  for (int i = 0; i < fileCount; i++) {
    FILE *myfile = fopen(fileNames[i], "r");

    if (myfile == NULL) {
      fprintf(stderr, "Не удалось открыть файл %s\n", fileNames[i]);
      error = 1;
    }

    if (!error) {
      while (fgets(line, sizeof(line), myfile)) {
        is_empty = (line[0] == '\n');

        if (flags.pS && is_empty) {
          if (compressionLine > 0) continue;
          compressionLine++;
        } else
          compressionLine = 0;

        if (flags.pB) {
          if (!is_empty)
            printf("%6d\t", lineNumber++);
          else if (flags.pE)
            printf("%6s\t", "");
        } else if (flags.pN && !flags.pB) {
          printf("%6d\t", lineNumber++);
        }

        for (int i = 0; line[i] != '\0'; i++) print_chars(line[i], flags);
      }
    }
    lineNumber = 1;
    fclose(myfile);
  }
}