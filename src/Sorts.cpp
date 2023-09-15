/**
 * @file
 * @brief Sort functions sources
*/
#include <string.h>

int cmp_strings(const void* a, const void* b)
{
    return strcmp(*(char* const *) a, *(char* const *) b);
}