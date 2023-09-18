/**
 * @file
 * @brief Sort functions sources
*/
#include <string.h>
#include <stdlib.h>

#include "Error.h"
#include "Sorts.h"


enum errorCode choice_sort(char** array, size_t count)
{
    if (!array) return NO_BUFFER;

    char* temp     = NULL;
    char** min_ptr = NULL;

    for (size_t i = 0; i < count; i++)
    {
        temp = *(array + i);
        min_ptr = min_string(array + i, count - i);

        if (!min_ptr) return NO_BUFFER;

        array[i] = *min_ptr;
        *min_ptr = temp;
    }

    return NO_ERRORS;
}

enum errorCode choice_sort_reverse(char** array, size_t count)
{
    if (!array) return NO_BUFFER;

    char* temp     = NULL;
    char** min_ptr = NULL;

    for (size_t i = 0; i < count; i++)
    {
        temp = *(array + i);
        min_ptr = min_string_reverse(array + i, count - i);

        if (!min_ptr) return NO_BUFFER;

        *(array + i) = *min_ptr;
        *min_ptr     = temp;
    }

    return NO_ERRORS;
}

char** min_string(char** array, size_t size)
{
    if (!array) return NULL;

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

char** min_string_reverse(char** array, size_t size)
{
    if (!array) return NULL;

    char** min = array;
    for (size_t i = 0; i < size; i++)
    {
        if (strcmp_reverse(array[i], *min) < 0)
        {
            min = array + i;
        }
    }

    return min;
}

int strcmp_reverse(const char* s1, const char* s2)
{
    char* s1Rev = strdup(s1);
    char* s2Rev = strdup(s2);
    int res = 0;

    str_reverse(s1Rev);
    str_reverse(s2Rev);

    res = strcmp(s1Rev, s2Rev);

    free(s1Rev);
    free(s2Rev);

    return res;
}

char* str_reverse(char* string)
{
    if (!string) return NULL;
    
    char* str = string;
    size_t size = strlen(string);

    char temp = '\0';
    for (size_t i = 0; i < (size / 2); i++)
    {
        temp = string[i];
        string[i] = string[size - (1+i)];
        string[size - (1+i)] = temp;
    }

    return str;
}

int cmp_strings(const void* firstStr, const void* secondStr)
{
    return strcmp(*(char* const *) firstStr, *(char* const *) secondStr);
}