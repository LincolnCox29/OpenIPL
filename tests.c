#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMG_LIB_IMPLEMENTATION
#include "ImgLib.h"

int main() //tests
{
    Img* img = malloc(sizeof(Img));
    img->data = stbi_load("examples\\source.png", &img->width, &img->height, &img->channels, 0);
    ImgLibErrorInfo err = imgAdjustContrast(img, 1.5);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    stbi_write_png("examples\\output.png",
        img->width, img->height, img->channels, img->data, img->width * img->channels);
    return 0;
}