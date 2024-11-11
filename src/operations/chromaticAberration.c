#include "chromaticAberration.h"
#include "../errors.h"
#include "../tools.h"
#include <string.h>

void applyChromaticShift(Img* img, int x, int y, int bX, int bY, int rX, int rY)
{
    int index = (y * img->width + x) * img->channels;

    // –ассчитаем новые позиции дл€ сдвинутых пикселей, провер€€ на выход за границы
    int blueX = x + bX;
    int blueY = y + bY;
    int redX = x + rX;
    int redY = y + rY;

    // ѕроверка границ дл€ синего канала
    if (blueX >= 0 && blueX < img->width && blueY >= 0 && blueY < img->height) {
        int blueIndex = (blueY * img->width + blueX) * img->channels;
        img->data[index] = img->data[blueIndex];  // —двиг синего канала
    }

    // ѕроверка границ дл€ красного канала
    if (redX >= 0 && redX < img->width && redY >= 0 && redY < img->height) {
        int redIndex = (redY * img->width + redX) * img->channels;
        img->data[index + 2] = img->data[redIndex];  // —двиг красного канала
    }
}

OpenIPLErrorInfo imgChromaticAberration(Img* img, int bX, int bY, int rX, int rY, float threshold)
{
    Img sobelImg;
    sobelImg.width = img->width;
    sobelImg.height = img->height;
    sobelImg.channels = img->channels;
    sobelImg.data = imgDataAlloc(img);
    memcpy(sobelImg.data, img->data, img->width * img->height * img->channels * sizeof(unsigned char));

    OpenIPLErrorInfo err;
    if ((err = imgDataValidation(img->data)).code != OIPL_SUCCESS)
    {
        return err;
    }

    err = imgSobelFilter(&sobelImg, 0.5f);

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++) 
        {
            int index = (y * img->width + x) * img->channels;
            float gradient = (sobelImg.data[index] + sobelImg.data[index + 1] + sobelImg.data[index + 2]) / 3.0f;

            if (gradient > threshold)
                applyChromaticShift(img, x, y, bX, bY, rX, rY);
        }
    }
    return err;
}