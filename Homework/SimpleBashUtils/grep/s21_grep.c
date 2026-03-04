#include "s21_grep.h"

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void parse_args(int argc, char *argv[], grep_params *params) {
  int opt;
  params->e_flag = 0;
  params->i_flag = 0;
  params->v_flag = 0;
  params->c_flag = 0;
  params->l_flag = 0;
  params->n_flag = 0;
  params->patterns = NULL;
  params->pattern_count = 0;

  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
      case 'e':
        params->e_flag = 1;
        params->patterns = realloc(
            params->patterns, (params->pattern_count + 1) * sizeof(char *));
        params->patterns[params->pattern_count] = optarg;
        params->pattern_count++;
        break;
      case 'i':
        params->i_flag = 1;
        break;
      case 'v':
        params->v_flag = 1;
        break;
      case 'c':
        params->c_flag = 1;
        break;
      case 'l':
        params->l_flag = 1;
        break;
      case 'n':
        params->n_flag = 1;
        break;
      default:
        fprintf(stderr, "Неизвестный флаг: %c\n", opt);
        exit(EXIT_FAILURE);
    }
  }

  if (params->pattern_count == 0 && optind < argc) {
    params->patterns =
        realloc(params->patterns, (params->pattern_count + 1) * sizeof(char *));
    params->patterns[params->pattern_count] = argv[optind++];
    params->pattern_count++;
  }
  if (params->pattern_count == 0) {
    fprintf(stderr, "Использование: %s [-eivcln] <pattern> <filename>\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }
}
void process_file(char *filename, grep_params params, int mult_files) {
  regex_t regex;
  int regex_flags = REG_EXTENDED;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Не удалось открыть файл %s\n", filename);
    exit(1);

  } else {
    if (params.i_flag) {
      regex_flags |= REG_ICASE;
    }
    char *combined_pattern = malloc(1);
    combined_pattern[0] = '\0';

    for (int i = 0; i < params.pattern_count; i++) {
      size_t len = strlen(combined_pattern) + strlen(params.patterns[i]) + 2;
      combined_pattern = realloc(combined_pattern, len);
      strcat(combined_pattern, params.patterns[i]);
      if (i < params.pattern_count - 1) {
        strcat(combined_pattern, "|");
      }
    }
    int reti = regcomp(&regex, combined_pattern, regex_flags);
    if (reti != 0) {
      fprintf(stderr, "Не удалось скомпилировать регулярное выражение\n");
      fclose(file);
      free(combined_pattern);
      exit(1);
    }
    free(combined_pattern);
  }

  char *line = NULL;
  size_t len = 0;
  ssize_t read;
  int line_number = 0;
  int count = 0;
  int has_match = 0;

  while ((read = getline(&line, &len, file)) != -1) {
    line_number++;

    int reti = regexec(&regex, line, 0, NULL, 0);
    int match = (reti == 0);

    if (params.v_flag) {
      match = !match;
    }

    if (match) {
      count++;
      has_match = 1;

      if (params.l_flag) {
        continue;
      }

      if (!params.c_flag) {
        if (mult_files) printf("%s:", filename);
        if (params.n_flag) {
          printf("%d:", line_number);
        }
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] != '\n')
          printf("%s\n", line);
        else
          printf("%s", line);
      }
    }
  }

  if (params.l_flag && has_match) {
    printf("%s\n", filename);
  }

  if (params.c_flag) {
    if (mult_files) printf("%s:", filename);
    printf("%d\n", count);
  }

  free(line);
  fclose(file);
  regfree(&regex);
}

int main(int argc, char *argv[]) {
  grep_params params;

  parse_args(argc, argv, &params);

  int mult_files = (argc - optind > 1);
  for (int i = optind; i < argc; i++) process_file(argv[i], params, mult_files);

  free(params.patterns);
  return 0;
}
