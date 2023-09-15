/**
 * @file
 * @brief Sort functions
*/

/**
 * @brief Comparator for strings
 * @param [in] firstStr  First string
 * @param [in] secondStr Second string
*/
int cmp_strings(const void* firstStr, const void* secondStr);

void choice_sort(char** array, size_t count);

char** min_string(char** array, size_t size);

char* str_reverse(char* string);

int strcmp_reverse(const char* s1, const char* s2);

char** min_string_reverse(char** array, size_t size);

void choice_sort_reverse(char** array, size_t count);