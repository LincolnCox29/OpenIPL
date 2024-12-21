#include "OpenIPL.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "errors.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

OpenIPLErrorInfo OIPL_imgWrite(const char* path, OIPL_Img* img)
{
    const char* ext = strrchr(path, '.');

    if (ext != NULL)
    {
        if (!strcmp(ext, ".png") || !strcmp(ext, ".PNG"))
        {
            stbi_write_png(path, img->width, img->height, img->channels, img->data, img->width * img->channels);
            return SUCCESS;
        }
        else if (!strcmp(ext, ".jpg") || !strcmp(ext, ".jpeg") || !strcmp(ext, ".JPG") || !strcmp(ext, ".JPEG"))
        {
            stbi_write_jpg(path, img->width, img->height, img->channels, img->data, 100);
            return SUCCESS;
        }
        else if (!strcmp(ext, ".bmp") || !strcmp(ext, ".BMP"))
        {
            stbi_write_bmp(path, img->width, img->height, img->channels, img->data);
            return SUCCESS;
        }
        else if (!strcmp(ext, ".tga") || !strcmp(ext, ".TGA"))
        {
            stbi_write_tga(path, img->width, img->height, img->channels, img->data);
            return SUCCESS;
        }
        else
            return UNSUPPORTED_IMAGE_FORMAT;
    }
    else
        return FILE_PATH_DOES_NOT_EXIST;
}

OIPL_Img* OIPL_imgLoad(const char* path)
{
    OIPL_Img* img = malloc(sizeof(OIPL_Img));
    img->data = stbi_load(path, &img->width, &img->height, &img->channels, 0);
    return img;
}

void OIPL_imgFree(OIPL_Img* img)
{
    if (img == NULL) 
        return;
    free(img->data);
    img->data = NULL;
    free(img);
}