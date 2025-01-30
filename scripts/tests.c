#include "../src/OpenIPL.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define _CRT_SECURE_NO_WARNINGS

#define CALL_TEST_FUNCTION(func, ...) do { \
    char inputPath[128]; \
    snprintf(inputPath, sizeof(inputPath), "examples\\%s\\source.png", #func); \
    OIPL_Img* img = OIPL_imgLoad(inputPath); \
    clock_t start = clock(); \
    OIPL_ErrorInfo err = func(img, ##__VA_ARGS__); \
    clock_t end = clock(); \
    char outputPath[128]; \
    snprintf(outputPath, sizeof(outputPath), "examples\\%s\\%s.png", #func, #func); \
    printf("Operation: %s\n", #func); \
    if (err.code != 0) \
    {\
        printf("Error: %d - %s\n", err.code, err.message);\
    }\
    printf("Execution time: %.3f ms\n\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC); \
    OIPL_imgWrite(outputPath, img); \
    OIPL_imgFree(img); \
} while(0)

int main()
{
    CALL_TEST_FUNCTION(OIPL_ToGrayscale, 0.8f);

    CALL_TEST_FUNCTION(OIPL_ToBlackAndWhite, 0.3f);

    CALL_TEST_FUNCTION(OIPL_AdjustBrightness, 0.7f);

    CALL_TEST_FUNCTION(OIPL_AdjustContrast, 0.7f);

    CALL_TEST_FUNCTION(OIPL_SobelFilter, 0.4f);

    CALL_TEST_FUNCTION(OIPL_SepiaFilter);

    CALL_TEST_FUNCTION(OIPL_Negative);

    CALL_TEST_FUNCTION(OIPL_ToMirror);

    CALL_TEST_FUNCTION(OIPL_Turn90);

    CALL_TEST_FUNCTION(OIPL_Sharpen);

    CALL_TEST_FUNCTION(OIPL_Vignette, 0.8f, 1.4f);

    CALL_TEST_FUNCTION(OIPL_BilinearInterpolation, 256, 200);

    CALL_TEST_FUNCTION(OIPL_Pixelate, 5u);

    CALL_TEST_FUNCTION(OIPL_GaussianBlur, 50u);

    CALL_TEST_FUNCTION(OIPL_ChromaticAberration, 5, 5, -3, 0, 0.1f);

    CALL_TEST_FUNCTION(OIPL_Tint, 1.2f, 1.0f, 0.8f);

    OIPL_Font* font = OIPL_fontLoad("examples\\OIPL_AddText\\Lobster-Regular.ttf");
    CALL_TEST_FUNCTION(OIPL_AddText, 350, 800, "Hello world", 100, font, 255, 255, 255);
    OIPL_fontFree(font);

    return 0;
}