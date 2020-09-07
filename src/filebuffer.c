#include "ttt.h"
#include <stdio.h>
#include <stdlib.h>

int get_file_size(FILE *file) {
    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fseek(file, 0, SEEK_SET);
    return size;
}

char *create_file_buffer(FILE *file, int file_size, int close_file) {
    char *file_buffer = (char *)malloc(sizeof(char) * (file_size + 1));
    fread(file_buffer, sizeof(char), file_size, file);
    if (close_file) {
        fclose(file);
    }
    return file_buffer;
}

char *read_ascii_file(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        printf("Error loading file '%s'\n", file_path);
        return NULL;
    }

    int file_size = get_file_size(file);
    char *file_buffer = create_file_buffer(file, file_size, 1);
    file_buffer[file_size] = '\0';

    return file_buffer;
}
