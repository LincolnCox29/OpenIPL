#pragma once

#include "errors.h"

#define MID_COLOR_VALUE 128
#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

typedef struct
{
    int width, height, channels;
    unsigned char* data;
} Img;

void* imgDataAlloc(Img* img);
void clampColorValue(int* value);
unsigned char MaxComponent(unsigned char r, unsigned char g, unsigned char b);
ImgLibErrorInfo writeImg(const char* path, Img img);
Img* loadImg(const char* path);
ImgLibErrorInfo imgTint(Img* img, float rFactor, float gFactor, float bFactor);
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
ImgLibErrorInfo imgBilinearInterpolation(Img* img, int height, int width);