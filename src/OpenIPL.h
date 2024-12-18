#pragma once

#include "errors.h"
#include "font.h"

#define MID_COLOR_VALUE 128
#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

typedef struct
{
    int width, height, channels;
    unsigned char* data;
} Img;

void OIPL_imgFree(Img* img);
Img* OIPL_imgLoad(const char* path);
OpenIPLErrorInfo OIPL_imgWrite(const char* path, Img* img);
OpenIPLErrorInfo OIPL_Tint(Img* img, float rFactor, float gFactor, float bFactor);
OpenIPLErrorInfo OIPL_ToGrayscale(Img* img, const float factor);
OpenIPLErrorInfo OIPL_ToBlackAndWhite(Img* img, const float factor);
OpenIPLErrorInfo OIPL_AdjustBrightness(Img* img, const float factor);
OpenIPLErrorInfo OIPL_AdjustContrast(Img* img, const float factor);
OpenIPLErrorInfo OIPL_Vignette(Img* img, float factor);
OpenIPLErrorInfo OIPL_GaussianBlur(Img* img, unsigned iterations);
OpenIPLErrorInfo OIPL_SepiaFilter(Img* img);
OpenIPLErrorInfo OIPL_Negative(Img* img);
OpenIPLErrorInfo OIPL_SobelFilter(Img* img, float factor);
OpenIPLErrorInfo OIPL_ToMirror(Img* img);
OpenIPLErrorInfo OIPL_Turn90(Img* img);
OpenIPLErrorInfo OIPL_BilinearInterpolation(Img* img, int height, int width);
OpenIPLErrorInfo OIPL_Sharpen(Img* img);
OpenIPLErrorInfo OIPL_ChromaticAberration(Img* img, int bX, int bY, int rX, int rY, float threshold);
OpenIPLErrorInfo OIPL_AddText(Img* img, int centerX, int centerY, char* text, unsigned fontSize, const OIPLFont* font, int r, int g, int b);