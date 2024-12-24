#pragma once

#include "stb_truetype.h"

typedef struct OIPL_Font
{
    stbtt_fontinfo fontInfo;
    unsigned char* fontBuffer;
} OIPL_Font;

OIPL_Font* OIPL_fontLoad(const char* path);
void OIPL_fontFree(OIPL_Font* font);