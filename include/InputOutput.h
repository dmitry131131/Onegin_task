/**
 * @file
 * @brief Input output functions
*/

struct textData {
    size_t bufferSize;
    size_t linesCount;
    char*  bufferName;
    char** linesPtr;
};

size_t get_file_size(FILE* file);

char* get_file(FILE* file, size_t fileSize);

size_t char_count(const char* buffer, char ch);

int get_lines(struct textData* text);

int remove_text(struct textData* text);

int get_text(const char* const fileName, struct textData* text);

int char_replace(char* buffer, char findSym, char repSym);

int output_text(const struct textData* text);