#include "../errors.h"
#include "../tools.h"
#include "../simde/x86/sse2.h"

inline int reflect(int pos, int max) 
{
    return (pos < 0) ? -pos : (pos >= max) ? 2 * max - pos - 2 : pos;
}

OpenIPLErrorInfo imgGaussianBlur(Img* img, unsigned iterations)
{
    unsigned char* currentData = img->data;
    unsigned char* blurredData = imgDataAlloc(img);

    OpenIPLErrorInfo err = SUCCESS;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS ||
        (err = memallocValidation(blurredData)).code != OIPL_SUCCESS)
    {
        free(blurredData);
        return err;
    }

    const int weights[3][3] = 
    {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    const int weightSum = 16;

    unsigned char* temp;

    while (iterations-- > 0)
    {
        for (int y = 1; y < img->height - 1; y++)
        {
            for (int x = 1; x < img->width - 1; x++)
            {
                int pIndex = (y * img->width + x) * img->channels;

                for (int c = 0; c < 3; c++)
                {
                    simde__m128i sum = simde_mm_setzero_si128();
                    for (int ky = -1; ky <= 1; ky++)
                    {
                        int yOffset = y + ky;

                        for (int kx = -1; kx <= 1; kx++)
                        {
                            int xOffset = x + kx;
                            int neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                            int weight = weights[ky + 1][kx + 1];

                            simde__m128i pixelValue = simde_mm_set1_epi32(currentData[neighborIndex + c] * weight);
                            sum = simde_mm_add_epi32(sum, pixelValue);
                        }
                    }

                    int blurredValue = simde_mm_cvtsi128_si32(sum) / weightSum;
                    clampColorValue(&blurredValue);
                    blurredData[pIndex + c] = (unsigned char)blurredValue;
                }
            }
        }

        for (int y = 0; y < img->height; y++)
        {
            for (int x = 0; x < img->width; x++)
            {
                if (y > 0 && y < img->height - 1 && x > 0 && x < img->width - 1)
                    continue;

                int pIndex = (y * img->width + x) * img->channels;

                for (int c = 0; c < 3; c++)
                {
                    simde__m128i sum = simde_mm_setzero_si128();
                    for (int ky = -1; ky <= 1; ky++)
                    {
                        int yOffset = reflect(y + ky, img->height);

                        for (int kx = -1; kx <= 1; kx++)
                        {
                            int xOffset = reflect(x + kx, img->width);
                            int neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                            int weight = weights[ky + 1][kx + 1];

                            simde__m128i pixelValue = simde_mm_set1_epi32(currentData[neighborIndex + c] * weight);
                            sum = simde_mm_add_epi32(sum, pixelValue);
                        }
                    }

                    int blurredValue = simde_mm_cvtsi128_si32(sum) / weightSum;
                    clampColorValue(&blurredValue);
                    blurredData[pIndex + c] = (unsigned char)blurredValue;
                }
            }
        }

        temp = currentData;
        currentData = blurredData;
        blurredData = temp;
    }

    if (iterations % 2 == 0)
        memcpy(img->data, currentData, img->width * img->height * img->channels);

    free(blurredData);
    return err;
}