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

int main() //tests
{
    absTest(imgToGrayscale, "examples\\Grayscale.png");
    absTest(imgToBlackAndWhite, "examples\\BlackAndWhite.png");
    absTest(imgAdjustBrightness, "examples\\Brightness.png");
    absTest(imgAdjustContrast, "examples\\Contrast.png");

    return 0;
}

void absTest(ImgOperationWithFac func, char* outputPath)
{
    Img* img = malloc(sizeof(Img));
    img->data = stbi_load("examples\\source.png", &img->width, &img->height, &img->channels, 0);
    ImgLibErrorInfo err = func(img, 1.5);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    stbi_write_png(outputPath,
        img->width, img->height, img->channels, img->data, img->width * img->channels);
    free(img->data);
}