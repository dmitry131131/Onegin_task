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
#endif