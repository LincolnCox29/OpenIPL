#include "../errors.h"
#include "../tools.h"
#include <string.h>

OpenIPLErrorInfo OIPL_Sharpen(OIPL_Img* img)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    unsigned char* sharpenedData = imgDataAlloc(img);
    if (sharpenedData == NULL)
        return FAILED_MEMORY_ALLOCATION;

    const int weights[3][3] = 
    {
        { 0, -1,  0},
        {-1,  5, -1},
        { 0, -1,  0}
    };

    const int width = img->width;
    const int height = img->height;
    const int channels = img->channels;

    int sum;
    int pIndex;

    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            pIndex = (y * width + x) * channels;

            for (int c = 0; c < channels; c++)
            {
                sum = (
                    img->data[((y - 1) * width + (x - 1)) * channels + c] * weights[0][0] +
                    img->data[((y - 1) * width + (x)) * channels + c] * weights[0][1] +
                    img->data[((y - 1) * width + (x + 1)) * channels + c] * weights[0][2] +

                    img->data[((y)*width + (x - 1)) * channels + c] * weights[1][0] +
                    img->data[((y)*width + (x)) * channels + c] * weights[1][1] +
                    img->data[((y)*width + (x + 1)) * channels + c] * weights[1][2] +

                    img->data[((y + 1) * width + (x - 1)) * channels + c] * weights[2][0] +
                    img->data[((y + 1) * width + (x)) * channels + c] * weights[2][1] +
                    img->data[((y + 1) * width + (x + 1)) * channels + c] * weights[2][2]
                    );

                clampColorValueInt(&sum);
                sharpenedData[pIndex + c] = (unsigned char)sum;
            }
        }
    }

    memcpy(img->data, sharpenedData, width * height * channels);
    free(sharpenedData);

    return SUCCESS;
}