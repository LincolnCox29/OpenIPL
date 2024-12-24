#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_Negative(OIPL_Img* img)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    int totalPixels = img->height * img->width * img->channels;
    for (int pIndex = 0; pIndex < totalPixels; pIndex++)
        img->data[pIndex] = (unsigned char)(255 - img->data[pIndex]);

    return SUCCESS;
}