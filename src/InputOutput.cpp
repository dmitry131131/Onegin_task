/**
 * @file
 * @brief Input output functions source
*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>

#include "InputOutput.h"

int get_text(const char* const fileName, struct textData* text)
{
    FILE* file = fopen(fileName, "r");
    if (!file) return 1;

    text->bufferSize = get_file_size(file) + 2;

    if (!(text->bufferSize)) return 2;

    text->bufferName = get_file(file, text->bufferSize - 2);

    text->linesCount = char_count(text->bufferName, '\n');

    get_lines(text);

    char_replace(text->bufferName, '\n', '\0');

    return 0;
}

int remove_text(struct textData* text)
{
    text->bufferSize = 0;
    text->linesCount = 0;
    free(text->bufferName);
    free(text->linesPtr);

    return 0;
}

size_t get_file_size(FILE* file)
{
    if (!file) return 0;

    struct stat buff = {};

    if (fstat(fileno(file), &buff)) return 0;

    if (buff.st_size < 0) return 0;

    return buff.st_size;
}

char* get_file(FILE* file, size_t fileSize)
{
    if (!file)
    {
        //printf("No file!\n");
        return NULL;
    }

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

int char_replace(char* buffer, char findSym, char repSym)
{
    if (!buffer) return 1;

    while (*buffer != '\0')
    {
        if (*buffer == findSym)
        {
            *buffer = repSym;
        }

        buffer++;
    }

    return 0;
}

size_t char_count(const char* buffer, char ch)
{
    if (!buffer) 
    {
        return 0;
    }
    size_t count = 0;

    while (*(buffer++) != '\0')
    {
        if (*buffer == ch) count++;
    }
    
    return count;
}

int get_lines(struct textData* text)
{
    text->linesPtr = (char**) calloc(text->linesCount + 1, sizeof(char*));
    if (!text) return 1;

    text->linesPtr[0] = text->bufferName;
    size_t lineNumber = 1;

    for (size_t i = 0; i < text->bufferSize - 1; i++)
    {
        if (text->bufferName[i] == '\n')
        {
            text->linesPtr[lineNumber] = text->bufferName + i + 1;
            lineNumber++;
        }
    }

    return 0;
}

int output_text(const struct textData* text)
{
    assert(1);
    for(size_t i = 0; i < text->linesCount; i++)
    {
        puts(text->linesPtr[i]);
    }

    return 0;
}