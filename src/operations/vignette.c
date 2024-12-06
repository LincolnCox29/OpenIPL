#include "../errors.h"
#include "../tools.h"
#include <math.h>

inline void applyVignette(unsigned char* channelPtr, double factor)
{
    int newValue = (int)(*channelPtr * factor);
    *channelPtr = (unsigned char)(newValue > 255 ? 255 : newValue);
}

#define DISTANCE(x, y, halfW, halfH) (sqrt((x - halfW) * (x - halfW) + (y - halfH) * (y - halfH)))

OpenIPLErrorInfo imgVignette(Img* img, float intensity, float curve)
{
    if (img->data == NULL)
        return ERROR_LOADING_IMAGE;
    if (intensity < 0.0f || curve <= 0.0f)
        return NEGATIVE_FACTOR;

    const double halfW = img->width / 2.0;
    const double halfH = img->height / 2.0;
    const double maxDistance = sqrt(halfW * halfW + halfH * halfH);

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            int pIndex = (y * img->width + x) * img->channels;

            double distanceFactor = DISTANCE(x, y, halfW, halfH) / maxDistance;

            double vignetteFactor = 1.0 - pow(distanceFactor, curve) * intensity;
            if (vignetteFactor < 0.0) vignetteFactor = 0.0;

            applyVignette(&img->data[pIndex], vignetteFactor);
            applyVignette(&img->data[pIndex + 1], vignetteFactor);
            applyVignette(&img->data[pIndex + 2], vignetteFactor);
        }
    }

    return SUCCESS;
}