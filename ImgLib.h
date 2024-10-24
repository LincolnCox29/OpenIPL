#pragma once

typedef struct
{
    int width, height, channels;
    unsigned char* data;
} Img;

typedef enum
{
    IMG_LIB_SUCCESS = 0,
    IMG_LIB_ERROR_LOADING_IMAGE,
    IMG_LIB_ERROR_NEGATIVE_FACTOR,
    IMG_LIB_ERROR_MEMORY_ALLOCATION,
} ImgLibErrorCode;

typedef enum
{
    PNG = 0,
    JPEG,
    BMP,
    TGA
} IMG_LIB_IMG_TYPE;

typedef struct
{
    ImgLibErrorCode code;
    const char* message;
} ImgLibErrorInfo;

void writeImg(const char* path, Img img, const IMG_LIB_IMG_TYPE type);
Img* loadImg(const char* path);
ImgLibErrorInfo imgToGrayscale(Img* img, const float factor);
ImgLibErrorInfo imgToBlackAndWhite(Img* img, const float factor);
ImgLibErrorInfo imgAdjustBrightness(Img* img, const float factor);
ImgLibErrorInfo imgAdjustContrast(Img* img, const float factor);
ImgLibErrorInfo imgGaussianBlur(Img* img, unsigned iterations);
ImgLibErrorInfo imgSepiaFilter(Img* img);
ImgLibErrorInfo imgNegative(Img* img);
ImgLibErrorInfo imgSobelFilter(Img* img, float factor);
ImgLibErrorInfo imgToMirror(Img* img);
ImgLibErrorInfo imgTurn90(Img* img);