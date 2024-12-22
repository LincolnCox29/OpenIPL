#include "../errors.h"
#include "../tools.h"

inline int reflect(int pos, int max) 
{
    return (pos < 0) ? -pos : (pos >= max) ? 2 * max - pos - 2 : pos;
}

OpenIPLErrorInfo OIPL_GaussianBlur(OIPL_Img* img, unsigned iterations)
{
    unsigned char* currentData = img->data;
    unsigned char* blurredData = imgDataAlloc(img);

    if (blurredData == NULL)
    {
        free(blurredData);
        return FAILED_MEMORY_ALLOCATION;
    }
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

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
                    int sum = 0;
                    for (int ky = -1; ky <= 1; ky++)
                    {
                        int yOffset = y + ky;

                        for (int kx = -1; kx <= 1; kx++)
                        {
                            int xOffset = x + kx;
                            int neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                            int weight = weights[ky + 1][kx + 1];

                            int pixelValue = currentData[neighborIndex + c] * weight;
                            sum = sum + pixelValue;
                        }
                    }

                    int blurredValue = sum / weightSum;
                    clampColorValueInt(&blurredValue);
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
                    int sum = 0;
                    for (int ky = -1; ky <= 1; ky++)
                    {
                        int yOffset = reflect(y + ky, img->height);

                        for (int kx = -1; kx <= 1; kx++)
                        {
                            int xOffset = reflect(x + kx, img->width);
                            int neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                            int weight = weights[ky + 1][kx + 1];

                            int pixelValue = currentData[neighborIndex + c] * weight;
                            sum = sum +pixelValue;
                        }
                    }

                    int blurredValue = sum / weightSum;
                    clampColorValueInt(&blurredValue);
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
    return SUCCESS;
}