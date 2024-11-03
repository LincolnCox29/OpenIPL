#include "src/OpenIPL.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef OpenIPLErrorInfo(*ImgOperationWithFac)(Img*, float);
typedef OpenIPLErrorInfo(*ImgOperation)(Img*);

void absTestWithFac(ImgOperationWithFac func, const float fac, char* outputPath, char* sourcePath);
void absTest(ImgOperation func, char* outputPath, char* sourcePath);
void gaussianBlurTest(unsigned iterations, char* outputPath, char* sourcePath);
void tintTest(float rF, float gF, float bF, char* outputPath, char* sourcePath);
void bilinearInterpolationTest(int h, int w, char* outputPath, char* sourcePath);

int main() //tests
{
    absTestWithFac(imgToGrayscale, 0.8f, "examples\\Grayscale\\Grayscale.png", "examples\\Grayscale\\source.png");
    absTestWithFac(imgToBlackAndWhite, 0.3f, "examples\\BlackAndWhite\\BlackAndWhite.png", "examples\\BlackAndWhite\\source.png");
    absTestWithFac(imgAdjustBrightness, 0.7f, "examples\\Brightness\\Brightness.png", "examples\\Brightness\\source.png");
    absTestWithFac(imgAdjustContrast, 0.7f, "examples\\Contrast\\Contrast.png", "examples\\Contrast\\source.png");
    absTestWithFac(imgSobelFilter, 0.4f, "examples\\SobelFilter\\SobelFilter.png", "examples\\SobelFilter\\source.png");

    absTest(imgSepiaFilter, "examples\\SepiaFilter\\SepiaFilter.png", "examples\\SepiaFilter\\source.png");
    absTest(imgNegative, "examples\\Negative\\Negative.png", "examples\\Negative\\source.png");
    absTest(imgToMirror, "examples\\ToMirror\\ToMirror.png", "examples\\ToMirror\\source.png");
    absTest(imgTurn90, "examples\\Turn90\\Turn90.png", "examples\\Turn90\\source.png");
    absTest(imgSharpen, "examples\\Sharpen\\Sharpen.png", "examples\\Sharpen\\source.png");

    bilinearInterpolationTest(256, 200, "examples\\BilinearInterpolation\\BilinearInterpolation.png", "examples\\BilinearInterpolation\\source.png");

    gaussianBlurTest(50u, "examples\\GaussianBlur\\GaussianBlur.png", "examples\\GaussianBlur\\source.png");

    tintTest(1.2f, 1.0f, 0.8f, "examples\\Tint\\Tint.png", "examples\\Tint\\source.png");

    return 0;
}

void absTestWithFac(ImgOperationWithFac func, const float fac, char* outputPath, char* sourcePath)
{
    clock_t start, end;
    Img* img = loadImg(sourcePath);
    start = clock();
    OpenIPLErrorInfo err = func(img, fac);
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    writeImg(outputPath, *img);
    imgFree(img);
}

void absTest(ImgOperation func, char* outputPath, char* sourcePath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg(sourcePath);
    start = clock();
    if ((err = func(img)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    writeImg(outputPath, *img);
    imgFree(img);
}

void gaussianBlurTest(unsigned iterations, char* outputPath, char* sourcePath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg(sourcePath);
    start = clock();
    if ((err = imgGaussianBlur(img, iterations)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    writeImg(outputPath, *img);
    imgFree(img);
}

void tintTest(float rF, float gF, float bF, char* outputPath, char* sourcePath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg(sourcePath);
    start = clock();
    if ((err = imgTint(img, rF, gF, bF)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    writeImg(outputPath, *img);
    imgFree(img);
}

void bilinearInterpolationTest(int h, int w, char* outputPath, char* sourcePath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg(sourcePath);
    start = clock();
    if ((err = imgBilinearInterpolation(img, h, w)).code != 0)
    {
        printf("code: %d msg: %s", err.code, err.message);
        return;
    }
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    writeImg(outputPath, *img);
    imgFree(img);
}