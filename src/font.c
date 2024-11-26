#include "font.h"
#include "stb_truetype.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

OpenIPLErrorInfo fontLoadFromFile(const char* path, OIPLFont* font)
{
    if (!font)
        return FAILED_MEMORY_ALLOCATION;

    FILE* file = fopen(path, "rb");
    if (!file)
        return FILE_PATH_DOES_NOT_EXIST;

    fseek(file, 0, SEEK_END);
    size_t size = ftell(file);
    rewind(file);

    unsigned char* buffer = (unsigned char*)malloc(size);
    if (!buffer)
    {
        fclose(file);
        return FAILED_MEMORY_ALLOCATION;
    }

    fread(buffer, 1, size, file);
    fclose(file);

    if (!stbtt_InitFont(&font->fontInfo, buffer, stbtt_GetFontOffsetForIndex(buffer, 0)))
    {
        free(buffer);
        return UNSUPPORTED_IMAGE_FORMAT;
    }

    font->fontBuffer = buffer;
    return SUCCESS;
}

void fontFree(OIPLFont* font) 
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

float fontGetScaleForPixelHeight(OIPLFont* font, float pixelHeight) 
{
    if (!font)
        return 0.0f;
    return stbtt_ScaleForPixelHeight(&font->fontInfo, pixelHeight);
}

void fontGetGlyphBitmap(OIPLFont* font, int codepoint, float scale,
    unsigned char** bitmap, int* width, int* height) 
{
    if (!font || !bitmap || !width || !height)
        return;

    *bitmap = stbtt_GetCodepointBitmap(&font->fontInfo, 0, scale, codepoint, width, height, 0, 0);
}