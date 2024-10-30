#include "adjustContrast.h"
#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo imgAdjustContrast(Img* img, const float factor)
{
    OpenIPLErrorInfo err = { OIPL_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS ||
        (err = factorValidation(factor)).code != OIPL_SUCCESS)
    {
        return err;
    }

    int pIndex = 0;
    const int totalChannels = img->height * img->width * img->channels;
    int newValue;

    for (int cIndex = 0; cIndex < totalChannels; cIndex++)
    {
        newValue = (int)((img->data[cIndex] - MID_COLOR_VALUE) * factor + MID_COLOR_VALUE);
        clampColorValue(&newValue);
        img->data[cIndex] = (unsigned char)newValue;
    }

    return err;
}