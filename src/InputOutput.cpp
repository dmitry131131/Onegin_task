/**
 * @file
 * @brief Input output functions source
*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <assert.h>

#include "Error.h"
#include "InputOutput.h"

enum errorCode get_text(const char* const fileName, struct textData* text)
{
    FILE* file = fopen(fileName, "r");
    if (!file) return FILE_NOT_OPENED;

    enum errorCode error = NO_ERRORS;
    text->bufferSize = get_file_size(file, &error) + 2;

    if (error) return error;

    text->bufferName = get_file(file, text->bufferSize - 2, &error);

    if (error) return error;

    text->linesCount = char_count(text->bufferName, '\n', &error);

    if (error) return error;

    error = get_lines(text);

    if (error) return error;

    error = char_replace(text->bufferName, '\n', '\0');

    if (error) return error;

    return NO_ERRORS;
}

enum errorCode remove_text(struct textData* text)
{
    if (!text) return NO_TEXT_STRUCT;

    text->bufferSize = 0;
    text->linesCount = 0;
    free(text->bufferName);
    free(text->linesPtr);

    return NO_ERRORS;
}

size_t get_file_size(FILE* file, enum errorCode* errorPtr = NULL)
{
    if (!file)
    {
        if (!errorPtr) *errorPtr = FILE_NOT_OPENED;
        return 0;
    }

    struct stat buff = {};

    if (fstat(fileno(file), &buff))
    {
        if (!errorPtr) *errorPtr = FILE_BAD_DESCRIPTOR;
        return 0;
    }

    if (buff.st_size < 0) return 0;

    return buff.st_size;
}

char* get_file(FILE* file, size_t fileSize, enum errorCode* errorPtr = NULL)
{
    if (!file)
    {
        if (!errorPtr) *errorPtr = FILE_NOT_OPENED;
        return NULL;
    }

    if (!fileSize)
    {
        if (!errorPtr) *errorPtr = FILE_SIZE_ZERO;
        return NULL;
    }

    char* buffer = (char*) calloc(fileSize + 2, sizeof(char));
    if (!buffer)
    {
        if (!errorPtr) *errorPtr = NO_MEMORY;
        return NULL;
    }

    fread(buffer, sizeof(char), fileSize + 1, file);

    if (ferror(file))
    {
        if (!errorPtr) *errorPtr = ERROR_IN_FILE;
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

enum errorCode char_replace(char* buffer, char findSym, char repSym)
{
    if (!buffer)
    {
        return NO_BUFFER;
    }

    while (*buffer != '\0')
    {
        if (*buffer == findSym)
        {
            *buffer = repSym;
        }

        buffer++;
    }

    return NO_ERRORS;
}

size_t char_count(const char* buffer, char ch, enum errorCode* errorPtr = NULL)
{
    if (!buffer) 
    {
        if (!errorPtr) *errorPtr = NO_BUFFER;
        return 0;
    }
    
    size_t count = 0;

    while (*(buffer++) != '\0')
    {
        if (*buffer == ch) count++;
    }
    
    return count;
}

enum errorCode get_lines(struct textData* text)
{
    if (!text) return NO_TEXT_STRUCT;

    text->linesPtr = (char**) calloc(text->linesCount + 1, sizeof(char*));

    if (!text->linesPtr) return NO_MEMORY;

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

    return NO_ERRORS;
}

enum errorCode output_text(const struct textData* text)
{
    if (!text) return NO_TEXT_STRUCT;

    for(size_t i = 0; i < text->linesCount; i++)
    {
        puts(text->linesPtr[i]);
    }

    return NO_ERRORS;
}