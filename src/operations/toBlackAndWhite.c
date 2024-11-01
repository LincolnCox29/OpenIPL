#include "toBlackAndWhite.h"
#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo imgToBlackAndWhite(Img* img, const float factor)
{
    OpenIPLErrorInfo err = SUCCESS;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS ||
        (err = factorValidation(factor)).code != OIPL_SUCCESS)
    {
        return err;
    }

    float brightness;
    const int totalChannels = img->height * img->width * img->channels;
    const float threshold = MID_COLOR_VALUE * factor;

    for (int pIndex = 0; pIndex < totalChannels; pIndex += img->channels)
    {
        brightness = 0.299f * img->data[pIndex + 0] + 0.587f * img->data[pIndex + 1] + 0.114f * img->data[pIndex + 2];
        brightness > threshold
            ? memset(&img->data[pIndex], MAX_COLOR_VALUE, 3)
            : memset(&img->data[pIndex], MIN_COLOR_VALUE, 3);
    }

    return err;
}