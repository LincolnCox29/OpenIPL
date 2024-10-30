#include "negative.h"
#include "../errors.h"
#include "../tools.h"


OpenIPLErrorInfo imgNegative(Img* img)
{
    OpenIPLErrorInfo err = { OIPL_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS)
    {
        return err;
    }
    int totalPixels = img->height * img->width * img->channels;
    for (int pIndex = 0; pIndex < totalPixels; pIndex++)
        img->data[pIndex] = (unsigned char)(255 - img->data[pIndex]);

    return err;
}