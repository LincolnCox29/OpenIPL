#include "../errors.h"
#include "../tools.h"
#include <string.h>

OpenIPLErrorInfo imgSharpen(Img* img)
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

    for (int y = 1; y < height - 1; y++)
    {
        for (int x = 1; x < width - 1; x++)
        {
            int pIndex = (y * width + x) * channels;

            for (int c = 0; c < channels; c++)
            {
                int sum = 0;

                sum += img->data[((y - 1) * width + (x - 1)) * channels + c] * weights[0][0];
                sum += img->data[((y - 1) * width + (x)) * channels + c] * weights[0][1];
                sum += img->data[((y - 1) * width + (x + 1)) * channels + c] * weights[0][2];

                sum += img->data[((y)*width + (x - 1)) * channels + c] * weights[1][0];
                sum += img->data[((y)*width + (x)) * channels + c] * weights[1][1];
                sum += img->data[((y)*width + (x + 1)) * channels + c] * weights[1][2];

                sum += img->data[((y + 1) * width + (x - 1)) * channels + c] * weights[2][0];
                sum += img->data[((y + 1) * width + (x)) * channels + c] * weights[2][1];
                sum += img->data[((y + 1) * width + (x + 1)) * channels + c] * weights[2][2];

                clampColorValue(&sum);
                sharpenedData[pIndex + c] = (unsigned char)sum;
            }
        }
    }

    memcpy(img->data, sharpenedData, width * height * channels);
    free(sharpenedData);

    return SUCCESS;
}