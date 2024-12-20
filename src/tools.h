#include "OpenIPL.h"
#include <stdio.h>
#include "stdlib.h"

#define MID_COLOR_VALUE 128
#define MAX_COLOR_VALUE 255
#define MIN_COLOR_VALUE 0

unsigned char MaxComponent(unsigned char r, unsigned char g, unsigned char b);
void clampColorValue(int* value);
void* imgDataAlloc(Img* img);