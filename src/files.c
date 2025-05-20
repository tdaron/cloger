#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename) {
    FILE* f = fopen(filename, "rb");
    if (!f) return NULL;

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    char* buffer = (char*)malloc(size + 1);
    if (!buffer) {
        fclose(f);
        return NULL;
    }

    if (fread(buffer, 1, size, f) != (size_t)size) {
        fclose(f);
        free(buffer);
        return NULL;
    }

    buffer[size] = '\0';
    fclose(f);
    return buffer;
}

