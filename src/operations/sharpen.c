#include "../errors.h"
#include "../tools.h"
#include <string.h>

OpenIPLErrorInfo imgSharpen(Img* img)
{
    unsigned char* currentData = img->data;
    unsigned char* sharpenedData = imgDataAlloc(img);

    if (sharpenedData == NULL)
    {
        free(sharpenedData);
        return FAILED_MEMORY_ALLOCATION;
    }
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    const int weights[3][3] = {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };
    const int weightSum = 1;

    for (int y = 1; y < img->height - 1; y++)
    {
        for (int x = 1; x < img->width - 1; x++)
        {
            int pIndex = (y * img->width + x) * img->channels;

            for (int c = 0; c < img->channels; c++)
            {
                int sum = 0;

                for (int ky = -1; ky <= 1; ky++)
                {
                    for (int kx = -1; kx <= 1; kx++)
                    {
                        int neighborIndex = ((y + ky) * img->width + (x + kx)) * img->channels + c;
                        sum += currentData[neighborIndex] * weights[ky + 1][kx + 1];
                    }
                }

                sum = sum / weightSum;
                clampColorValue(&sum);
                sharpenedData[pIndex + c] = (unsigned char)sum;
            }
        }
    }

    memcpy(img->data, sharpenedData, img->width * img->height * img->channels);
    free(sharpenedData);
    return SUCCESS;
}