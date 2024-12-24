#include "../errors.h"
#include "../tools.h"

static inline int getPixelIndex(int x, int y, int c, const OIPL_Img* imgPtr) 
{
    return (y * imgPtr->width + x) * imgPtr->channels + c;
}
static inline int getTargetIndex(int x, int y, int c, int width, const OIPL_Img* imgPtr) 
{
    return ((x * width) + (width - y - 1)) * imgPtr->channels + c;
}

OIPL_ErrorInfo OIPL_Turn90(OIPL_Img* img)
{
    const int newWidth = img->height;
    const int newHeight = img->width;

    unsigned char* rotatedData = (unsigned char*)malloc(newWidth * newHeight * img->channels * sizeof(unsigned char));

    if (rotatedData == NULL)
    {
        free(rotatedData);
        return FAILED_MEMORY_ALLOCATION;
    }
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    for (int y = 0; y < img->height; y++)
        for (int x = 0; x < img->width; x++)
            for (int c = 0; c < img->channels; c++)
                rotatedData[getTargetIndex(x, y, c, newWidth, img)] = img->data[getPixelIndex(x, y, c, img)];

    free(img->data);
    img->data = rotatedData;
    img->width = newWidth;
    img->height = newHeight;

    return SUCCESS;
}