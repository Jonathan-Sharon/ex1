#include "Matrix.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct Matrix
{
    //fields
    uint32_t height;
    uint32_t width;
    double** values;
}Matrix;


ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width){

    //if the matrix pointer is set to null return the NULL Pointer Error
    if(matrix == NULL) {
        return ERROR_POINTER_NULL;
    }

    //If the row or the col we were given equal to zero, then create that
    //that specific error
    if (height == 0 || width == 0){
        return ERROR_ZERO_ROW_OR_COL;
    }

    //Allocate a new memory for the matrix
    *matrix = (PMatrix)malloc(sizeof(Matrix));

    //If the allocation was unsuccessful, return that kind of error
    if (*matrix == NULL) {
        return ERROR_ALLOCATION_PROBLEM;
    }

    //Put the parameters in the matrix's fields
    (*matrix)->height = height;
    (*matrix)->width = width;
    //Allocate a new memory for the values
    (*matrix)->values = (double**)malloc(height * sizeof(double*));

    //If the allocation was unsuccessful, return that kind of error,
    //and free what we have already allocated
    if((*matrix)->values == NULL) {
        free(*matrix);
        return ERROR_ALLOCATION_PROBLEM;
    }

    //initial values to zero
    for(uint32_t i = 0; i < height; i++) {
        //Allocate memory
        (*matrix)->values[i] = (double*)calloc(width, sizeof(double));

        //free what we have already allocated
        if((*matrix)->values[i] == NULL) {
            for(uint32_t j = 0; j < i; j++) {
                free((*matrix)->values[j]);
            }

            free((*matrix)->values);
            free(*matrix);
            return ERROR_ALLOCATION_PROBLEM;

        }
    }

    return ERROR_SUCCESS;
}


ErrorCode matrix_copy(PMatrix* result, CPMatrix source){
    
    //check if there isn't an NULL pointer error
    if(source == NULL || result == NULL) {
        return ERROR_POINTER_NULL;
    }

    //Create a new matrix, in order to create deep copy
    ErrorCode error = matrix_create(result, source->height, source->width);
    if(error != ERROR_SUCCESS) {
        return error;
    }

    //Deep Copy
    for (uint32_t i = 0; i < (*result)->height; i++) {
        for (uint32_t j = 0; j < (*result)->width; i++) {
            (*result)->values[i][j] = source->values[i][j];
        }
    }

    return ERROR_SUCCESS;
}


/**
 * @brief Destroys a matrix.
 *
 * @param matrix the matrix to destroy.
 */
void matrix_destroy(PMatrix matrix){
    //If the matrix is null, then return
    if (matrix == NULL) {
        return;
    }
    
    //free
    for(uint32_t i = 0; i < matrix->height; i++) {
        free(matrix->values[i]);
    }

    //free
    free(matrix->values);
    free(matrix);
}




ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    //if the matrix or the result pointer are null return the NULL Pointer Error
    if (matrix == NULL || result == NULL) {
        return ERROR_POINTER_NULL;
    }

    //There are no Errors, so change the value of return to the matrix's height
    *result = matrix->height;
    return ERROR_SUCCESS;

}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result){
    //if the matrix or the result pointer are null return the NULL Pointer Error
    if (matrix == NULL || result == NULL) {
        return ERROR_POINTER_NULL;
    }


    //There are no Errors, so change the value of return to the matrix's height
    *result = matrix->width;
    return ERROR_SUCCESS;
}


ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value){

    //if the matrix pointer is set to null return the NULL Pointer Error
    if(matrix == NULL) {
        return ERROR_POINTER_NULL;
    }

    //If the row or the col we were given equal to zero, then create that
    //that specific error 
    if (rowIndex == 0 || colIndex == 0) {
        return ERROR_ZERO_ROW_OR_COL;
    }

    //if the row or the col we were given exceeds the size of the matrix,
    //then create the appropriate error.
    if(rowIndex > matrix->height || colIndex > matrix->width) {
        return ERROR_EXCEEDED_ROW_OR_COL;
    }

    //Else, everything is good, and set the value
    matrix->values[rowIndex - 1][colIndex - 1] = value;
    return ERROR_SUCCESS;
    
}


ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value){

    //if the matrix or the value pointer are null return the NULL Pointer Error
    if (matrix == NULL || value == NULL) {
        return ERROR_POINTER_NULL;
    }

    //If the row or the col we were given equal to zero, then create that
    //that specific error 
    if (rowIndex == 0 || colIndex == 0) {
        return ERROR_ZERO_ROW_OR_COL;
    }

    //if the row or the col we were given exceeds the size of the matrix,
    //then create the appropriate error.
    if(rowIndex > matrix->height || colIndex > matrix->width) {
        return ERROR_EXCEEDED_ROW_OR_COL;
    }

    //Else, everything is good, and get the value
    *value = matrix->values[rowIndex - 1][colIndex - 1];
    return ERROR_SUCCESS;

 }


ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    //If one of those equals to num, then a pointer error will be returned
    if (result == NULL || lhs == NULL || rhs == NULL) {
        return ERROR_POINTER_NULL;
    }

    //if the matrixes have different sizes, than create an error.
    if (lhs->height != rhs->height || lhs->width != rhs->width) {
        return ERROR_MATRIXES_SIZES;
    }

    //Create the new matrix
    ErrorCode error = matrix_create(result, rhs->height, rhs->width);
    if (error != ERROR_SUCCESS) {
        return error;
    }

    //Add both matrixes
    for(uint32_t i = 0; i < rhs->height; i++) {
        for(uint32_t j = 0; j < rhs->width; j++) {
            double xl = lhs->values[i][j];
            double xr = rhs->values[i][j];

            (*result)->values[i][j] = xl + xr;
        }
    }

    return ERROR_SUCCESS;
}


ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    //If one of those equals to num, then a pointer error will be returned
    if (result == NULL || lhs == NULL || rhs == NULL) {
        return ERROR_POINTER_NULL;
    }

    //if the matrixes have different sizes, than create an error.
    if (lhs->width != rhs->height) {
        return ERROR_MATRIXES_SIZES;
    }

    //Create the new matrix
    ErrorCode error = matrix_create(result, lhs->height, rhs->width);
    if (error != ERROR_SUCCESS) {
        return error;
    }

    //multiplication
    for(uint32_t i = 0; i < lhs->height; i++) {
        for(uint32_t j = 0; j < rhs->width; j++) {
            for (uint32_t z = 0; z < lhs->width; z++) {
                //In matrix multiplication first matrix one row element is multiplied
                // by second matrix all column elements.
                double xl = lhs->values[i][z];
                double xr = rhs->values[z][j];
                (*result)->values[i][j] += xl * xr;
            }
        }
    }
    return ERROR_SUCCESS;
}


ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar){
    //If matrix equals to null, then a pointer error will be returned
    if (matrix == NULL) {
        return ERROR_POINTER_NULL;
    }

    //multiplay a matrix with a scalar, and store the result in the given matrix.
    for(uint32_t i = 0; i < matrix->height; i++) {
        for(uint32_t j = 0; j < matrix->width; j++) {
            matrix->values[i][j] = scalar * matrix->values[i][j];
        }
    }

    return ERROR_SUCCESS;

}

