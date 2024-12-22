#include "OpenIPL.h"
#include <stdio.h>
#include "stdlib.h"
#include "tools.h"

unsigned char MaxComponent(unsigned char r, unsigned char g, unsigned char b)
{
    return (r > g) ? ((r > b) ? r : b) : ((g > b) ? g : b);
}

void clampColorValueInt(int* value)
{
    if (*value < MIN_COLOR_VALUE)
        *value = MIN_COLOR_VALUE;
    else if (*value > MAX_COLOR_VALUE)
        *value = MAX_COLOR_VALUE;
}

void clampColorValueUChar(unsigned char* value)
{
    if (*value < MIN_COLOR_VALUE)
        *value = MIN_COLOR_VALUE;
    else if (*value > MAX_COLOR_VALUE)
        *value = MAX_COLOR_VALUE;
}

void* imgDataAlloc(OIPL_Img* img)
{
    return malloc(img->width * img->height * img->channels * sizeof(unsigned char));
}