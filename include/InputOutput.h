/**
 * @file
 * @brief Input output functions
*/
#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

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
size_t get_file_size(FILE* file, enum errorCode* errorPtr = NULL);
/**
 * @brief Input text from file
 * @param [in] file     pointer to file
 * @param [in] fileSize size of file
 * @return pointer to text buffer
*/
char* get_file(FILE* file, struct textData* text, enum errorCode* errorPtr = NULL);
/**
 * @brief Function counts number of occurrences ch in buffer
 * @param [in] buffer text line
 * @param [in] ch     char
 * @return number of occurrences ch in buffer
*/
size_t char_count(const struct textData* text, char ch, enum errorCode* errorPtr = NULL);
/**
 * @brief function cut buffer on lines
 * @param [in,out] text text struct
*/
enum errorCode get_lines(struct textData* text);
/**
 * @brief Function free alloced memory and clean text struct
 * @param [in,out] text text struct
 * @return Error code
*/
enum errorCode remove_text(struct textData* text);
/**
 * @brief Function open file and read it in text struct
 * @param [in]  fileName file name
 * @param [out] text text struct
 * @return Error code
*/
enum errorCode get_text(const char* const fileName, struct textData* text);
/**
 * @brief Function replace chars in buffer
 * @param [out] buffer  text buffer
 * @param [in]  findSym replaced value
 * @param [in]  repSym  target value
 * @return Error code
*/
enum errorCode char_replace(char* buffer, char findSym, char repSym);
/**
 * @brief Function output text
 * @param [in] text text struct
 * @return Error code 
*/
enum errorCode output_text(const struct textData* text);
/**
 * @brief Function print error value
 * @param [in] stream output stream
 * @param [in] error  error code
*/
void print_error(FILE* stream, enum errorCode error);
/**
 * @brief Function print text buffer
 * @param [in] text text buffer
 * @return Error code
*/
enum errorCode print_buffer(const struct textData* text);

#endif