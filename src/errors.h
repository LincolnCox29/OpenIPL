#pragma once

typedef enum
{
    OIPL_SUCCESS = 0,
    OIPL_ERROR_LOADING_IMAGE,
    OIPL_ERROR_NEGATIVE_FACTOR,
    OIPL_ERROR_MEMORY_ALLOCATION,
    OIPL_ERROR_UNSUPPORTED_IMAGE_FORMAT,
    OIPL_ERROR_FILE_PATH_DOES_NOT_EXIST
} OpenIPLErrorCode;

typedef struct
{
    OpenIPLErrorCode code;
    const char* message;
} OpenIPLErrorInfo;

#define VALIDATE_CONDITION(condition, errorCode, errorMessage) \
    (condition) ? (OpenIPLErrorInfo) { errorCode, errorMessage } : (OpenIPLErrorInfo) { OIPL_SUCCESS, NULL }

#define SUCCESS (OpenIPLErrorInfo) { OIPL_SUCCESS, NULL }

#define UNSUPPORTED_IMAGE_FORMAT (OpenIPLErrorInfo) { OIPL_ERROR_UNSUPPORTED_IMAGE_FORMAT, "Unsupported image format.\n" }

#define FILE_PATH_DOES_NOT_EXIST (OpenIPLErrorInfo) { OIPL_ERROR_FILE_PATH_DOES_NOT_EXIST, "File path does not have an extension!\n" }

OpenIPLErrorInfo imgDataValidation(const unsigned char* data);
OpenIPLErrorInfo factorValidation(const float factor);
OpenIPLErrorInfo memallocValidation(const unsigned char* imgData);