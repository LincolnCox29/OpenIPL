#ifndef FONT_H
#define FONT_H

#include "stb_truetype.h"
#include "errors.h"

typedef struct OIPLFont 
{
    stbtt_fontinfo fontInfo;
    unsigned char* fontBuffer;
} OIPLFont;

OpenIPLErrorInfo fontLoadFromFile(const char* path, OIPLFont* font);
void fontFree(OIPLFont* font);
float fontGetScaleForPixelHeight(OIPLFont* font, float pixelHeight);

#endif // FONT_H