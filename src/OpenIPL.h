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
void imgFree(Img* img);
unsigned char MaxComponent(unsigned char r, unsigned char g, unsigned char b);
Img* loadImg(const char* path);
OpenIPLErrorInfo writeImg(const char* path, Img img);
OpenIPLErrorInfo imgTint(Img* img, float rFactor, float gFactor, float bFactor);
OpenIPLErrorInfo imgToGrayscale(Img* img, const float factor);
OpenIPLErrorInfo imgToBlackAndWhite(Img* img, const float factor);
OpenIPLErrorInfo imgAdjustBrightness(Img* img, const float factor);
OpenIPLErrorInfo imgAdjustContrast(Img* img, const float factor);
OpenIPLErrorInfo imgGaussianBlur(Img* img, unsigned iterations);
OpenIPLErrorInfo imgSepiaFilter(Img* img);
OpenIPLErrorInfo imgNegative(Img* img);
OpenIPLErrorInfo imgSobelFilter(Img* img, float factor);
OpenIPLErrorInfo imgToMirror(Img* img);
OpenIPLErrorInfo imgTurn90(Img* img);
OpenIPLErrorInfo imgBilinearInterpolation(Img* img, int height, int width);
OpenIPLErrorInfo imgSharpen(Img* img);