#pragma once

#ifndef IMG_LIB_H
#define IMG_LIB_H

#define MaxComponent(r, g, b) ((r) > (g) ? ((r) > (b) ? (r) : (b)) : ((g) > (b) ? (g) : (b)))

#define MID_COLOR_VALUE 128
#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

#include <stdbool.h>
#include <math.h>

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
ImgLibErrorInfo imgNegative(Img* img);
ImgLibErrorInfo imgSobelFilter(Img* img, float factor);
ImgLibErrorInfo imgToMirror(Img* img);
ImgLibErrorInfo imgTurn90(Img* img);
static inline void* imgDataAlloc(Img* img);
static ImgLibErrorInfo absValidation(const ImgLibErrorCode code, const char* message, const bool error—ondition);
static void clampColorValue(int* value);
static inline ImgLibErrorInfo imgDataValidation(const unsigned char* data);
static inline ImgLibErrorInfo factorValidation(const float factor);
static inline ImgLibErrorInfo memallocValidation(const unsigned char* imgData);

#ifdef IMG_LIB_IMPLEMENTATION

// ERRORS
static inline ImgLibErrorInfo imgDataValidation(const unsigned char* data)
{
    return absValidation(IMG_LIB_ERROR_LOADING_IMAGE,
                  "The specified path may be invalid or the file may not exist. Please check the file path and permissions.\n",
                  data == NULL);
}

static inline ImgLibErrorInfo factorValidation(const float factor)
{
    return absValidation(IMG_LIB_ERROR_NEGATIVE_FACTOR,
                  "Factor must be non-negative. Please provide a valid value.\n", 
                  factor < 0);
}

static inline ImgLibErrorInfo memallocValidation(const unsigned char* imgData)
{
    return absValidation(IMG_LIB_ERROR_MEMORY_ALLOCATION, 
                  "Memory allocation failed.",
                  imgData == NULL);
}

static ImgLibErrorInfo absValidation(const ImgLibErrorCode code, const char* message, const bool errorCondition)
{
    return errorCondition 
        ? (ImgLibErrorInfo) { code, message }
        : (ImgLibErrorInfo) { IMG_LIB_SUCCESS, NULL };
}
// ERRORS END

static void clampColorValue(int* value)
{
    if (*value < MIN_COLOR_VALUE)
        *value = MIN_COLOR_VALUE;
    else if (*value > MAX_COLOR_VALUE)
        *value = MAX_COLOR_VALUE;
}

static inline void* imgDataAlloc(Img* img)
{
    return malloc(img->width * img->height * img->channels * sizeof(unsigned char));
}

ImgLibErrorInfo imgToGrayscale(Img* img, const float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = factorValidation(factor)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }

    const int totalChannels = img->height * img->width * img->channels;
    unsigned char maxComponent;

    for (int pIndex = 0; pIndex < totalChannels; pIndex+=3)
    {
        maxComponent = (unsigned char)(MaxComponent(img->data[pIndex], img->data[pIndex + 1], img->data[pIndex + 2]) * factor);

        for (int c = 0; c < 3; c++)
            img->data[pIndex + c] = maxComponent;
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

    float brightness;
    const int totalChannels = img->height * img->width * img->channels;
    const float threshold = MID_COLOR_VALUE * factor;

    for(int pIndex = 0; pIndex < totalChannels; pIndex += 3)
    {
        brightness = 0.299 * img->data[pIndex + 0] + 0.587 * img->data[pIndex + 1] + 0.114 * img->data[pIndex + 2];
        brightness > threshold
            ? memset(&img->data[pIndex], MAX_COLOR_VALUE, 3)
            : memset(&img->data[pIndex], MIN_COLOR_VALUE, 3);
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

    const int totalChannels = img->height * img->width * img->channels;
    int newValue;

    for (int cIndex = 0; cIndex < totalChannels; cIndex++)
    {
        newValue = (int)(img->data[cIndex] * factor);
        clampColorValue(&newValue);
        img->data[cIndex] = (unsigned char)newValue;
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
    const int totalChannels = img->height * img->width * img->channels;
    int newValue;

    for (int cIndex = 0; cIndex < totalChannels; cIndex++)
    {
        newValue = (int)((img->data[cIndex] - MID_COLOR_VALUE) * factor + MID_COLOR_VALUE);
        clampColorValue(&newValue);
        img->data[cIndex] = (unsigned char)newValue;
    }

    return err;
}

ImgLibErrorInfo imgGaussianBlur(Img* img, unsigned iterations)
{
    unsigned char* currentData = img->data;
    unsigned char* blurredData = imgDataAlloc(img);

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
    const int weights[3][3] = 
    { 
        {1, 2, 1}, 
        {2, 4, 2}, 
        {1, 2, 1} 
    };
    int appliedWeightSum;
    int neighborIndex;
    unsigned char* temp;

    while (0 != iterations--)
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
                        yOffset = y + ky;
                        if (yOffset < 0 || yOffset >= img->height) 
                            continue;

                        for (int kx = -1; kx <= 1; kx++)
                        {
                            xOffset = x + kx;
                            if (xOffset < 0 || xOffset >= img->width) 
                                continue;

                            neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                            blurredValue += currentData[neighborIndex + c] * weights[ky + 1][kx + 1];
                            appliedWeightSum += weights[ky + 1][kx + 1];
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

    const int totalChannels = img->height * img->width * img->channels;
    int newColors[3] = { 0,0,0 };

    for (int pIndex = 0; pIndex < totalChannels; pIndex += 3)
    {
        newColors[0] = (int)(
            (0.393 * img->data[pIndex]) + (0.769 * img->data[pIndex + 1]) + (0.189 * img->data[pIndex + 2]));
        newColors[1] = (int)(
            (0.349 * img->data[pIndex]) + (0.686 * img->data[pIndex + 1]) + (0.168 * img->data[pIndex + 2]));
        newColors[2] = (int)(
            (0.272 * img->data[pIndex]) + (0.534 * img->data[pIndex + 1]) + (0.131 * img->data[pIndex + 2]));

        for (short i = 0; i < 3; i++)
        {
            clampColorValue(&(newColors[i]));
            img->data[pIndex + i] = ((unsigned char)newColors[i]);
        }
    }

    return err;
}

ImgLibErrorInfo imgNegative(Img* img)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS)
    {
        return err;
    }
    int totalPixels = img->height * img->width * img->channels;
    for (int pIndex = 0; pIndex < totalPixels; pIndex++)
        img->data[pIndex] = (unsigned char)(255 - img->data[pIndex]);

    return err;
}

ImgLibErrorInfo imgSobelFilter(Img* img, float factor)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    unsigned char* edgeData = imgDataAlloc(img);
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = memallocValidation(edgeData)).code != IMG_LIB_SUCCESS)
    {
        free(edgeData);
        return err;
    }

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

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            pIndex = (y * img->width + x) * img->channels;

            for (int c = 0; c < img->channels; c++)
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

                        int neighborIndex = (yOffset * img->width + xOffset) * img->channels;
                        gx += img->data[neighborIndex + c] * sobelX[ky + 1][kx + 1];
                        gy += img->data[neighborIndex + c] * sobelY[ky + 1][kx + 1];
                    }
                }

                newValue = sqrt(gx * gx + gy * gy) * factor;
                clampColorValue(&newValue);
                edgeData[pIndex + c] = (unsigned char)newValue;
            }
        }
    }

    memcpy(img->data, edgeData, img->width * img->height * img->channels * sizeof(unsigned char));
    free(edgeData);

    return err;
}

ImgLibErrorInfo imgToMirror(Img* img)
{
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS)
        return err;

    int pIndex = 0;
    unsigned char tempData;
    int targetIndex;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width / 2; x++)
        {
            for (int c = 0; c < img->channels; c++)
            {
                pIndex = (y * img->width + x) * img->channels + c;
                targetIndex = (y * img->width + (img->width - 1 - x)) * img->channels + c;

                tempData = img->data[pIndex];
                img->data[pIndex] = img->data[targetIndex];
                img->data[targetIndex] = tempData;
            }
        }
    }

    return err;
}

ImgLibErrorInfo imgTurn90(Img* img)
{
    const int newWidth = img->height;
    const int newHeight = img->width;
    unsigned char* rotatedData = (unsigned char*)malloc(newWidth * newHeight * img->channels * sizeof(unsigned char));
    ImgLibErrorInfo err = { IMG_LIB_SUCCESS, NULL };
    if ((err = imgDataValidation(img->data)).code != IMG_LIB_SUCCESS ||
        (err = memallocValidation(rotatedData)).code != IMG_LIB_SUCCESS)
        return err;

    int pIndex;
    int targetIndex;

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            for (int c = 0; c < img->channels; c++)
            {
                pIndex = (y * img->width + x) * img->channels + c;
                targetIndex = ((x * newWidth) + (newWidth - y - 1)) * img->channels + c;

                rotatedData[targetIndex] = img->data[pIndex];
            }
        }
    }

    free(img->data);
    img->data = rotatedData;
    img->width = newWidth;
    img->height = newHeight;

    return err;
}

#endif

#endif // IMG_LIB_H