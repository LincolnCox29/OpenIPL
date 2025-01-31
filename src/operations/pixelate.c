#include "../errors.h"
#include "../tools.h"

OIPL_ErrorInfo OIPL_Pixelate(OIPL_Img* img, const unsigned scale)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;

    if (scale > 1)
    {
        for (unsigned y = 0; y < img->height; y += scale)
        {
            for (unsigned x = 0; x < img->width; x += scale)
            {
                unsigned int colSum[3] = { 0, 0, 0 };
                unsigned blockPixels = 0;

                for (unsigned yPix = y; yPix < y + scale && yPix < img->height; yPix++)
                {
                    for (unsigned xPix = x; xPix < x + scale && xPix < img->width; xPix++)
                    {
                        unsigned index = (yPix * img->width + xPix) * 3;
                        colSum[0] += img->data[index];
                        colSum[1] += img->data[index + 1];
                        colSum[2] += img->data[index + 2];
                        blockPixels++;
                    }
                }

                colSum[0] /= blockPixels;
                colSum[1] /= blockPixels;
                colSum[2] /= blockPixels;

                for (unsigned yPix = y; yPix < y + scale && yPix < img->height; yPix++)
                {
                    for (unsigned xPix = x; xPix < x + scale && xPix < img->width; xPix++)
                    {
                        unsigned index = (yPix * img->width + xPix) * 3;
                        img->data[index] = (unsigned char)colSum[0];
                        img->data[index + 1] = (unsigned char)colSum[1];
                        img->data[index + 2] = (unsigned char)colSum[2];
                    }
                }
            }
        }
    }

    return SUCCESS;
}
