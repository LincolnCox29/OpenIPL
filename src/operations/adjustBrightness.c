#include "adjustBrightness.h"
#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo imgAdjustBrightness(Img* img, const float factor)
{
    OpenIPLErrorInfo err = SUCCESS;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS ||
        (err = factorValidation(factor)).code != OIPL_SUCCESS)
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