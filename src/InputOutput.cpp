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
#include "Color_output.h"

enum errorCode get_text(const char* const fileName, struct textData* text)
{
    FILE* file = fopen(fileName, "r");
    if (!file) return FILE_NOT_OPENED;

    if (!text) return NO_TEXT_STRUCT;

    enum errorCode error = NO_ERRORS;

    text->bufferSize = get_file_size(file, &error) + 2;

    CHECK_ERR_FUNC(error);

    text->bufferName = get_file(file, text, &error);

    CHECK_ERR_FUNC(error);

    text->linesCount = char_count(text, '\n', &error);

    CHECK_ERR_FUNC(error);

    CHECK_ERR_FUNC(get_lines(text));

    error = char_replace(text->bufferName, '\n', '\0');

    fclose(file);
    return error;
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

size_t get_file_size(FILE* file, enum errorCode* errorPtr)
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

char* get_file(FILE* file, struct textData* text, enum errorCode* errorPtr)
{
    if (!text)
    {
        if (!errorPtr) *errorPtr = NO_TEXT_STRUCT;
        return NULL;
    }

    char* buffer = (char*) calloc(text->bufferSize + 2, sizeof(char));
    if (!buffer)
    {
        if (!errorPtr) *errorPtr = NO_MEMORY;
        return NULL;
    }

    text->bufferSize = fread(buffer, sizeof(char), text->bufferSize + 1, file) + 1;

    if (ferror(file))
    {
        if (!errorPtr) *errorPtr = ERROR_IN_FILE;
        free(buffer);
        return NULL;
    }

    if (feof(file))
    {
        buffer[text->bufferSize] = '\n';
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

size_t char_count(const struct textData* text, char ch, enum errorCode* errorPtr)
{
    if (!text) 
    {
        if (!errorPtr) *errorPtr = NO_TEXT_STRUCT;
        return 0;
    }

    if (!text->bufferName)
    {
        if (!errorPtr) *errorPtr = NO_BUFFER;
        return 0;
    }
    
    size_t count = 0;

    for (size_t i = 0; i < text->bufferSize; i++)
    {
        if (text->bufferName[i] == ch) count++;
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

    for(size_t i = 0; i < text->linesCount + 1; i++)
    {
        puts(text->linesPtr[i]);
    }

    return NO_ERRORS;
}

enum errorCode print_buffer(const struct textData* text)
{
    if (!text) return NO_TEXT_STRUCT;

    for (size_t i = 0; i < text->bufferSize; i++)
    {
        if (text->bufferName[i] == '\0')
        {
            putchar('\n');
            continue;
        }
        putchar(text->bufferName[i]);
    }

    return NO_ERRORS;
}
