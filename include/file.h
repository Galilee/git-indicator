#ifndef file_h
#define file_h

#include <stdio.h>

FILE *open_file (char *file_path, char *rights);
void write_file (char *file_path, char *message, char *rights);
char **read_file (char *file_path, int *n);

#endif
