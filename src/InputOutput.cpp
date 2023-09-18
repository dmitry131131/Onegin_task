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

    enum errorCode error = NO_ERRORS;
    do{
        text->bufferSize = get_file_size(file, &error) + 2;

        if (error) break;

        text->bufferName = get_file(file, text->bufferSize - 2, &error);

        if (error) break;

        text->linesCount = char_count(text->bufferName, '\n', &error);

        if (error) break;

        error = get_lines(text);

        if (error) break;

        error = char_replace(text->bufferName, '\n', '\0');

    } while(0);

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

void print_error(FILE* stream, enum errorCode error)
{
    switch (error)
    {
    case NO_ERRORS:
        break;

    case FILE_NOT_OPENED:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "File not opened!\n");
        break;
    
    case FILE_BAD_DESCRIPTOR:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "File bad descriptor!\n");
        break;
    
    case FILE_SIZE_ZERO:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "File size is zero!\n");
        break;

    case NO_MEMORY:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "Can't alloc memory!\n");
        break;

    case ERROR_IN_FILE:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "File had opened, but found error in file!\n");
        break;

    case NO_BUFFER:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "No buffer or buffer pointer is NULL!\n");
        break;

    case NO_TEXT_STRUCT:
        color_fprintf(COLOR_RED, STYLE_BOLD, stream, "Error: ");
        fprintf(stream, "No text struct or text pointer is NULL!\n");
        break;

    default:
        break;
    }
}