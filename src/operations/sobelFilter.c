#include "../errors.h"
#include "../tools.h"
#include <string.h>
#include <math.h>

OIPL_ErrorInfo OIPL_SobelFilter(OIPL_Img* img, float factor)
{
    unsigned char* edgeData = imgDataAlloc(img);

    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (edgeData == NULL)
        return FAILED_MEMORY_ALLOCATION;

    const int sobelX[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    const int sobelY[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    int pIndex = 0;
    int gx = 0, gy = 0;
    int xOffset, yOffset;
    int newValue = 0;
    int neighborIndex;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;

            for (int c = 0; c < 3; c++)
            {
                gx = 0;
                gy = 0;

                for (int ky = -1; ky <= 1; ky++)
                {
                    yOffset = y + ky;
                    if (yOffset < 0 || yOffset >= img->height)
                        continue;

                    for (int kx = -1; kx <= 1; kx++)
                    {
                        xOffset = x + kx;
                        if (xOffset < 0 || xOffset >= img->width)
                            continue;

                        neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                        gx += img->data[neighborIndex + c] * sobelX[ky + 1][kx + 1];
                        gy += img->data[neighborIndex + c] * sobelY[ky + 1][kx + 1];
                    }
                }

                newValue = (int)((float)(sqrt(gx * gx + gy * gy)) * factor);
                clampColorValueInt(&newValue);
                edgeData[pIndex + c] = (unsigned char)newValue;
            }
            if (img->channels == 4)
                edgeData[pIndex + 3] = img->data[pIndex + 3];
        }
    }

    memcpy(img->data, edgeData, img->width * img->height * img->channels);
    free(edgeData);

    return SUCCESS;
}