#pragma once

#ifndef IMG_LIB_H
#define IMG_LIB_H

#define MaxComponent(r, g, b) ((r) > (g) ? ((r) > (b) ? (r) : (b)) : ((g) > (b) ? (g) : (b)))

#define MID_COLOR_VALUE 128
#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

typedef struct
{
    int width, height, channels;
    unsigned char* data;
} Img;

typedef enum 
{
    IMG_LIB_SUCCESS = 0,
    IMG_LIB_ERROR_LOADING_IMAGE,
    IMG_LIB_ERROR_NEGATIVE_FACTOR,

} ImgLibErrorCode;

typedef struct 
{
    ImgLibErrorCode code;
    const char* message;
} ImgLibErrorInfo;

ImgLibErrorInfo imgToGrayscale(Img* img, const float factor);
ImgLibErrorInfo imgToBlackAndWhite(Img* img, const float factor);
ImgLibErrorInfo imgAdjustBrightness(Img* img, const float factor);
ImgLibErrorInfo imgAdjustContrast(Img* img, const float factor);
static void clampColorValue(int* value);
static ImgLibErrorInfo imgDataValidation(const unsigned char* data);
static ImgLibErrorInfo factorValidation(const float factor);

#ifdef IMG_LIB_IMPLEMENTATION

static ImgLibErrorInfo imgDataValidation(const unsigned char* data)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if (data == NULL)
    {
        err.code = IMG_LIB_ERROR_LOADING_IMAGE;
        err.message = "The specified path may be invalid or the file may not exist. Please check the file path and permissions.\n";
    }
    return err;
}

static ImgLibErrorInfo factorValidation(const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if (factor < 0)
    {
        err.code = IMG_LIB_ERROR_NEGATIVE_FACTOR;
        err.message = "Factor must be non-negative. Please provide a valid value.\n";
    }
    return err;
}

static void clampColorValue(int* value)
{
    if (*value < MIN_COLOR_VALUE)
        *value = MIN_COLOR_VALUE;
    else if (*value > MAX_COLOR_VALUE)
        *value = MAX_COLOR_VALUE;
}

ImgLibErrorInfo imgToGrayscale(Img* img, const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = factorValidation(factor)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    int pIndex = 0;
    unsigned char maxComponent = 0;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;
            maxComponent = MaxComponent(img->data[pIndex + 0], img->data[pIndex + 1], img->data[pIndex + 2]);
            for (int c = 0; c < 3; c++)
                img->data[pIndex + c] = (int)(maxComponent * factor);
        }
    }

    return err;
}

ImgLibErrorInfo imgToBlackAndWhite(Img* img, const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = factorValidation(factor)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    int brightness;
    int pIndex = 0;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;
            brightness = (int)(0.299 * img->data[pIndex + 0] + 0.587 * img->data[pIndex + 1] + 0.114 * img->data[pIndex + 2]);
            if (brightness > (int)(MID_COLOR_VALUE * factor))
                memset(&img->data[pIndex], 255, 3);
            else
                memset(&img->data[pIndex], 0, 3);
        }
    }

    return err;
}

ImgLibErrorInfo imgAdjustBrightness(Img* img, const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = factorValidation(factor)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    int pIndex = 0;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;
            for (int c = 0; c < 3; c++)
            {
                int newValue = (int)(img->data[pIndex + c] * factor);
                clampColorValue(&newValue);
                img->data[pIndex + c] = (unsigned char)newValue;
            }
        }
    }

    return err;
}

ImgLibErrorInfo imgAdjustContrast(Img* img, const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = factorValidation(factor)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    int pIndex = 0;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;
            for (int c = 0; c < 3; c++)
            {
                int newValue = (int)((img->data[pIndex + c] - MID_COLOR_VALUE) * factor + MID_COLOR_VALUE);
                clampColorValue(&newValue);
                img->data[pIndex + c] = (unsigned char)newValue;
            }
        }
    }

    return err;
}

#endif

#endif // IMG_LIB_H