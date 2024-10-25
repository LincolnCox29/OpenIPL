#include "errors.h"
#include "stdio.h"

ImgLibErrorInfo imgDataValidation(const unsigned char* data)
{
    return VALIDATE_CONDITION(data == NULL, IMG_LIB_ERROR_LOADING_IMAGE,
        "The specified path may be invalid or the file may not exist. Please check the file path and permissions.\n");
}

ImgLibErrorInfo factorValidation(const float factor)
{
    return VALIDATE_CONDITION(factor < 0, IMG_LIB_ERROR_NEGATIVE_FACTOR,
        "Factor must be non-negative. Please provide a valid value.\n");
}

ImgLibErrorInfo memallocValidation(const unsigned char* imgData)
{
    return VALIDATE_CONDITION(imgData == NULL, IMG_LIB_ERROR_MEMORY_ALLOCATION,
        "Memory allocation failed.");
}