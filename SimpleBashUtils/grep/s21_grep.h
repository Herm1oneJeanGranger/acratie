#ifndef S21_GREP_H
#define S21_GREP_H

typedef struct {
  int e_flag;
  int i_flag;
  int v_flag;
  int c_flag;
  int l_flag;
  int n_flag;
  char **patterns;
  int pattern_count;
} grep_params;

void process_file(char *filename, grep_params params, int mult_files);
#endif