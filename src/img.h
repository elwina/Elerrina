#ifndef IMG_H_
#define IMG_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <png.h>

#include "util.h"

#define PNG_ERROR printf("Error: PNG Error!");\
abort()

typedef struct {
	uint8_t blue;
	uint8_t green;
	uint8_t red;
} BGRPixel;

typedef struct {
	unsigned width;
	unsigned height;
	BGRPixel* data;
} BGRImage;

typedef struct {
	uint8_t red;
	uint8_t green;
	uint8_t blue;
} RGBPixel;

typedef struct {
	unsigned width;
	unsigned height;
	RGBPixel* data;
} RGBImage;

RGBImage* BGR2RGB(BGRImage* oldimg);
BGRImage* RGB2BGR(RGBImage* oldimg);

void saveImageRaw(RGBImage* img, char* filepath);
RGBImage* getPNG(char* filename);
#endif
