#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMG_LIB_IMPLEMENTATION
#include "ImgLib.h"

//  imgToGrayscale
//  imgToBlackAndWhite
//  imgAdjustBrightness
//  imgAdjustContrast

typedef ImgLibErrorInfo(*ImgOperationWithFac)(Img*, float);
typedef ImgLibErrorInfo(*ImgOperation)(Img*);

void absTestWithFac(ImgOperationWithFac func, char* outputPath);
void absTest(ImgOperation func, char* outputPath);
void gaussianBlurTest(unsigned iterations, char* outputPath);
void writePng(const char* path, Img img);
Img* loadPng(const char* path);

int main() //tests
{
    absTestWithFac(imgToGrayscale, "examples\\Grayscale.png");
    absTestWithFac(imgToBlackAndWhite, "examples\\BlackAndWhite.png");
    absTestWithFac(imgAdjustBrightness, "examples\\Brightness.png");
    absTestWithFac(imgAdjustContrast, "examples\\Contrast.png");

    gaussianBlurTest(50, "examples\\GaussianBlur.png");

    absTest(imgSepiaFilter, "examples\\SepiaFilter.png");
    absTest(imgNegative, "examples\\Negative.png");

    return 0;
}

void absTestWithFac(ImgOperationWithFac func, char* outputPath)
{
    Img* img = loadPng("examples\\source.png");
    ImgLibErrorInfo err = func(img, 0.8);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    writePng(outputPath, *img);
    free(img->data);
}

void absTest(ImgOperation func, char* outputPath)
{
    ImgLibErrorInfo err;
    Img* img = loadPng("examples\\source.png");

    if ((err = func(img)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    writePng(outputPath, *img);
    free(img->data);
}

void gaussianBlurTest(unsigned iterations, char* outputPath)
{
    ImgLibErrorInfo err;
    Img* img = loadPng("examples\\source.png");

    if ((err = imgGaussianBlur(img, iterations)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    writePng("examples\\GaussianBlur.png", *img);
    free(img->data);
}

void writePng(const char* path, Img img)
{
    stbi_write_png(path,img.width, img.height, img.channels, img.data, img.width * img.channels);
}

Img* loadPng(const char* path)
{
    Img* img = malloc(sizeof(Img));
    img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0);
    return img;
}