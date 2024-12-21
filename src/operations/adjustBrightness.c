#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo OIPL_AdjustBrightness(OIPL_Img* img, const float factor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (factor < 0)
        return NEGATIVE_FACTOR;

    const int totalChannels = img->height * img->width * img->channels;
    int newValue;

    for (int cIndex = 0; cIndex < totalChannels; cIndex++)
    {
        newValue = (int)(img->data[cIndex] * factor);
        clampColorValue(&newValue);
        img->data[cIndex] = (unsigned char)newValue;
    }
    return SUCCESS;
}