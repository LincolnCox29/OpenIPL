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
    img->data = stbi_load("example.png", &img->width, &img->height, &img->channels, 0);
    ImgLibErrorInfo err = imgToGrayscale(img, 0.1);
    if (err.code != 0)
        printf("code: %d msg: %s", err.code, err.message);
    stbi_write_png("output.png",
        img->width, img->height, img->channels, img->data, img->width * img->channels);
    return 0;
}