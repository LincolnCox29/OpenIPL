#include "../errors.h"
#include "../tools.h"

OpenIPLErrorInfo OIPL_BilinearInterpolation(Img* img, int height, int width)
{
    unsigned char* newData = (unsigned char*)malloc(height * width * img->channels);

    if (newData == NULL)
        return FAILED_MEMORY_ALLOCATION;
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    float scaleX = (float)img->width / width;
    float scaleY = (float)img->height / height;

    for (int y = 0; y < height; y++) 
    {
        for (int x = 0; x < width; x++)
        {
            float srcX = x * scaleX;
            float srcY = y * scaleY;

            int x1 = (int)srcX;
            int y1 = (int)srcY;
            int x2 = x1 + 1 < img->width ? x1 + 1 : x1;
            int y2 = y1 + 1 < img->height ? y1 + 1 : y1;

            float dx = srcX - x1;
            float dy = srcY - y1;

            for (int c = 0; c < img->channels; c++) 
            {
                int p11 = img->data[(y1 * img->width + x1) * img->channels + c];
                int p12 = img->data[(y2 * img->width + x1) * img->channels + c];
                int p21 = img->data[(y1 * img->width + x2) * img->channels + c];
                int p22 = img->data[(y2 * img->width + x2) * img->channels + c];

                float interpolatedValue = (1 - dx) * (1 - dy) * p11 +
                    dx * (1 - dy) * p21 +
                    (1 - dx) * dy * p12 +
                    dx * dy * p22;

                newData[(y * width + x) * img->channels + c] = (unsigned char)(interpolatedValue);
            }
        }
    }

    free(img->data);
    img->data = newData;
    img->width = width;
    img->height = height;

    return SUCCESS;
}