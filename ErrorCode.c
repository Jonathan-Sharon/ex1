#include "ErrorCode.h"

#include <stdio.h>

bool error_isSuccess(ErrorCode code) {
    printf("cool");
    return false;
}

const char* error_getErrorMessage(ErrorCode code){
    printf("cooler");
    return NULL;
}