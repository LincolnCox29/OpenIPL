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
    IMG_LIB_ERROR_MEMORY_ALLOCATION,

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
ImgLibErrorInfo imgGaussianBlur(Img* img, unsigned iterations);
ImgLibErrorInfo imgSepiaFilter(Img* img);
static void clampColorValue(int* value);
static ImgLibErrorInfo imgDataValidation(const unsigned char* data);
static ImgLibErrorInfo factorValidation(const float factor);
static ImgLibErrorInfo memallocValidation(const unsigned char* imgData);

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

static ImgLibErrorInfo memallocValidation(const unsigned char* imgData)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if (imgData == NULL)
    {
        err.code = IMG_LIB_ERROR_MEMORY_ALLOCATION;
        err.message = "Memory allocation failed.";
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
                memset(&img->data[pIndex], MAX_COLOR_VALUE, 3);
            else
                memset(&img->data[pIndex], MIN_COLOR_VALUE, 3);
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

ImgLibErrorInfo imgGaussianBlur(Img* img, unsigned iterations)
{
    unsigned char* currentData = img->data;
    unsigned char* blurredData = malloc(img->width * img->height * img->channels * sizeof(unsigned char));

    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = memallocValidation(blurredData)).code != IMG_LIB_SUCCESS)
    {
        free(blurredData);
        return err;
    }

    int pIndex = 0;
    int blurredValue = 0;
    int xOffset, yOffset;
    int weights[3][3] = { {1, 2, 1}, {2, 4, 2}, {1, 2, 1} };
    int appliedWeightSum;
    int neighborIndex;
    unsigned char* temp;

    while (iterations-- != 0)
    {
        for (int y = 0; y < img->height; y++)
        {
            for (int x = 0; x < img->width; x++)
            {
                pIndex = (y * img->width + x) * img->channels;
                for (int c = 0; c < 3; c++)
                {
                    blurredValue = 0;
                    appliedWeightSum = 0;

                    for (int ky = -1; ky <= 1; ky++)
                    {
                        for (int kx = -1; kx <= 1; kx++)
                        {
                            yOffset = y + ky;
                            xOffset = x + kx;

                            if (yOffset >= 0 && yOffset < img->height && xOffset >= 0 && xOffset < img->width)
                            {
                                neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                                blurredValue += currentData[neighborIndex + c] * weights[ky + 1][kx + 1];
                                appliedWeightSum += weights[ky + 1][kx + 1];
                            }
                        }
                    }
                    blurredValue /= appliedWeightSum;
                    clampColorValue(&blurredValue);
                    blurredData[pIndex + c] = (unsigned char)blurredValue;
                }
            }
        }
        temp = currentData;
        currentData = blurredData;
        blurredData = temp;
    }
    free(blurredData);

    return err;
}

ImgLibErrorInfo imgSepiaFilter(Img* img)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    int pIndex = 0;
    int newRed, newGreen, newBlue;
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;

            newRed = (int)(
                (0.393 * img->data[pIndex]) + (0.769 * img->data[pIndex + 1]) + (0.189 * img->data[pIndex + 2]));
            newGreen = (int)(
                (0.349 * img->data[pIndex]) + (0.686 * img->data[pIndex + 1]) + (0.168 * img->data[pIndex + 2]));
            newBlue = (int)(
                (0.272 * img->data[pIndex]) + (0.534 * img->data[pIndex + 1]) + (0.131 * img->data[pIndex + 2]));

            clampColorValue(&newRed);
            clampColorValue(&newGreen);
            clampColorValue(&newBlue);

            img->data[pIndex]     = ((unsigned char)newRed);
            img->data[pIndex + 1] = ((unsigned char)newGreen);
            img->data[pIndex + 2] = ((unsigned char)newBlue);
        }
    }

    return err;
}

#endif

#endif // IMG_LIB_H