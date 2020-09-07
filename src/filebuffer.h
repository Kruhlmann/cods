#ifndef FILEBUFFER_H
#define FILEBUFFER_H

#include <stdio.h>

int get_file_size(FILE *file);
char *create_file_buffer(FILE *file, int file_size, int close_file);
char *read_ascii_file(const char *file_path);

#endif
