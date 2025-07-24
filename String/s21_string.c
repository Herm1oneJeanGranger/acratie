#include "s21_string.h"

#include <stdlib.h>

void *s21_memchr(const void *s, int c, s21_size_t n) {
  const unsigned char *p = s;
  unsigned char uc = c;

  void *result = S21_NULL;

  for (s21_size_t i = 0; i < n; i++) {
    if (p[i] == uc) {
      result = (void *)&p[i];
      break;
    }
  }

  return result;
}

int s21_memcmp(const void *s1, const void *s2, s21_size_t n) {
  const unsigned char *c1 = s1;
  const unsigned char *c2 = s2;

  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (c1[i] != c2[i]) {
      result = (c1[i] - c2[i]);
      break;
    }
  }

  return result;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  const unsigned char *s = (const unsigned char *)src;

  for (size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return d;
};

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *p = (unsigned char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    p[i] = (unsigned char)c;
  }

  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest;

  while (*ptr != '\0') {
    ptr++;
  }

  s21_size_t i;
  for (i = 0; i < n && src[i] != '\0'; i++) {
    ptr[i] = src[i];
  }

  ptr[i] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *result = S21_NULL;

  while (*str != '\0') {
    if (*str == c) {
      result = (char *)str;
      break;
    }
    str++;
  }

  if (c == '\0') {
    result = (char *)str;
  }

  return result;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  const unsigned char *c1 = (const unsigned char *)str1;
  const unsigned char *c2 = (const unsigned char *)str2;

  int result = 0;
  for (s21_size_t i = 0; i < n; i++) {
    if (c1[i] != c2[i]) {
      result = (c1[i] - c2[i]);
      break;
    }
  }

  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *start = dest;

  while (n > 0 && *src != '\0') {
    *dest++ = *src++;
    n--;
  }

  while (n > 0) {
    *dest++ = '\0';
    n--;
  }

  return start;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t count = 0;

  int found = 0;
  for (int i = 0; str1[i] != '\0'; i++) {
    for (int j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        found = 1;
        break;
      }
    }
    if (found) break;
    count++;
  }

  return count;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  while (str[len]) {
    len++;
  }

  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  int i, j;
  int found = 0;
  for (i = 0; str1[i] != '\0'; i++) {
    for (j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        found = 1;
        break;
      }
    }
    if (found) break;
  }

  return found ? (char *)&str1[i] : S21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  const char *found = S21_NULL;

  int i;
  for (i = 0; str[i] != '\0'; i++) {
    if (str[i] == c) {
      found = &str[i];
    }
  }

  if (c == '\0' && str[i] == '\0') {
    found = &str[i];
  }

  return (char *)found;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t needle_len = s21_strlen(needle);
  s21_size_t haystack_len = s21_strlen(haystack);

  if (needle_len > haystack_len) {
    return S21_NULL;
  }

  const char *found = S21_NULL;

  s21_size_t i, j;

  for (i = 0; i <= haystack_len - needle_len; i++) {
    for (j = 0; j < needle_len; j++) {
      if (haystack[i + j] != needle[j]) {
        break;
      }
    }
    if (j == needle_len) {
      found = &haystack[i];
      break;
    }
  }

  return (char *)found;
}

char *s21_strtok(char *dest, const char *delim) {
  static char *s21_strtok_ptr = S21_NULL;
  if (dest == S21_NULL) {
    dest = s21_strtok_ptr;
    s21_strtok_ptr = S21_NULL;
  }
  if (delim != S21_NULL && dest != S21_NULL) {
    s21_strtok_ptr = S21_NULL;
    for (s21_size_t i = 0; dest[i] && s21_strtok_ptr == S21_NULL; i++) {
      if (s21_strchr(delim, (int)dest[i])) {
        if (i == 0) {
          i--;
          dest += 1;
        } else {
          if (dest[i + 1]) s21_strtok_ptr = &dest[i + 1];
          dest[i] = '\0';
        }
      }
    }
  }
  return (*dest) ? dest : S21_NULL;
}

// доп
void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);

  char *lower_str = (char *)malloc((len + 1) * sizeof(char));

  if (lower_str == S21_NULL) {
    // fprintf(stderr, "Memory allocation failed");   ?
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z')
      lower_str[i] = str[i] + 'a' - 'A';
    else
      lower_str[i] = str[i];
  }

  lower_str[len] = '\0';

  return (void *)lower_str;
}

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);

  char *upper_str = (char *)malloc((len + 1) * sizeof(char));

  if (upper_str == S21_NULL) {
    // fprintf(stderr, "Memory allocation failed");    ?
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z')
      upper_str[i] = str[i] + 'A' - 'a';
    else
      upper_str[i] = str[i];
  }

  upper_str[len] = '\0';

  return (void *)upper_str;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (!src || !str) {
    return S21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  s21_size_t whole_len = src_len + str_len;

  if (start_index > src_len) {
    return S21_NULL;
  }

  char *result_str = (char *)malloc((whole_len + 1) * sizeof(char));

  if (!result_str) {
    return S21_NULL;  // error message?
  }

  s21_size_t i;
  s21_size_t j;
  s21_size_t pos = 0;

  for (i = 0; i < src_len; i++) {
    if (i == start_index) {
      for (j = 0; j < str_len; j++) {
        result_str[pos++] = str[j];
      }
    }

    result_str[pos++] = src[i];
  }

  if (start_index == src_len) {
    for (j = 0; j < str_len; j++) {
      result_str[pos++] = str[j];
    }
  }

  result_str[whole_len] = '\0';

  return (void *)result_str;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) {
    return S21_NULL;
  }

  s21_size_t src_len = s21_strlen(src);
  s21_size_t trim_len = s21_strlen(trim_chars);

  // #1 count junk on the end:
  s21_size_t junk_end_count = 0;
  int found_junk = 0;
  for (s21_size_t i = src_len - 1; i > 0; i--) {
    for (size_t j = 0; j < trim_len; j++) {
      if (src[i] == trim_chars[j]) {
        found_junk = 1;
        junk_end_count++;
        break;
      } else {
        found_junk = 0;
      }
    }
    if (!found_junk) break;
  }

  // #2 count junk on the start:
  s21_size_t junk_start_count = 0;
  found_junk = 0;
  for (s21_size_t i = 0; i < src_len; i++) {
    for (size_t j = 0; j < trim_len; j++) {
      if (src[i] == trim_chars[j]) {
        found_junk = 1;
        junk_start_count++;
        break;
      } else {
        found_junk = 0;
      }
    }
    if (!found_junk) break;
  }

  int all_junk = 0;
  if (src_len == junk_start_count || src_len == junk_end_count) {
    all_junk = 1;
  }

  s21_size_t result_len;

  if (!all_junk) {
    result_len = src_len - (junk_start_count + junk_end_count);
  }

  char *result_str;

  if (all_junk) {
    result_str = (char *)malloc(1 * sizeof(char));
  } else {
    result_str = (char *)malloc((result_len + 1) * sizeof(char));
  }

  if (!result_str) {
    return S21_NULL;
  }

  if (!all_junk) {
    s21_size_t pos = 0;
    for (s21_size_t i = junk_start_count; i < src_len - junk_end_count; i++) {
      result_str[pos++] = src[i];
    }

    result_str[pos] = '\0';
  } else {
    result_str[0] = '\0';
  }

  return (void *)result_str;
}

#if defined(__APPLE__)
#define MAX_ERROR 107
#define MIN_ERROR -1
#define ERROR "Unknown error:"
const char *s21_error[] = {"Undefined error: 0",
                           "Operation not permitted",
                           "No such file or directory",
                           "No such process",
                           "Interrupted system call",
                           "Input/output error",
                           "Device not configured",
                           "Argument list too long",
                           "Exec format error",
                           "Bad file descriptor",
                           "No child processes",
                           "Resource deadlock avoided",
                           "Cannot allocate memory",
                           "Permission denied",
                           "Bad address",
                           "Block device required",
                           "Resource busy",
                           "File exists",
                           "Cross-device link",
                           "Operation not supported by device",
                           "Not a directory",
                           "Is a directory",
                           "Invalid argument",
                           "Too many open files in system",
                           "Too many open files",
                           "Inappropriate ioctl for device",
                           "Text file busy",
                           "File too large",
                           "No space left on device",
                           "Illegal seek",
                           "Read-only file system",
                           "Too many links",
                           "Broken pipe",
                           "Numerical argument out of domain",
                           "Result too large",
                           "Resource temporarily unavailable",
                           "Operation now in progress",
                           "Operation already in progress",
                           "Socket operation on non-socket",
                           "Destination address required",
                           "Message too long",
                           "Protocol wrong type for socket",
                           "Protocol not available",
                           "Protocol not supported",
                           "Socket type not supported",
                           "Operation not supported",
                           "Protocol family not supported",
                           "Address family not supported by protocol family",
                           "Address already in use",
                           "Can't assign requested address",
                           "Network is down",
                           "Network is unreachable",
                           "Network dropped connection on reset",
                           "Software caused connection abort",
                           "Connection reset by peer",
                           "No buffer space available",
                           "Socket is already connected",
                           "Socket is not connected",
                           "Can't send after socket shutdown",
                           "Too many references: can't splice",
                           "Operation timed out",
                           "Connection refused",
                           "Too many levels of symbolic links",
                           "File name too long",
                           "Host is down",
                           "No route to host",
                           "Directory not empty",
                           "Too many processes",
                           "Too many users",
                           "Disc quota exceeded",
                           "Stale NFS file handle",
                           "Too many levels of remote in path",
                           "RPC struct is bad",
                           "RPC version wrong",
                           "RPC prog. not avail",
                           "Program version wrong",
                           "Bad procedure for program",
                           "No locks available",
                           "Function not implemented",
                           "Inappropriate file type or format",
                           "Authentication error",
                           "Need authenticator",
                           "Device power is off",
                           "Device error",
                           "Value too large to be stored in data type",
                           "Bad executable (or shared library)",
                           "Bad CPU type in executable",
                           "Shared library version mismatch",
                           "Malformed Mach-o file",
                           "Operation canceled",
                           "Identifier removed",
                           "No message of desired type",
                           "Illegal byte sequence",
                           "Attribute not found",
                           "Bad message",
                           "EMULTIHOP (Reserved)",
                           "No message available on STREAM",
                           "ENOLINK (Reserved)",
                           "No STREAM resources",
                           "Not a STREAM",
                           "Protocol error",
                           "STREAM ioctl timeout",
                           "Operation not supported on socket",
                           "Policy not found",
                           "State not recoverable",
                           "Previous owner died",
                           "Interface output queue is full"};

#elif defined(__linux__)
#define MAX_ERROR 134
#define MIN_ERROR -1
#define ERROR "Unknown error"
const char *s21_error[] = {"Success",
                           "Operation not permitted",
                           "No such file or directory",
                           "No such process",
                           "Interrupted system call",
                           "Input/output error",
                           "No such device or address",
                           "Argument list too long",
                           "Exec format error",
                           "Bad file descriptor",
                           "No child processes",
                           "Resource temporarily unavailable",
                           "Cannot allocate memory",
                           "Permission denied",
                           "Bad address",
                           "Block device required",
                           "Device or resource busy",
                           "File exists",
                           "Invalid cross-device link",
                           "No such device",
                           "Not a directory",
                           "Is a directory",
                           "Invalid argument",
                           "Too many open files in system",
                           "Too many open files",
                           "Inappropriate ioctl for device",
                           "Text file busy",
                           "File too large",
                           "No space left on device",
                           "Illegal seek",
                           "Read-only file system",
                           "Too many links",
                           "Broken pipe",
                           "Numerical argument out of domain",
                           "Numerical result out of range",
                           "Resource deadlock avoided",
                           "File name too long",
                           "No locks available",
                           "Function not implemented",
                           "Directory not empty",
                           "Too many levels of symbolic links",
                           "Unknown error 41",
                           "No message of desired type",
                           "Identifier removed",
                           "Channel number out of range",
                           "Level 2 not synchronized",
                           "Level 3 halted",
                           "Level 3 reset",
                           "Link number out of range",
                           "Protocol driver not attached",
                           "No CSI structure available",
                           "Level 2 halted",
                           "Invalid exchange",
                           "Invalid request descriptor",
                           "Exchange full",
                           "No anode",
                           "Invalid request code",
                           "Invalid slot",
                           "Unknown error 58",
                           "Bad font file format",
                           "Device not a stream",
                           "No data available",
                           "Timer expired",
                           "Out of streams resources",
                           "Machine is not on the network",
                           "Package not installed",
                           "Object is remote",
                           "Link has been severed",
                           "Advertise error",
                           "Srmount error",
                           "Communication error on send",
                           "Protocol error",
                           "Multihop attempted",
                           "RFS specific error",
                           "Bad message",
                           "Value too large for defined data type",
                           "Name not unique on network",
                           "File descriptor in bad state",
                           "Remote address changed",
                           "Can not access a needed shared library",
                           "Accessing a corrupted shared library",
                           ".lib section in a.out corrupted",
                           "Attempting to link in too many shared libraries",
                           "Cannot exec a shared library directly",
                           "Invalid or incomplete multibyte or wide character",
                           "Interrupted system call should be restarted",
                           "Streams pipe error",
                           "Too many users",
                           "Socket operation on non-socket",
                           "Destination address required",
                           "Message too long",
                           "Protocol wrong type for socket",
                           "Protocol not available",
                           "Protocol not supported",
                           "Socket type not supported",
                           "Operation not supported",
                           "Protocol family not supported",
                           "Address family not supported by protocol",
                           "Address already in use",
                           "Cannot assign requested address",
                           "Network is down",
                           "Network is unreachable",
                           "Network dropped connection on reset",
                           "Software caused connection abort",
                           "Connection reset by peer",
                           "No buffer space available",
                           "Transport endpoint is already connected",
                           "Transport endpoint is not connected",
                           "Cannot send after transport endpoint shutdown",
                           "Too many references: cannot splice",
                           "Connection timed out",
                           "Connection refused",
                           "Host is down",
                           "No route to host",
                           "Operation already in progress",
                           "Operation now in progress",
                           "Stale file handle",
                           "Structure needs cleaning",
                           "Not a XENIX named type file",
                           "No XENIX semaphores available",
                           "Is a named type file",
                           "Remote I/O error",
                           "Disk quota exceeded",
                           "No medium found",
                           "Wrong medium type",
                           "Operation canceled",
                           "Required key not available",
                           "Key has expired",
                           "Key has been revoked",
                           "Key was rejected by service",
                           "Owner died",
                           "State not recoverable",
                           "Operation not possible due to RF-kill",
                           "Memory page has hardware error"};
#endif

char *s21_strerror(int errnum) {
  char *result = 0;
  if (MIN_ERROR < errnum && errnum < MAX_ERROR) {
    result = (char *)s21_error[errnum];
  } else {
    static char result_arr[100] = {0};
    s21_sprintf(result_arr, "%s %d", ERROR, errnum);
    result = result_arr;
  }
  return result;
}
