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
    size_t len1 = 0, len2 = 0, min = 0;

    while (*s1 != '\0')
    {
        len1++;
        s1++;
    }
    s1--;

    while (*s2 != '\0')
    {
        len2++;
        s2++;
    }
    s2--;

    if (len1 < len2) min = len1;
    else min = len2;

    for (size_t i = 0; i < min; i++)
    {
        if (*s1 < *s2) return -1;
        if (*s1 > *s2) return 1;
        s1--;
        s2--;
    }

    if (len1 > len2) return 1;
    else if (len1 < len2) return -1;

    return 0;
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