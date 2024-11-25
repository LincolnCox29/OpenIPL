#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo imgTint(Img* img, float rFactor, float gFactor, float bFactor)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    const int totalPixels = img->height * img->width;
    const int channels = img->channels;
    float filter[3] = { rFactor, gFactor, bFactor };
    int newColor;
    int colorIndex;

    for (int pIndex = 0; pIndex < totalPixels; pIndex++)
    {
        for (int i = 0; i < 3; i++)
        {
            colorIndex = pIndex * channels + i;
            newColor = (int)(filter[i] * img->data[colorIndex]);

            clampColorValue(&newColor);
            img->data[colorIndex] = (unsigned char)newColor;
        }
    }

    return SUCCESS;
}