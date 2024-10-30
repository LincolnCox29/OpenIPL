#include "grayscale.h"
#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo imgToGrayscale(Img* img, const float factor)
{
    OpenIPLErrorInfo err = { OIPL_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS ||
        (err = factorValidation(factor)).code != OIPL_SUCCESS)
    {
        return err;
    }

    const int totalChannels = img->height * img->width * img->channels;
    unsigned char maxComponent;

    for (int pIndex = 0; pIndex < totalChannels; pIndex += img->channels)
    {
        maxComponent = (unsigned char)(MaxComponent(img->data[pIndex], img->data[pIndex + 1], img->data[pIndex + 2]) * factor);

        for (int c = 0; c < 3; c++)
            img->data[pIndex + c] = maxComponent;
    }

    return err;
}