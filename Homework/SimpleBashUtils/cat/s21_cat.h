#ifndef S21_CAT_H
#define S21_CAT_H
#define MAX_FILES 100
#define MAX_LINE_LENGTH 4096

typedef struct {
  int pN;
  int pB;
  int pS;
  int pV;
  int pE;
  int pT;
} Flags;

Flags process_flags(int argc, char **argv);
void Cat_func(const char *fileNames[MAX_FILES], Flags flags, int fileCount);

#endif
