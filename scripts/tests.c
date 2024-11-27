#include "../src/OpenIPL.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

typedef OpenIPLErrorInfo(*ImgOperationWithFac)(Img*, float);
typedef OpenIPLErrorInfo(*ImgOperation)(Img*);
typedef OpenIPLErrorInfo(*ImgOperationWithRGB)(Img*, float, float, float);
typedef OpenIPLErrorInfo(*ImgOperationWithSize)(Img*, int, int);
typedef OpenIPLErrorInfo(*ImgOperationWithIterations)(Img*, unsigned);
typedef OpenIPLErrorInfo(*ImgOperationWithShift)(Img*, int, int, int, int, float);
typedef OpenIPLErrorInfo(*ImgOperationWithFont)(Img*, int, int, char*, unsigned, OIPLFont*, int, int, int);

void testFunction(void* func, int argType, char* outputPath, char* sourcePath, ...);
void printErr(OpenIPLErrorInfo* err);

enum 
{
    FUNC_WITH_FLOAT,
    FUNC_NO_ARGS,
    FUNC_WITH_RGB,
    FUNC_WITH_SIZE,
    FUNC_WITH_SHIFT,
    FUNC_WITH_ITERATIONS,
    FUNC_WITH_FONT
};

int main()
{
    testFunction(imgToGrayscale, FUNC_WITH_FLOAT, "examples\\Grayscale\\Grayscale.png", "examples\\Grayscale\\source.png", 0.8f);
    testFunction(imgToBlackAndWhite, FUNC_WITH_FLOAT, "examples\\BlackAndWhite\\BlackAndWhite.png", "examples\\BlackAndWhite\\source.png", 0.3f);
    testFunction(imgAdjustBrightness, FUNC_WITH_FLOAT, "examples\\Brightness\\Brightness.png", "examples\\Brightness\\source.png", 0.7f);
    testFunction(imgAdjustContrast, FUNC_WITH_FLOAT, "examples\\Contrast\\Contrast.png", "examples\\Contrast\\source.png", 0.7f);
    testFunction(imgSobelFilter, FUNC_WITH_FLOAT, "examples\\SobelFilter\\SobelFilter.png", "examples\\SobelFilter\\source.png", 0.4f);

    testFunction(imgSepiaFilter, FUNC_NO_ARGS, "examples\\SepiaFilter\\SepiaFilter.png", "examples\\SepiaFilter\\source.png");
    testFunction(imgNegative, FUNC_NO_ARGS, "examples\\Negative\\Negative.png", "examples\\Negative\\source.png");
    testFunction(imgToMirror, FUNC_NO_ARGS, "examples\\ToMirror\\ToMirror.png", "examples\\ToMirror\\source.png");
    testFunction(imgTurn90, FUNC_NO_ARGS, "examples\\Turn90\\Turn90.png", "examples\\Turn90\\source.png");
    testFunction(imgSharpen, FUNC_NO_ARGS, "examples\\Sharpen\\Sharpen.png", "examples\\Sharpen\\source.png");

    testFunction(imgBilinearInterpolation, FUNC_WITH_SIZE, "examples\\BilinearInterpolation\\BilinearInterpolation.png", "examples\\BilinearInterpolation\\source.png", 256, 200);

    testFunction(imgGaussianBlur, FUNC_WITH_ITERATIONS, "examples\\GaussianBlur\\GaussianBlur.png", "examples\\GaussianBlur\\source.png", 50u);

    testFunction(imgChromaticAberration, FUNC_WITH_SHIFT, "examples\\ChromaticAberration\\ChromaticAberration.png", "examples\\ChromaticAberration\\source.png", 5, 5, -3, 0, 0.1f);

    testFunction(imgTint, FUNC_WITH_RGB, "examples\\Tint\\Tint.png", "examples\\Tint\\source.png", 1.2f, 1.0f, 0.8f);

    testFunction(imgAddText, FUNC_WITH_FONT, "examples\\AddText\\AddText.png", "examples\\AddText\\source.png", 350, 800, "Hello world", 100, 255, 255, 255);

    return 0;
}

void testFunction(void* func, int argType, char* outputPath, char* sourcePath, ...)
{
    va_list args;
    va_start(args, sourcePath);

    clock_t start, end;
    Img* img = loadImg(sourcePath);
    OpenIPLErrorInfo err;

    if (!img) 
    {
        printf("Error: Unable to load image from %s\n", sourcePath);
        va_end(args);
        return;
    }

    start = clock();

    switch (argType)
    {
        case FUNC_WITH_FLOAT:
        {
            ImgOperationWithFac operation = (ImgOperationWithFac)func;
            float fac = (float)va_arg(args, double);
            err = operation(img, fac);
            break;
        }
        case FUNC_NO_ARGS:
        {
            ImgOperation operation = (ImgOperation)func;
            err = operation(img);
            break;
        }
        case FUNC_WITH_RGB:
        {
            ImgOperationWithRGB operation = (ImgOperationWithRGB)func;
            float rF = (float)va_arg(args, double);
            float gF = (float)va_arg(args, double);
            float bF = (float)va_arg(args, double);
            err = operation(img, rF, gF, bF);
            break;
        }
        case FUNC_WITH_SIZE:
        {
            ImgOperationWithSize operation = (ImgOperationWithSize)func;
            int h = va_arg(args, int);
            int w = va_arg(args, int);
            err = operation(img, h, w);
            break;
        }
        case FUNC_WITH_ITERATIONS:
        {
            ImgOperationWithIterations operation = (ImgOperationWithIterations)func;
            unsigned iterations = va_arg(args, unsigned);
            err = operation(img, iterations);
            break;
        }
        case FUNC_WITH_SHIFT:
        {
            ImgOperationWithShift operation = (ImgOperationWithShift)func;
            int bX = va_arg(args, int);
            int bY = va_arg(args, int);
            int rX = va_arg(args, int);
            int rY = va_arg(args, int);
            float threshold = (float)va_arg(args, double);
            err = operation(img, bX, bY, rX, rY, threshold);
            break;
        }
        case FUNC_WITH_FONT:
        {
            ImgOperationWithFont operation = (ImgOperationWithFont)func;
            int x = va_arg(args, int);
            int y = va_arg(args, int);
            char* text = va_arg(args, char*);
            unsigned size = va_arg(args, unsigned);
            int r = va_arg(args, int);
            int g = va_arg(args, int);
            int b = va_arg(args, int);

            OIPLFont* font = fontLoadFromFile("examples\\AddText\\Lobster-Regular.ttf");
             
            err = operation(img, x, y, text, size, font, r, g, b);

            break;
        }
    }

    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);

    if (err.code)
        printErr(&err);

    err = writeImg(outputPath, *img);
    if (err.code)
        printErr(&err);

    imgFree(img);
    va_end(args);
}

void printErr(OpenIPLErrorInfo* err)
{
    printf("code: %d msg: %s\n", err->code, err->message);
}