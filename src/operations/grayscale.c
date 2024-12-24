#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_ToGrayscale(OIPL_Img* img, const float factor)
{
    if (factor < 0)
        return NEGATIVE_FACTOR;
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    const int totalChannels = img->height * img->width * img->channels;
    unsigned char maxComponent;

    for (int pIndex = 0; pIndex < totalChannels; pIndex += img->channels)
    {
        maxComponent = (unsigned char)(MaxComponent(img->data[pIndex], img->data[pIndex + 1], img->data[pIndex + 2]) * factor);

        for (int c = 0; c < 3; c++)
            img->data[pIndex + c] = maxComponent;
    }

    return SUCCESS;
}