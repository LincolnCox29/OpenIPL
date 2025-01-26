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
OIPL_ErrorInfo OIPL_imgWrite(const char* path, OIPL_Img* img);
OIPL_ErrorInfo OIPL_Tint(OIPL_Img* img, float rFactor, float gFactor, float bFactor);
OIPL_ErrorInfo OIPL_ToGrayscale(OIPL_Img* img, const float factor);
OIPL_ErrorInfo OIPL_ToBlackAndWhite(OIPL_Img* img, const float factor);
OIPL_ErrorInfo OIPL_AdjustBrightness(OIPL_Img* img, const float factor);
OIPL_ErrorInfo OIPL_AdjustContrast(OIPL_Img* img, const float factor);
OIPL_ErrorInfo OIPL_Vignette(OIPL_Img* img, float intensity, float curve);
OIPL_ErrorInfo OIPL_GaussianBlur(OIPL_Img* img, unsigned iterations);
OIPL_ErrorInfo OIPL_SepiaFilter(OIPL_Img* img);
OIPL_ErrorInfo OIPL_Negative(OIPL_Img* img);
OIPL_ErrorInfo OIPL_SobelFilter(OIPL_Img* img, float factor);
OIPL_ErrorInfo OIPL_ToMirror(OIPL_Img* img);
OIPL_ErrorInfo OIPL_Turn90(OIPL_Img* img);
OIPL_ErrorInfo OIPL_BilinearInterpolation(OIPL_Img* img, int height, int width);
OIPL_ErrorInfo OIPL_Sharpen(OIPL_Img* img);
OIPL_ErrorInfo OIPL_ChromaticAberration(OIPL_Img* img, int bX, int bY, int rX, int rY, float threshold);
OIPL_ErrorInfo OIPL_AddText(OIPL_Img* img, int centerX, int centerY, char* text, unsigned fontSize, const OIPL_Font* font, int r, int g, int b);
OIPL_ErrorInfo OIPL_Pixelate(OIPL_Img* img, const unsigned scale);