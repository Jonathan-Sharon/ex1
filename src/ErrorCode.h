#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    // DON'T CHANGE THIS VALUE!!
    ERROR_SUCCESS = 0,
    ERROR_POINTER_NULL = 1,
    ERROR_ZERO_ROW_OR_COL = 2,
    ERROR_EXCEEDED_ROW_OR_COL = 3,
    ERROR_ALLOCATION_PROBLEM = 4,
    ERROR_MATRIXES_SIZES = 5,
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);