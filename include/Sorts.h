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
/**
 * @brief choice strings sort algoritm
 * @param [in,out] array sorted array
 * @param [in]     count count of lines
*/
void choice_sort(char** array, size_t count);
/**
 * @brief function find minimal element in string array
 * @param [in] array array where we fing min element
 * @param [in] size  size of array
 * @return pointer to min string
 */
char** min_string(char** array, size_t size);
/**
 * @brief Function reverse symbol array
 * @param [in,out] string Symbol array
 * @return pointer to first symbol of reversed symbol
*/
char* str_reverse(char* string);
/**
 * @brief Function compare two reversed strings
 * @param [in] s1 first string
 * @param [in] s2 second string
 * @return 0 if s1 == s2, >0 if s1 > s2, <0 if s1 < s2 
*/
int strcmp_reverse(const char* s1, const char* s2);
/**
 * @brief finction find minimal string in reverse strings array
 * @param [in] array lines array
 * @param [in] size  size of array
 * @return pointer to min string
*/
char** min_string_reverse(char** array, size_t size);
/**
 * @brief choice reverse strings sort algoritm
 * @param [in,out] array sorted array
 * @param [in]     count count of lines
*/
void choice_sort_reverse(char** array, size_t count);