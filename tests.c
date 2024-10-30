#include "src/OpenIPL.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef OpenIPLErrorInfo(*ImgOperationWithFac)(Img*, float);
typedef OpenIPLErrorInfo(*ImgOperation)(Img*);

void absTestWithFac(ImgOperationWithFac func, char* outputPath);
void absTest(ImgOperation func, char* outputPath);
void gaussianBlurTest(unsigned iterations, char* outputPath);
void tintTest(float rF, float gF, float bF, char* outputPath);
void bilinearInterpolationTest(int h, int w, char* outputPath);

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

    bilinearInterpolationTest(256, 200, "examples\\bilinearInterpolation.png");

    gaussianBlurTest(50u, "examples\\GaussianBlur.png");

    tintTest(1.2f, 1.0f, 0.8f, "examples\\tint.png");

    return 0;
}

void absTestWithFac(ImgOperationWithFac func, char* outputPath)
{
    clock_t start, end;
    Img* img = loadImg("examples\\source.png");
    start = clock();
    OpenIPLErrorInfo err = func(img, 0.8f);
    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    writeImg(outputPath, *img);
    free(img->data);
}

void absTest(ImgOperation func, char* outputPath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg("examples\\source.png");
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
    free(img->data);
}

void gaussianBlurTest(unsigned iterations, char* outputPath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg("examples\\source.png");
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
    free(img->data);
}

void tintTest(float rF, float gF, float bF, char* outputPath)
{
        clock_t start, end;
        OpenIPLErrorInfo err;
        Img* img = loadImg("examples\\source.png");
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
        free(img->data);
}

void bilinearInterpolationTest(int h, int w, char* outputPath)
{
    clock_t start, end;
    OpenIPLErrorInfo err;
    Img* img = loadImg("examples\\source.png");
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
    free(img->data);
}