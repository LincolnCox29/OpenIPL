#include "../errors.h"
#include "../tools.h"
#include "../font.h"
#define STB_TRUETYPE_IMPLEMENTATION
#include "../stb_truetype.h"
#include <string.h>
#include <stdlib.h>

OpenIPLErrorInfo imgAddText(Img* img, int x, int y, char* text, unsigned fontSize, const OIPLFont* font)
{
    if (!img || !img->data)
        return ERROR_LOADING_IMAGE;

    float scale = fontGetScaleForPixelHeight(font, (float)fontSize);
    int ascent, descent, lineGap;
    stbtt_GetFontVMetrics(&font->fontInfo, &ascent, &descent, &lineGap);
    int baseline = (int)(ascent * scale);

    int penX = x;
    int penY = y + baseline;

    for (size_t i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == ' ')
        {
            int advanceWidth, leftSideBearing;
            stbtt_GetCodepointHMetrics(&font->fontInfo, text[i], &advanceWidth, &leftSideBearing);
            penX += (int)(advanceWidth * scale);
            continue;
        }

        int width, height, xOffset, yOffset;
        unsigned char* glyphBitmap = stbtt_GetCodepointBitmap(
            &font->fontInfo, 0, scale, text[i], &width, &height, &xOffset, &yOffset);

        if (!glyphBitmap)
            continue;

        for (int gy = 0; gy < height; gy++)
        {
            for (int gx = 0; gx < width; gx++)
            {
                int imgX = penX + gx + xOffset;
                int imgY = penY + gy + yOffset;

                if (imgX >= 0 && imgX < img->width && imgY >= 0 && imgY < img->height)
                {
                    int index = (imgY * img->width + imgX) * img->channels;
                    unsigned char glyphValue = glyphBitmap[gy * width + gx];

                    img->data[index] = (img->data[index] * (255 - glyphValue) + 0 * glyphValue) / 255;         // Red
                    img->data[index + 1] = (img->data[index + 1] * (255 - glyphValue) + 0 * glyphValue) / 255; // Green
                    img->data[index + 2] = (img->data[index + 2] * (255 - glyphValue) + 0 * glyphValue) / 255; // Blue
                }
            }
        }

        int advanceWidth, leftSideBearing;
        stbtt_GetCodepointHMetrics(&font->fontInfo, text[i], &advanceWidth, &leftSideBearing);

        penX += (int)(advanceWidth * scale);

        if (text[i + 1]) 
        {
            int kern = stbtt_GetCodepointKernAdvance(&font->fontInfo, text[i], text[i + 1]);
            penX += (int)(kern * scale);
        }

        stbtt_FreeBitmap(glyphBitmap, NULL);
    }

    return SUCCESS;
}