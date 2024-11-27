#ifndef FONT_H
#define FONT_H

#include "stb_truetype.h"

typedef struct OIPLFont 
{
    stbtt_fontinfo fontInfo;
    unsigned char* fontBuffer;
} OIPLFont;

OIPLFont* fontLoadFromFile(const char* path);
void fontFree(OIPLFont* font);
float fontGetScaleForPixelHeight(OIPLFont* font, float pixelHeight);

#endif // FONT_H