#include "ImgLib.h";
#include <stdio.h>
#include "stdlib.h"

unsigned char MaxComponent(unsigned char r, unsigned char g, unsigned char b);
void clampColorValue(int* value);
void* imgDataAlloc(Img* img);