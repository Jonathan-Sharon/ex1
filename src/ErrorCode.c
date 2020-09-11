#include "ErrorCode.h"
#include <stdio.h>

bool error_isSuccess(const ErrorCode code) {
    return code == ERROR_SUCCESS;
}

const char* error_getErrorMessage(const ErrorCode code){
    switch(code) {
        case ERROR_SUCCESS: {
            return "success\n";
        }
        case ERROR_NULL_POINTER: {
            return "tried to access or store information inside NULL pointer\n";
        }
        case ZERO_ROW_OR_COLUMNS: {
            return "tried to access/create the 0-th row or column\n";
        }
        case EXCEEDED_ROW_OR_COLUMNS: {
            return "tried to access rows or columns which are not in the matrix\n";
        }
        case ALLOCATION_PROBLEM: {
            return "Allocation new memory in the progra, failed\n";
        }
        case ERROR_MATRIXES_SIZES: {
            return "matrices were not able to sum/mult because matrices sizes did not match\n";
        }
        default: {
            return "unknown error\n";
        }

    }
}