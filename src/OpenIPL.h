#pragma once

#include "errors.h"
#include "font.h"

typedef struct
{
    int width, height, channels;
    unsigned char* data;
} OIPL_Img;

void OIPL_imgFree(OIPL_Img* img);
OIPL_Img* OIPL_imgLoad(const char* path);
OpenIPLErrorInfo OIPL_imgWrite(const char* path, OIPL_Img* img);
OpenIPLErrorInfo OIPL_Tint(OIPL_Img* img, float rFactor, float gFactor, float bFactor);
OpenIPLErrorInfo OIPL_ToGrayscale(OIPL_Img* img, const float factor);
OpenIPLErrorInfo OIPL_ToBlackAndWhite(OIPL_Img* img, const float factor);
OpenIPLErrorInfo OIPL_AdjustBrightness(OIPL_Img* img, const float factor);
OpenIPLErrorInfo OIPL_AdjustContrast(OIPL_Img* img, const float factor);
OpenIPLErrorInfo OIPL_Vignette(OIPL_Img* img, float intensity, float curve);
OpenIPLErrorInfo OIPL_GaussianBlur(OIPL_Img* img, unsigned iterations);
OpenIPLErrorInfo OIPL_SepiaFilter(OIPL_Img* img);
OpenIPLErrorInfo OIPL_Negative(OIPL_Img* img);
OpenIPLErrorInfo OIPL_SobelFilter(OIPL_Img* img, float factor);
OpenIPLErrorInfo OIPL_ToMirror(OIPL_Img* img);
OpenIPLErrorInfo OIPL_Turn90(OIPL_Img* img);
OpenIPLErrorInfo OIPL_BilinearInterpolation(OIPL_Img* img, int height, int width);
OpenIPLErrorInfo OIPL_Sharpen(OIPL_Img* img);
OpenIPLErrorInfo OIPL_ChromaticAberration(OIPL_Img* img, int bX, int bY, int rX, int rY, float threshold);
OpenIPLErrorInfo OIPL_AddText(OIPL_Img* img, int centerX, int centerY, char* text, unsigned fontSize, const OIPLFont* font, int r, int g, int b);