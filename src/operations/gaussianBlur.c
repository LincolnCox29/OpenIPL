#include "gaussianBlur.h"
#include "../errors.h"
#include "../tools.h"

ImgLibErrorInfo imgGaussianBlur(Img* img, unsigned iterations)
{
    unsigned char* currentData = img->data;
    unsigned char* blurredData = imgDataAlloc(img);

    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = memallocValidation(blurredData)).code != IMG_LIB_SUCCESS)
    {
        free(blurredData);
        return err;
    }

    int pIndex = 0;
    int blurredValue = 0;
    int xOffset, yOffset;
    const int weights[3][3] =
    {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    int appliedWeightSum;
    int neighborIndex;
    unsigned char* temp;

    while (0 != iterations--)
    {
        for (int y = 0; y < img->height; y++)
        {
            for (int x = 0; x < img->width; x++)
            {
                pIndex = (y * img->width + x) * img->channels;
                for (int c = 0; c < 3; c++)
                {
                    blurredValue = 0;
                    appliedWeightSum = 0;

                    for (int ky = -1; ky <= 1; ky++)
                    {
                        yOffset = y + ky;
                        if (yOffset < 0 || yOffset >= img->height)
                            continue;

                        for (int kx = -1; kx <= 1; kx++)
                        {
                            xOffset = x + kx;
                            if (xOffset < 0 || xOffset >= img->width)
                                continue;

                            neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                            blurredValue += currentData[neighborIndex + c] * weights[ky + 1][kx + 1];
                            appliedWeightSum += weights[ky + 1][kx + 1];
                        }
                    }
                    blurredValue /= appliedWeightSum;
                    clampColorValue(&blurredValue);
                    blurredData[pIndex + c] = (unsigned char)blurredValue;
                }
            }
        }
        temp = currentData;
        currentData = blurredData;
        blurredData = temp;
    }
    free(blurredData);

    return err;
}