/**
 * @file
 * @brief Input output functions source
*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "InputOutput.h"

size_t get_file_size(FILE* file)
{
    if (!file) return 0;

    struct stat buff = {};

    if (fstat(fileno(file), &buff)) return 0;

    if (buff.st_size < 0) return 0;

    return buff.st_size;
}

char* get_file(FILE* file)
{
    if (!file)
    {
        //printf("No file!\n");
        return NULL;
    }

    size_t fileSize = get_file_size(file);

    if (!fileSize)
    {
        //printf("File size in 0!\n");
        return NULL;
    }

    char* buffer = (char*) calloc(fileSize + 2, sizeof(char));
    if (!buffer)
    {
        //printf("Can't alloc the memory!\n");
        return NULL;
    }

    fread(buffer, sizeof(char), fileSize + 1, file);

    if (ferror(file))
    {
        //printf("Error in file!\n");
        free(buffer);
        return NULL;
    }

    if (feof(file))
    {
        buffer[fileSize] = '\n';
        return buffer;
    }

    free(buffer);
    return NULL;
}

size_t line_count(const char* buffer)
{
    if (!buffer) 
    {
        return 0;
    }
    size_t count = 0;

    while (*(buffer++) != '\0')
    {
        if (*buffer == '\n') count++;
    }
    
    return count;
}