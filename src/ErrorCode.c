#include "ErrorCode.h"
#include <stdio.h>

bool error_isSuccess(ErrorCode code) {
    return !code;
}

const char* error_getErrorMessage(ErrorCode code){
    switch(code) {
        case ERROR_SUCCESS: {
            return "success\n";
        }
        case ERROR_POINTER_NULL: {
            return "tried to access or store information inside NULL pointer\n";
            break;
        }
        case ERROR_ZERO_ROW_OR_COL: {
            return "tried to access/create the 0-th row or column\n";
            break;
        }
        case ERROR_EXCEEDED_ROW_OR_COL: {
            return "tried to access rows or columns which are not in the matrix\n";
            break;
        }
        case ERROR_ALLOCATION_PROBLEM: {
            return "Allocation new memory in the progra, failed\n";
            break;
        }
        case ERROR_MATRIXES_SIZES: {
            return "matrices were not able to sum/mult because matrices sizes did not match\n";
            break;
        }
        default: {
            return "\n";
        }

    }
}