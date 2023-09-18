#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "InputOutput.h"
#include "Sorts.h"

int main()
{
    struct textData text = {};
    enum errorCode err = NO_ERRORS;
    do{

        err = get_text("t.txt", &text);

        if (err) break;

        err = output_text(&text);

        if (err) break;

        choice_sort(text.linesPtr, text.linesCount);

        printf("\n");

        err = output_text(&text);

        if (err) break;

        printf("\n");

        choice_sort_reverse(text.linesPtr, text.linesCount);

        err = output_text(&text);

        if (err) break;

    } while(0);

    print_error(stdout, err);
    
    remove_text(&text);

    return 0;
}