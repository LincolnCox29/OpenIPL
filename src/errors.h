#pragma once

typedef enum
{
    IMG_LIB_SUCCESS = 0,
    IMG_LIB_ERROR_LOADING_IMAGE,
    IMG_LIB_ERROR_NEGATIVE_FACTOR,
    IMG_LIB_ERROR_MEMORY_ALLOCATION,
    IMG_LIB_ERROR_UNSUPPORTED_IMAGE_FORMAT,
    IMG_LIB_ERROR_FILE_PATH_DOES_NOT_EXIST
} ImgLibErrorCode;

typedef struct
{
    ImgLibErrorCode code;
    const char* message;
} ImgLibErrorInfo;

#define VALIDATE_CONDITION(condition, errorCode, errorMessage) \
    (condition) ? (ImgLibErrorInfo) { errorCode, errorMessage } : (ImgLibErrorInfo) { IMG_LIB_SUCCESS, NULL }

ImgLibErrorInfo imgDataValidation(const unsigned char* data);
ImgLibErrorInfo factorValidation(const float factor);
ImgLibErrorInfo memallocValidation(const unsigned char* imgData);