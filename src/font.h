#pragma once

#ifndef FONT_H
#define FONT_H

#include "stb_truetype.h"

typedef struct OIPLFont
{
    stbtt_fontinfo fontInfo;
    unsigned char* fontBuffer;
} OIPLFont;

OIPLFont* OIPL_fontLoad(const char* path);
void OIPL_fontFree(OIPLFont* font);
float fontGetScaleForPixelHeight(OIPLFont* font, float pixelHeight);

#endif // FONT_H