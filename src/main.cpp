#include <stdio.h>
#include <stdlib.h>

#include "InputOutput.h"
#include "Sorts.h"

int main()
{
    struct textData text = {};

    get_text("t.txt", &text);

    output_text(&text);

    choice_sort(text.linesPtr, text.linesCount);

    printf("\n");

    output_text(&text);

    remove_text(&text);

    return 0;
}