#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_AdjustContrast(OIPL_Img* img, const float factor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (factor < 0)
        return NEGATIVE_FACTOR;

    const unsigned char* lastChannelPtr = img->data + (img->height * img->width * img->channels) - 1;

    for (unsigned char* pPtr = img->data; pPtr < lastChannelPtr; pPtr += img->channels)
    {
        for (unsigned char* cPtr = pPtr; cPtr < pPtr + 3; cPtr++)
        {
            *cPtr = (unsigned char)((*cPtr - MID_COLOR_VALUE) * factor + MID_COLOR_VALUE);
            clampColorValueUChar(cPtr);
        }
    }
    return SUCCESS;
}