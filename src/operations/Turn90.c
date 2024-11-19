#include "../errors.h"
#include "../tools.h"

static inline int getPixelIndex(int x, int y, int c, const Img* imgPtr) 
{
    return (y * imgPtr->width + x) * imgPtr->channels + c;
}
static inline int getTargetIndex(int x, int y, int c, int width, const Img* imgPtr) 
{
    return ((x * width) + (width - y - 1)) * imgPtr->channels + c;
}

OpenIPLErrorInfo imgTurn90(Img* img)
{
    const int newWidth = img->height;
    const int newHeight = img->width;

    unsigned char* rotatedData = (unsigned char*)malloc(newWidth * newHeight * img->channels * sizeof(unsigned char));

    OpenIPLErrorInfo err = SUCCESS;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS ||
        (err = memallocValidation(rotatedData)).code != OIPL_SUCCESS)
        return err;

    for (int y = 0; y < img->height; y++)
        for (int x = 0; x < img->width; x++)
            for (int c = 0; c < img->channels; c++)
                rotatedData[getTargetIndex(x, y, c, newWidth, img)] = img->data[getPixelIndex(x, y, c, img)];

    free(img->data);
    img->data = rotatedData;
    img->width = newWidth;
    img->height = newHeight;

    return err;
}