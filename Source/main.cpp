#include <stdio.h>
#include <stdlib.h>

#include "InputOutput.h"

int main()
{
    FILE* file = fopen("t.txt", "r");
    
    char* buff = get_file(file);

    printf("%s\n", buff);

    if (buff) free(buff);

    return 0;
}