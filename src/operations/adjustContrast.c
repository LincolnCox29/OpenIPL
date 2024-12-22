#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo OIPL_AdjustContrast(OIPL_Img* img, const float factor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (factor < 0)
        return NEGATIVE_FACTOR;

    const unsigned char* lastChannelPtr = img->data + (img->height * img->width * img->channels) - 1;

    for (unsigned char* cPtr = img->data; cPtr < lastChannelPtr; cPtr++)
    {
        *cPtr = (unsigned char)((*cPtr - MID_COLOR_VALUE) * factor + MID_COLOR_VALUE);
        clampColorValueUChar(cPtr);
    }
    return SUCCESS;
}