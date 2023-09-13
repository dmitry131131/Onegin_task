#include <stdio.h>
#include <stdlib.h>

#include "InputOutput.h"

int main()
{
    struct textData text = {};

    get_text("t.txt", &text);

    printf("%s\n", text.linesPtr[1]);

    remove_text(&text);

    return 0;
}