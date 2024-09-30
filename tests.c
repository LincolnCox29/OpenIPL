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

void absTest(ImgOperationWithFac func, char* outputPath);
void gaussianBlurTest(unsigned iterations);
void writePng(const char* path, Img img);
Img* loadPng(const char* path);

int main() //tests
{
    absTest(imgToGrayscale, "examples\\Grayscale.png");
    absTest(imgToBlackAndWhite, "examples\\BlackAndWhite.png");
    absTest(imgAdjustBrightness, "examples\\Brightness.png");
    absTest(imgAdjustContrast, "examples\\Contrast.png");

    gaussianBlurTest(50);

    return 0;
}

void absTest(ImgOperationWithFac func, char* outputPath)
{
    Img* img = loadPng("examples\\source.png");
    ImgLibErrorInfo err = func(img, 0.8);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    writePng(outputPath, *img);
    free(img->data);
}

void gaussianBlurTest(unsigned iterations)
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