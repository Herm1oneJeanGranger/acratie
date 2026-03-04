#include "s21_string.h"

void parser(va_list ap, const char* format, char* str, int* result) {
  Flags flags = {0};
  for (int i = 0; format[i]; i++) {
    Values values = {0};
    values.widthWithDot = 6;
    Specifiers specs = {0};
    Length length = {0};
    if (format[i] == '%') {
      i++;
      flags_for_parser(format, &i, &flags);
      if (format[i] > 48 && format[i] <= 57) {
        values.widthWithoutDot = calculate_width(format, &i);
      }
      if (format[i] == '.') {
        i++;
        values.widthWithDot = calculate_width(format, &i);
      }
      length_for_parser(format, &i, &length);
      specifiers_for_parser(format, ap, &i, str, result, &specs, &flags,
                            &values, &length);
    } else {
      char_to_str(format[i], str, result, &values, &flags);
    }
  }
}

void length_for_parser(const char* format, int* i, Length* length) {
  switch (format[*i]) {
    case 'h':
      length->h = 1;
      (*i)++;
      break;
    case 'l':
      length->l = 1;
      (*i)++;
      break;
  }
}

int s21_sprintf(char* str, const char* format, ...) {
  int result = 0;
  va_list ap;
  va_start(ap, format);
  parser(ap, format, str, &result);
  va_end(ap);
  str[result] = '\0';
  return result;
}

int calculate_width(const char* format, int* i) {
  int sizeForNumber = 1;
  int sign = 1;
  char* numbers = (char*)calloc(sizeForNumber, sizeof(char));
  if (format[*i] == '-') {
    sign = -1;
    (*i)++;
  }
  for (int indexForNumber = 0; format[*i] >= 48 && format[*i] <= 57;
       indexForNumber++) {
    if (sizeForNumber > indexForNumber + 1) {
      char* tempNumbers = realloc(numbers, (sizeForNumber += 1) * sizeof(char));
      numbers = tempNumbers;
      free(tempNumbers);
    }
    numbers[indexForNumber] = format[*i];
    (*i)++;
  }
  int number = s21_atoi(numbers);
  free(numbers);
  return number * sign;
}

int s21_atoi(const char* numbers) {
  int result = 0;
  int sign = 1;
  if (numbers[0] == '-') {
    sign = -1;
  }
  for (int i = 0; numbers[i] != '\0'; ++i) {
    result = result * 10 + numbers[i] - '0';
  }
  return result * sign;
}

void specifiers_for_parser(const char* format, va_list ap, int* i, char* str,
                           int* result, Specifiers* specs, Flags* flags,
                           Values* values, Length* length) {
  switch (format[*i]) {
    case 'i':
    case 'd':
      if (!length->h && !length->l) {
        specs->d = va_arg(ap, int);
        num_to_str(specs->d, str, result, flags, values);
      } else if (length->h && !length->l) {
        specs->hd = va_arg(ap, int);
        sint_to_str(specs->hd, str, result, flags, values);
      } else if (!length->h && length->l) {
        specs->ld = va_arg(ap, long int);
        lint_to_str(specs->ld, str, result, flags, values);
      }
      if (flags->minus)
        make_width(values->widthWithoutDot - values->digits, str, result,
                   flags);
      break;
    case 'c':
      specs->c = (char)va_arg(ap, int);
      char_to_str(specs->c, str, result, values, flags);
      break;
    case 'e':
    case 'E':
      specs->e = va_arg(ap, double);
      create_scientific_notation(specs->e, values);
      double_to_str(values->floatingPointNumber, values, flags, str, result);
      str[(*result)++] = format[*i];
      if (values->exponent >= 0 && !flags->plus) str[(*result)++] = '+';
      if (values->exponent < 0) {
        str[(*result)++] = '-';
        values->exponent = -values->exponent;
      }
      if (values->exponent > -100 && values->exponent < 100)
        str[(*result)++] = '0';
      num_to_str(values->exponent, str, result, flags, values);
      break;
    case 'f':
      specs->f = va_arg(ap, double);
      double_to_str(specs->f, values, flags, str, result);
      if (values->widthWithDot < 0) str[(*result)++] = format[*i];
      break;
    case '%':
      char_to_str(format[*i], str, result, values, flags);
      break;
    case 's':
      specs->s = va_arg(ap, char*);
      str_to_str(specs->s, str, result);
      break;
    case 'u':
      if (!length->h && !length->l) {
        specs->u = va_arg(ap, unsigned int);
        uint_to_str(specs->u, str, result, flags, values);
      } else if (length->h && !length->l) {
        specs->hu = va_arg(ap, unsigned int);
        suint_to_str(specs->hu, str, result, flags, values);
      } else if (!length->h && length->l) {
        specs->lu = va_arg(ap, long unsigned int);
        luint_to_str(specs->lu, str, result, flags, values);
      }
      break;
  }
}

void luint_to_str(long unsigned int number, char* str, int* result,
                  Flags* flags, Values* values) {
  values->digits = 0;
  if (flags->plus) {
    str[(*result)++] = '+';
  } else if (flags->space) {
    str[(*result)++] = ' ';
  }
  long unsigned int tempDSpec = number;
  do {
    values->digits++;
  } while ((tempDSpec /= 10) > 0);
  char tempStr[values->digits];
  for (int i = values->digits - 1; i >= 0; i--) {
    tempStr[i] = number % 10 + 48;
    number /= 10;
  }
  tempStr[values->digits] = '\0';
  logic_for_to_string(flags, values, tempStr, str, result);
}

void suint_to_str(short unsigned int number, char* str, int* result,
                  Flags* flags, Values* values) {
  values->digits = 0;
  if (flags->plus) {
    str[(*result)++] = '+';
  } else if (flags->space) {
    str[(*result)++] = ' ';
  }
  short unsigned int tempDSpec = number;
  do {
    values->digits++;
  } while ((tempDSpec /= 10) > 0);
  char tempStr[values->digits];
  for (int i = values->digits - 1; i >= 0; i--) {
    tempStr[i] = number % 10 + 48;
    number /= 10;
  }
  tempStr[values->digits] = '\0';
  logic_for_to_string(flags, values, tempStr, str, result);
}

void lint_to_str(long int number, char* str, int* result, Flags* flags,
                 Values* values) {
  values->digits = 0;
  if (number < 0) {
    str[(*result)++] = '-';
    number = -number;
  } else if (number > 0 && flags->plus) {
    str[(*result)++] = '+';
  } else if (number > 0 && flags->space && !flags->plus) {
    str[(*result)++] = ' ';
  }
  long int tempDSpec = number;
  do {
    values->digits++;
  } while ((tempDSpec /= 10) > 0);
  char tempStr[values->digits];
  for (int i = values->digits - 1; i >= 0; i--) {
    tempStr[i] = number % 10 + 48;
    number /= 10;
  }
  tempStr[values->digits] = '\0';
  logic_for_to_string(flags, values, tempStr, str, result);
}

void sint_to_str(short int number, char* str, int* result, Flags* flags,
                 Values* values) {
  values->digits = 0;
  if (number < 0) {
    str[(*result)++] = '-';
    number = -number;
  } else if (number > 0 && flags->plus) {
    str[(*result)++] = '+';
  } else if (number > 0 && flags->space && !flags->plus) {
    str[(*result)++] = ' ';
  }
  short int tempDSpec = number;
  do {
    values->digits++;
  } while ((tempDSpec /= 10) > 0);
  char tempStr[values->digits];
  for (int i = values->digits - 1; i >= 0; i--) {
    tempStr[i] = number % 10 + 48;
    number /= 10;
  }
  tempStr[values->digits] = '\0';
  logic_for_to_string(flags, values, tempStr, str, result);
}

void uint_to_str(unsigned int number, char* str, int* result, Flags* flags,
                 Values* values) {
  values->digits = 0;
  if (flags->plus) {
    str[(*result)++] = '+';
  } else if (flags->space) {
    str[(*result)++] = ' ';
  }
  unsigned int tempDSpec = number;
  do {
    values->digits++;
  } while ((tempDSpec /= 10) > 0);
  char tempStr[values->digits];
  for (int i = values->digits - 1; i >= 0; i--) {
    tempStr[i] = number % 10 + 48;
    number /= 10;
  }
  tempStr[values->digits] = '\0';
  logic_for_to_string(flags, values, tempStr, str, result);
}

void str_to_str(char* s, char* str, int* result) {
  for (int index = 0; s[index]; index++) {
    str[(*result)++] = s[index];
  }
}

void double_to_str(double number, Values* values, Flags* flags, char* str,
                   int* result) {
  if (values->widthWithDot > 0) {
    num_to_str((int)number, str, result, flags, values);
    if (number < 0.0) number = -number;
    if ((int)number == 0) number += 1.0;
    str[(*result)++] = '.';
    for (int i = 0; i <= values->widthWithDot; i++) {
      number *= 10.0;
    }
    number += 2;
    int digits = 0;
    int tempDSpec = number;
    do {
      digits++;
    } while ((tempDSpec /= 10) > 0);
    char tempStr[digits];
    for (int i = digits - 1; i >= 0; i--) {
      tempStr[i] = (int)number % 10 + 48;
      number /= 10;
    }
    tempStr[digits] = '\0';
    int tempStrLen = s21_strlen(tempStr) - 1;
    for (int i = values->digits; i < tempStrLen; i++) {
      str[(*result)++] = tempStr[i];
    }
  } else if (values->widthWithDot == 0) {
    num_to_str((int)number, str, result, flags, values);
  }
}

void create_scientific_notation(double number, Values* values) {
  if (number >= 0) {
    while (number >= 10.0) {
      number /= 10.0;
      values->exponent++;
    }
    while (number < 1.0) {
      number *= 10.0;
      values->exponent--;
    }
  }
  values->floatingPointNumber = number;
}

void flags_for_parser(const char* format, int* i, Flags* flags) {
  while (format[*i] == ' ' || format[*i] == '+' || format[*i] == '-' ||
         format[*i] == '#' || format[*i] == '0') {
    switch (format[*i]) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
    }
    (*i)++;
  }
}

void make_width(int width, char* str, int* result, Flags* flags) {
  if (flags->plus) width--;
  if (!flags->zero || flags->minus) {
    while (width > 0) {
      str[(*result)++] = ' ';
      width--;
    }
  } else if (!flags->minus) {
    while (width > 0) {
      str[(*result)++] = '0';
      width--;
    }
  }
}

void num_to_str(int number, char* str, int* result, Flags* flags,
                Values* values) {
  values->digits = 0;
  if (number < 0) {
    str[(*result)++] = '-';
    number = -number;
  } else if (number > 0 && flags->plus) {
    str[(*result)++] = '+';
  } else if (number > 0 && flags->space && !flags->plus) {
    str[(*result)++] = ' ';
  }
  int tempDSpec = number;
  do {
    values->digits++;
  } while ((tempDSpec /= 10) > 0);
  char tempStr[values->digits];
  for (int i = values->digits - 1; i >= 0; i--) {
    tempStr[i] = number % 10 + 48;
    number /= 10;
  }
  tempStr[values->digits] = '\0';
  logic_for_to_string(flags, values, tempStr, str, result);
}

void logic_for_to_string(Flags* flags, Values* values, char* tempStr, char* str,
                         int* result) {
  if (!flags->minus)
    make_width(values->widthWithoutDot - values->digits, str, result, flags);
  int tempStrLen = s21_strlen(tempStr);
  for (int i = 0; i < tempStrLen; i++) {
    str[(*result)++] = tempStr[i];
  }
}

void char_to_str(char symbol, char* str, int* result, Values* values,
                 Flags* flags) {
  flags->zero = 0;
  if (flags->plus) values->widthWithoutDot++;
  if (!flags->minus)
    make_width(values->widthWithoutDot - 1, str, result, flags);
  str[(*result)++] = symbol;
  if (flags->minus) make_width(values->widthWithoutDot - 1, str, result, flags);
}
