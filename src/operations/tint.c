#include "tint.h"
#include "../errors.h"
#include "../tools.h"

ImgLibErrorInfo imgTint(Img* img, float rFactor, float gFactor, float bFactor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS)
        return err;

    const int totalPixels = img->height * img->width;
    const int channels = img->channels;
    float filter[3] = { rFactor, gFactor, bFactor };
    int newColor;
    int colorIndex;

    for (int pIndex = 0; pIndex < totalPixels; pIndex++)
    {
        for (short i = 0; i < 3; i++)
        {
            colorIndex = pIndex * channels + i;
            newColor = filter[i] * img->data[colorIndex];

            clampColorValue(&newColor);
            img->data[colorIndex] = (unsigned char)newColor;
        }
    }

    return err;
}