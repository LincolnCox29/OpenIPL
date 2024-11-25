#include "../errors.h"
#include "../tools.h"
#include <string.h>

#define GRADIENT(sobelImg, index) ((sobelImg.data[index] + sobelImg.data[index + 1] + sobelImg.data[index + 2]) / 3.0f)
#define IS_SHIFT_PIX_IN_BOUNDS(imgPtr, x, y) (x >= 0 && x < imgPtr->width && y >= 0 && y < imgPtr->height)

OpenIPLErrorInfo imgChromaticAberration(Img* img, const int bX, const int bY, const int rX, const int rY, const float threshold)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    Img sobelImg;
    sobelImg.width = img->width;
    sobelImg.height = img->height;
    sobelImg.channels = img->channels;
    sobelImg.data = imgDataAlloc(img);
    memcpy(sobelImg.data, img->data, img->width * img->height * img->channels * sizeof(unsigned char));

    OpenIPLErrorInfo err = imgSobelFilter(&sobelImg, 0.5f);
    if (err.code)
        return err;

    int index, bxShift, byShift, rxShift, ryShift;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            index = (y * img->width + x) * img->channels;

            if (GRADIENT(sobelImg, index) > threshold)
            {
                bxShift = bX + x;
                byShift = bY + y;
                rxShift = rX + x;
                ryShift = rY + y;

                if (IS_SHIFT_PIX_IN_BOUNDS(img, bxShift, byShift))
                    img->data[index] = img->data[(byShift * img->width + bxShift) * img->channels];

                if (IS_SHIFT_PIX_IN_BOUNDS(img, rxShift, ryShift))
                    img->data[index + 2] = img->data[(ryShift * img->width + rxShift) * img->channels];
            }
        }
    }

    free(sobelImg.data);
    return err;
}