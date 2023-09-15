/**
 * @file
 * @brief Sort functions sources
*/
#include <string.h>

#include "Sorts.h"


void choice_sort(char** array, size_t count)
{
    char* temp     = NULL;
    char** min_ptr = NULL;

    for (size_t i = 0; i < count; i++)
    {
        temp = *(array + i);
        min_ptr = min_string(array + i, count - i);

        *(array + i) = *min_ptr;
        *min_ptr     = temp;
    }
}

char** min_string(char** array, size_t size)
{
    char** min = array;
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp(array[i], *min) < 0)
        {
            min = array + i;
        }
    }

    return min;
}


int cmp_strings(const void* firstStr, const void* secondStr)
{
    return strcmp(*(char* const *) firstStr, *(char* const *) secondStr);
}