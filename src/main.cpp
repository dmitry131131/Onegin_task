#include <stdio.h>
#include <stdlib.h>

#include "Error.h"
#include "InputOutput.h"
#include "Sorts.h"

int main()
{
    struct textData text = {};
    enum errorCode err = NO_ERRORS;

    CHECK_ERR_MAIN(get_text("t.txt", &text));
 
    CHECK_ERR_MAIN(output_text(&text));

    CHECK_ERR_MAIN(choice_sort(text.linesPtr, text.linesCount));

    printf("\n");

    CHECK_ERR_MAIN(output_text(&text));

    printf("\n");

    CHECK_ERR_MAIN(choice_sort_reverse(text.linesPtr, text.linesCount));

    CHECK_ERR_MAIN(output_text(&text));

    printf("\n");

    CHECK_ERR_MAIN(print_buffer(&text));

    print_error(stdout, err);
    remove_text(&text);

    return 0;
}