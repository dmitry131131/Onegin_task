#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "InputOutput.h"
#include "Sorts.h"

int main()
{
    struct textData text = {};
    enum errorCode err = NO_ERRORS;

    err = get_text("t.txt", &text);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    err = output_text(&text);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    err = choice_sort(text.linesPtr, text.linesCount);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    printf("\n");

    err = output_text(&text);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    printf("\n");

    err = choice_sort_reverse(text.linesPtr, text.linesCount);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    err = output_text(&text);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    printf("\n");

    err = print_buffer(&text);

    if (err) 
    {
        RETURN_E_MAIN;
    }

    print_error(stdout, err);
    remove_text(&text);

    return 0;
}