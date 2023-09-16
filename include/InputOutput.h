/**
 * @file
 * @brief Input output functions
*/

/// @brief text struct with data about text
struct textData {
    size_t bufferSize;  ///< Size of text buffer
    size_t linesCount;  ///< Count of lines in text
    char*  bufferName;  ///< Name of buffer
    char** linesPtr;    ///< Name of lines array
};
/**
 * @brief Function find size of file
 * @param [in] file pointer to file
 * @return size of file
*/
size_t get_file_size(FILE* file);
/**
 * @brief Input text from file
 * @param [in] file     pointer to file
 * @param [in] fileSize size of file
 * @return pointer to text buffer
*/
char* get_file(FILE* file, size_t fileSize);
/**
 * @brief Function counts number of occurrences ch in buffer
 * @param [in] buffer text line
 * @param [in] ch     char
 * @return number of occurrences ch in buffer
*/
size_t char_count(const char* buffer, char ch);
/**
 * @brief function cut buffer on lines
 * @param [in,out] text text struct
*/
int get_lines(struct textData* text);

int remove_text(struct textData* text);

int get_text(const char* const fileName, struct textData* text);

int char_replace(char* buffer, char findSym, char repSym);

int output_text(const struct textData* text);