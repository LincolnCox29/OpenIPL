#include "Turn90.h"
#include "../errors.h"
#include "../tools.h"

ImgLibErrorInfo imgTurn90(Img* img)
{
    const int newWidth = img->height;
    const int newHeight = img->width;
    unsigned char* rotatedData = (unsigned char*)malloc(newWidth * newHeight * img->channels * sizeof(unsigned char));
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = memallocValidation(rotatedData)).code != IMG_LIB_SUCCESS)
        return err;

    int pIndex;
    int targetIndex;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            for (int c = 0; c < img->channels; c++)
            {
                pIndex = (y * img->width + x) * img->channels + c;
                targetIndex = ((x * newWidth) + (newWidth - y - 1)) * img->channels + c;

                rotatedData[targetIndex] = img->data[pIndex];
            }
        }
    }

    free(img->data);
    img->data = rotatedData;
    img->width = newWidth;
    img->height = newHeight;

    return err;
}