#include "adjustBrightness.h"
#include "../errors.h"
#include "../tools.h"

ImgLibErrorInfo imgAdjustBrightness(Img* img, const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = factorValidation(factor)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    const int totalChannels = img->height * img->width * img->channels;
    int newValue;

    for (int cIndex = 0; cIndex < totalChannels; cIndex++)
    {
        newValue = (int)(img->data[cIndex] * factor);
        clampColorValue(&newValue);
        img->data[cIndex] = (unsigned char)newValue;
    }
    return err;
}