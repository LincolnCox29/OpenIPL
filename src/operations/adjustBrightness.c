#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_AdjustBrightness(OIPL_Img* img, const float factor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (factor < 0)
        return NEGATIVE_FACTOR;

    const unsigned char* lastChannelPtr = img->data + (img->height * img->width * img->channels) - 1;
    unsigned char* cPtr = img->data;

    while (cPtr <= lastChannelPtr)
    {
        *cPtr = (unsigned char)(*cPtr * factor);
        clampColorValueUChar(cPtr);
        cPtr++;
    }

    return SUCCESS;
}