#include "../errors.h"
#include "../tools.h"
#include "../simde/x86/sse2.h"

OIPL_ErrorInfo OIPL_AdjustBrightness(OIPL_Img* img, const float factor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (factor < 0)
        return NEGATIVE_FACTOR;

    const unsigned char* lastChannelPtr = img->data + (img->height * img->width * img->channels) - 1;
    unsigned char* cPtr = img->data;

    const simde__m128i factorVec = simde_mm_set1_epi16((int)(factor * 255));

    while (cPtr + 3 < lastChannelPtr)
    {
        simde__m128i pixelVec = simde_mm_cvtsi32_si128(*(const int*)cPtr);

        simde__m128i pixels16 = simde_mm_unpacklo_epi8(pixelVec, simde_mm_setzero_si128());

        simde__m128i adjusted = simde_mm_mullo_epi16(pixels16, factorVec);

        adjusted = simde_mm_srai_epi16(adjusted, 8);

        simde__m128i clamped = simde_mm_max_epi16(adjusted, simde_mm_setzero_si128());
        clamped = simde_mm_min_epi16(clamped, simde_mm_set1_epi16(255));

        simde__m128i final = simde_mm_packus_epi16(clamped, clamped);

        *cPtr = simde_mm_cvtsi128_si32(final);

        cPtr += 4;
    }

    while (cPtr <= lastChannelPtr)
    {
        *cPtr = (unsigned char)(*cPtr * factor);

        clampColorValueUChar(cPtr);

        cPtr++;
    }

    return SUCCESS;
}