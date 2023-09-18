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

#define RETURN_E_MAIN do{           \
    print_error(stdout, err);       \
    remove_text(&text);             \
    return 0;                       \
} while(0)


#define RETURN_E_FUNC do{           \
    fclose(file);                   \
    return error;                   \
} while(0)


#endif