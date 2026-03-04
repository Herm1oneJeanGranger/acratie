#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

typedef struct flags {
  int minus;
  int plus;
  int space;
  int zero;
} Flags;

typedef struct specifiers {
  void* p;
  unsigned int x;
  int d;
  short int hd;
  short unsigned int hu;
  long unsigned int lu;
  long int ld;
  double e;
  char c;
  double f;
  char* s;
  unsigned int u;
} Specifiers;

typedef struct values {
  int widthWithoutDot;
  int widthWithDot;
  int exponent;
  double floatingPointNumber;
  int digits;
} Values;

typedef struct length {
  int h;
  int l;
} Length;

void logic_for_to_string(Flags* flags, Values* values, char* tempStr, char* str,
                         int* result);
void length_for_parser(const char* format, int* i, Length* length);
void uint_to_str(unsigned int number, char* str, int* result, Flags* flags,
                 Values* values);
void luint_to_str(long unsigned int number, char* str, int* result,
                  Flags* flags, Values* values);
void suint_to_str(short unsigned int number, char* str, int* result,
                  Flags* flags, Values* values);
void str_to_str(char* s, char* str, int* result);
void double_to_str(double number, Values* values, Flags* flags, char* str,
                   int* result);
void parser(va_list ap, const char* format, char* str, int* result);
void flags_for_parser(const char* format, int* i, Flags* flags);
void num_to_str(int number, char* str, int* result, Flags* flags,
                Values* values);
void sint_to_str(short int number, char* str, int* result, Flags* flags,
                 Values* values);
void lint_to_str(long int number, char* str, int* result, Flags* flags,
                 Values* values);
void char_to_str(char symbol, char* str, int* result, Values* values,
                 Flags* flags);
void specifiers_for_parser(const char* format, va_list ap, int* i, char* str,
                           int* result, Specifiers* specs, Flags* flags,
                           Values* values, Length* length);
int calculate_width(const char* format, int* i);
void make_width(int width, char* str, int* result, Flags* flags);
void create_scientific_notation(double number, Values* values);
int s21_atoi(const char* numbers);
void hex_to_str(unsigned int value, char* str, char* result, int flags,
                int values, int uppercase);

#endif
