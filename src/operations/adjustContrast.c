#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo OIPL_AdjustContrast(OIPL_Img* img, const float factor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (factor < 0)
        return NEGATIVE_FACTOR;

    int pIndex = 0;
    const int totalChannels = img->height * img->width * img->channels;
    int newValue;

    for (int cIndex = 0; cIndex < totalChannels; cIndex++)
    {
        newValue = (int)((img->data[cIndex] - MID_COLOR_VALUE) * factor + MID_COLOR_VALUE);
        clampColorValueInt(&newValue);
        img->data[cIndex] = (unsigned char)newValue;
    }

    return SUCCESS;
}