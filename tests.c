#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "ImgLib.h"

#include <stdio.h>
#include <time.h>

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
    absTestWithFac(imgSobelFilter, "examples\\SobelFilter.png");

    absTest(imgSepiaFilter, "examples\\SepiaFilter.png");
    absTest(imgNegative, "examples\\Negative.png");
    absTest(imgToMirror, "examples\\imgToMirror.png");
    absTest(imgTurn90, "examples\\imgTurn90.png");

    gaussianBlurTest(50u, "examples\\GaussianBlur.png");

    return 0;
}

void absTestWithFac(ImgOperationWithFac func, char* outputPath)
{
    clock_t start, end;
    Img* img = loadPng("examples\\source.png");
    start = clock();
    ImgLibErrorInfo err = func(img, 0.7f);
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    writePng(outputPath, *img);
    free(img->data);
}

void absTest(ImgOperation func, char* outputPath)
{
    clock_t start, end;
    ImgLibErrorInfo err;
    Img* img = loadPng("examples\\source.png");
    start = clock();
    if ((err = func(img)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    writePng(outputPath, *img);
    free(img->data);
}

void gaussianBlurTest(unsigned iterations, char* outputPath)
{
    clock_t start, end;
    ImgLibErrorInfo err;
    Img* img = loadPng("examples\\source.png");
    start = clock();
    if ((err = imgGaussianBlur(img, iterations)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    writePng(outputPath, *img);
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