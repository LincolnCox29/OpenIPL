#include "chromaticAberration.h"
#include "../errors.h"
#include "../tools.h"
#include <string.h>

#define GRADIENT(sobelImg, index) ((sobelImg.data[index] + sobelImg.data[index + 1] + sobelImg.data[index + 2]) / 3.0f)

OpenIPLErrorInfo imgChromaticAberration(Img* img, int bX, int bY, int rX, int rY, float threshold)
{
    OpenIPLErrorInfo err;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS)
    {
        return err;
    }

    Img sobelImg;
    sobelImg.width = img->width;
    sobelImg.height = img->height;
    sobelImg.channels = img->channels;
    sobelImg.data = imgDataAlloc(img);
    memcpy(sobelImg.data, img->data, img->width * img->height * img->channels * sizeof(unsigned char));
    err = imgSobelFilter(&sobelImg, 0.5f);

    int index;
    int bxShift;
    int byShift;
    int rxShift;
    int ryShift;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            index = (y * img->width + x) * img->channels;

            if (GRADIENT(sobelImg, index) > threshold)
            {
                bxShift = bX + x;
                byShift = bY + y;
                rxShift = rX + x;
                ryShift = rY + y;

                if (bxShift >= 0 && bxShift < img->width && byShift >= 0 && byShift < img->height)
                    img->data[index] = img->data[(byShift * img->width + bxShift) * img->channels];

                if (rxShift >= 0 && rxShift < img->width && ryShift >= 0 && ryShift < img->height)
                    img->data[index + 2] = img->data[(ryShift * img->width + rxShift) * img->channels];
            }
        }
    }
    free(sobelImg.data);
    return err;
}