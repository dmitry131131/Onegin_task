/**
 * @file
 * @brief Error handling functions structs and enums
*/
#ifndef ERROR_H
#define ERROR_H

enum errorCode {
    NO_ERRORS,
    FILE_NOT_OPENED,
    FILE_BAD_DESCRIPTOR,
    FILE_SIZE_ZERO,
    NO_MEMORY,
    ERROR_IN_FILE,
    NO_BUFFER,
    NO_TEXT_STRUCT
};

#define CHECK_ERR_MAIN(code) do{            \
    err = code;                             \
                                            \
    if (err)                                \
    {                                       \
        print_error_message(stdout, err);   \
        remove_text(&text);                 \
        return 0;                           \
    }                                       \
} while(0)


#define CHECK_ERR_FUNC(code) do{    \
    enum errorCode err = code;      \
                                    \
    if (err)                        \
    {                               \
        fclose(file);               \
        return error;               \
    }                               \
} while(0)

/**
 * @brief Function print error value
 * @param [in] stream output stream
 * @param [in] error  error code
*/
void print_error_message(FILE* stream, enum errorCode error);


#endif