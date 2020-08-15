#include "Matrix.h"

typedef struct Matrix
{
    /* data */
    uint32_t height;
    uint32_t width;
    double** values;
}Matrix;

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    //if the matrix is null return the matching Error
    if (matrix == NULL) {
        return ERROR_POINTER_NULL;
    }

    //if the return pointer is null return the matching Error
    if (result == NULL) {
        return ERROR_POINTER_NULL;
    }

    //There are no Errors, so change the value of return to the matrix's height
    *result = matrix->height;
    return ERROR_SUCCESS;

}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result){
    //if the matrix is null return the matching Error
    if (matrix == NULL) {
        return ERROR_POINTER_NULL;
    }

    //If the return pointer is null return the matching Error
    if (result == NULL) {
        return ERROR_POINTER_NULL;
    }

    //There are no Errors, so change the value of return to the matrix's height
    *result = matrix->width;
    return ERROR_SUCCESS;
}