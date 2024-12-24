#include "font.h"
#include "stb_truetype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

OIPL_Font* OIPL_fontLoad(const char* path)
{
    OIPL_Font* font = (OIPL_Font*)malloc(sizeof(OIPL_Font));

    FILE* file = fopen(path, "rb");
    if (!file)
        return NULL;

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    unsigned char* buffer = (unsigned char*)malloc(size);
    if (!buffer)
    {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    fclose(file);

    if (!stbtt_InitFont(&font->fontInfo, buffer, stbtt_GetFontOffsetForIndex(buffer, 0)))
    {
        free(buffer);
        free(font);
        return NULL;
    }

    font->fontBuffer = buffer;
    return font;
}

void OIPL_fontFree(OIPL_Font* font) 
{
    if (font) 
    {
        if (font->fontBuffer) 
        {
            free(font->fontBuffer);
            font->fontBuffer = NULL;
        }
        free(font);
        font = NULL;
    }
}

void fontGetGlyphBitmap(OIPL_Font* font, int codepoint, float scale,
    unsigned char** bitmap, int* width, int* height) 
{
    if (!font || !bitmap || !width || !height)
        return;

    *bitmap = stbtt_GetCodepointBitmap(&font->fontInfo, 0, scale, codepoint, width, height, 0, 0);
}