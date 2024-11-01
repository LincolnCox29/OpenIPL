#include "OpenIPL.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"
#include "operations/grayscale.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

OpenIPLErrorInfo writeImg(const char* path, Img img)
{
    const char* ext = strrchr(path, '.');

    if (ext != NULL)
    {
        if (strcmp(ext, ".png") == 0 || strcmp(ext, ".PNG") == 0)
        {
            stbi_write_png(path, img.width, img.height, img.channels, img.data, img.width * img.channels);
            return SUCCESS;
        }
        else if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0 || strcmp(ext, ".JPG") == 0 || strcmp(ext, ".JPEG") == 0)
        {
            stbi_write_jpg(path, img.width, img.height, img.channels, img.data, 100);
            return SUCCESS;
        }
        else if (strcmp(ext, ".bmp") == 0 || strcmp(ext, ".BMP") == 0)
        {
            stbi_write_bmp(path, img.width, img.height, img.channels, img.data);
            return SUCCESS;
        }
        else if (strcmp(ext, ".tga") == 0 || strcmp(ext, ".TGA") == 0)
        {
            stbi_write_tga(path, img.width, img.height, img.channels, img.data);
            return SUCCESS;
        }
        else
            return UNSUPPORTED_IMAGE_FORMAT;
    }
    else
        return FILE_PATH_DOES_NOT_EXIST;
}

Img* loadImg(const char* path)
{
    Img* img = malloc(sizeof(Img));
    img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0);
    return img;
}