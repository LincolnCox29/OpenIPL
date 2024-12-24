#pragma once

#include <stdio.h>

typedef enum
{
    OIPL_SUCCESS = 0,
    OIPL_ERROR_LOADING_IMAGE,
    OIPL_ERROR_NEGATIVE_FACTOR,
    OIPL_ERROR_MEMORY_ALLOCATION,
    OIPL_ERROR_UNSUPPORTED_IMAGE_FORMAT,
    OIPL_ERROR_FILE_PATH_DOES_NOT_EXIST,
    OIPL_ERROR_UNSUPPORTED_FONT_FORMAT
} OIPL_ErrorCode;

typedef struct
{
    OIPL_ErrorCode code;
    const char* message;
} OIPL_ErrorInfo;

#define SUCCESS (OIPL_ErrorInfo) { OIPL_SUCCESS, "Success.\n" }
#define ERROR_LOADING_IMAGE (OIPL_ErrorInfo) { OIPL_ERROR_LOADING_IMAGE, "Failed to load the image. The file may be corrupted, unsupported, or inaccessible. Please verify the file path, format, and permissions.\n" }
#define NEGATIVE_FACTOR (OIPL_ErrorInfo) { OIPL_ERROR_NEGATIVE_FACTOR,  "Factor must be non-negative. Please provide a valid value.\n" }
#define FAILED_MEMORY_ALLOCATION (OIPL_ErrorInfo) { OIPL_ERROR_MEMORY_ALLOCATION, "Memory allocation failed.\n" }
#define UNSUPPORTED_IMAGE_FORMAT (OIPL_ErrorInfo) { OIPL_ERROR_UNSUPPORTED_IMAGE_FORMAT, "Unsupported image format.\n" }
#define FILE_PATH_DOES_NOT_EXIST (OIPL_ErrorInfo) { OIPL_ERROR_FILE_PATH_DOES_NOT_EXIST, "The specified path may be invalid or the file may not exist. Please check the file path and permissions.\n" }
#define UNSUPPORTED_FONT_FORMAT (OIPL_ErrorInfo) { OIPL_ERROR_UNSUPPORTED_FONT_FORMAT, "Invalid font format.\n" }