#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_Negative(OIPL_Img* img)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    const unsigned char* lastChannelPtr = img->data + (img->height * img->width * img->channels) - 1;
    for (unsigned char* cPtr = img->data; cPtr < lastChannelPtr; cPtr += img->channels)
    {
        cPtr[0] = (unsigned char)(255 - cPtr[0]);
        cPtr[1] = (unsigned char)(255 - cPtr[1]);
        cPtr[2] = (unsigned char)(255 - cPtr[2]);
    }

    return SUCCESS;
}