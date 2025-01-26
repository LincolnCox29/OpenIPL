#include "../src/OpenIPL.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define _CRT_SECURE_NO_WARNINGS

typedef OIPL_ErrorInfo(*ImgOperationWithFac)(OIPL_Img*, float);
typedef OIPL_ErrorInfo(*ImgOperationWith2Fac)(OIPL_Img*, float, float);
typedef OIPL_ErrorInfo(*ImgOperation)(OIPL_Img*);
typedef OIPL_ErrorInfo(*ImgOperationWithRGB)(OIPL_Img*, float, float, float);
typedef OIPL_ErrorInfo(*ImgOperationWithSize)(OIPL_Img*, int, int);
typedef OIPL_ErrorInfo(*ImgOperationWithIterations)(OIPL_Img*, unsigned);
typedef OIPL_ErrorInfo(*ImgOperationWithShift)(OIPL_Img*, int, int, int, int, float);
typedef OIPL_ErrorInfo(*ImgOperationWithFont)(OIPL_Img*, int, int, char*, unsigned, OIPL_Font*, int, int, int);

void testFunction(void* func, int argType, char* operationName, ...);
void printErr(OIPL_ErrorInfo* err);

enum 
{
    FUNC_WITH_FLOAT,
    FUNC_WITH_2_FLOAT,
    FUNC_NO_ARGS,
    FUNC_WITH_RGB,
    FUNC_WITH_SIZE,
    FUNC_WITH_SHIFT,
    FUNC_WITH_ITERATIONS,
    FUNC_WITH_FONT
};

int main()
{
    testFunction(OIPL_ToGrayscale, FUNC_WITH_FLOAT, "Grayscale", 0.8f);
    testFunction(OIPL_ToBlackAndWhite, FUNC_WITH_FLOAT, "BlackAndWhite", 0.3f);
    testFunction(OIPL_AdjustBrightness, FUNC_WITH_FLOAT, "Brightness", 0.7f);
    testFunction(OIPL_AdjustContrast, FUNC_WITH_FLOAT, "Contrast", 0.7f);
    testFunction(OIPL_SobelFilter, FUNC_WITH_FLOAT, "SobelFilter", 0.4f);

    testFunction(OIPL_SepiaFilter, FUNC_NO_ARGS, "SepiaFilter");
    testFunction(OIPL_Negative, FUNC_NO_ARGS, "Negative");
    testFunction(OIPL_ToMirror, FUNC_NO_ARGS, "ToMirror");
    testFunction(OIPL_Turn90, FUNC_NO_ARGS, "Turn90");
    testFunction(OIPL_Sharpen, FUNC_NO_ARGS, "Sharpen");

    testFunction(OIPL_Vignette, FUNC_WITH_2_FLOAT, "Vignette", 0.8f, 1.4f);

    testFunction(OIPL_BilinearInterpolation, FUNC_WITH_SIZE, "BilinearInterpolation", 256, 200);

    testFunction(OIPL_Pixelate, FUNC_WITH_ITERATIONS, "Pixelate", 3u);
    testFunction(OIPL_GaussianBlur, FUNC_WITH_ITERATIONS, "GaussianBlur", 50u);

    testFunction(OIPL_ChromaticAberration, FUNC_WITH_SHIFT, "ChromaticAberration", 5, 5, -3, 0, 0.1f);

    testFunction(OIPL_Tint, FUNC_WITH_RGB, "Tint", 1.2f, 1.0f, 0.8f);

    testFunction(OIPL_AddText, FUNC_WITH_FONT, "AddText", 350, 800, "Hello world", 100, 255, 255, 255);

    return 0;
}

void testFunction(void* func, int argType, char* operationName, ...)
{
    char outputPath[128];
    snprintf(outputPath, sizeof(outputPath), "examples\\%s\\%s.png", operationName, operationName);

    char sourcePath[128];
    snprintf(sourcePath, sizeof(sourcePath), "examples\\%s\\source.png", operationName);

    va_list args;
    va_start(args, operationName);

    clock_t start, end;
    OIPL_Img* img = OIPL_imgLoad(sourcePath);
    OIPL_ErrorInfo err;

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
        case FUNC_WITH_2_FLOAT:
        {
            ImgOperationWith2Fac operation = (ImgOperationWith2Fac)func;
            float fac1 = (float)va_arg(args, double);
            float fac2 = (float)va_arg(args, double);
            err = operation(img, fac1, fac2);
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

            OIPL_Font* font = OIPL_fontLoad("examples\\AddText\\Lobster-Regular.ttf");
             
            err = operation(img, x, y, text, size, font, r, g, b);

            break;
        }
    }

    end = clock();
    double timeSpent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("time: %f sec ---> %s\n", timeSpent, outputPath);

    if (err.code)
        printErr(&err);

    err = OIPL_imgWrite(outputPath, img);
    if (err.code)
        printErr(&err);

    OIPL_imgFree(img);
    va_end(args);
}

void printErr(OIPL_ErrorInfo* err)
{
    printf("code: %d msg: %s\n", err->code, err->message);
}