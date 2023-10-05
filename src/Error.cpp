#include <stdio.h>
#include <stdlib.h>

#include "OneginError.h"
#include "Color_output.h"

void print_error_message(FILE* stream, enum errorCode error)
{
    switch (error)
    {
    case NO_ERRORS:
        break;

    case FILE_NOT_OPENED:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "File not opened!\n");
        break;
    
    case FILE_BAD_DESCRIPTOR:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "File bad descriptor!\n");
        break;
    
    case FILE_SIZE_ZERO:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "File size is zero!\n");
        break;

    case NO_MEMORY:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "Can't alloc memory!\n");
        break;

    case ERROR_IN_FILE:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "File had opened, but found error in file!\n");
        break;

    case NO_BUFFER:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "No buffer or buffer pointer is NULL!\n");
        break;

    case NO_TEXT_STRUCT:
        color_fprintf(stream, COLOR_RED, STYLE_BOLD, "Error: ");
        fprintf(stream, "No text struct or text pointer is NULL!\n");
        break;

    default:
        break;
    }
}