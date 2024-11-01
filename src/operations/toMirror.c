#include "toMirror.h"
#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo imgToMirror(Img* img)
{
    OpenIPLErrorInfo err = SUCCESS;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS)
        return err;

    int pIndex = 0;
    unsigned char tempData;
    int targetIndex;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width / 2; x++)
        {
            for (int c = 0; c < img->channels; c++)
            {
                pIndex = (y * img->width + x) * img->channels + c;
                targetIndex = (y * img->width + (img->width - 1 - x)) * img->channels + c;

                tempData = img->data[pIndex];
                img->data[pIndex] = img->data[targetIndex];
                img->data[targetIndex] = tempData;
            }
        }
    }

    return err;
}