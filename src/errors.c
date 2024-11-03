#include "errors.h"
#include "stdio.h"

OpenIPLErrorInfo imgDataValidation(const unsigned char* data)
{
    return VALIDATE_CONDITION(data == NULL, OIPL_ERROR_LOADING_IMAGE,
        "The specified path may be invalid or the file may not exist. Please check the file path and permissions.\n");
}

OpenIPLErrorInfo factorValidation(const float factor)
{
    return VALIDATE_CONDITION(factor < 0, OIPL_ERROR_NEGATIVE_FACTOR,
        "Factor must be non-negative. Please provide a valid value.\n");
}

OpenIPLErrorInfo memallocValidation(const unsigned char* imgData)
{
    return VALIDATE_CONDITION(imgData == NULL, OIPL_ERROR_MEMORY_ALLOCATION,
        "Memory allocation failed.\n");
}