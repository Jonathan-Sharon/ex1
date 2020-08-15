#include "ErrorCode.h"
#include <stdio.h>

bool error_isSuccess(ErrorCode code) {
    return !code;
}

const char* error_getErrorMessage(ErrorCode code){
    printf("cooler");
    return NULL;
}