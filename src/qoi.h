#ifndef QOI_H_
#define QOI_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "img.h"
#include "util.h"

#pragma pack(push)
#pragma pack (1)
typedef struct {
    uint32_t magic; // magic bytes "qoif"
    uint32_t width; // image width in pixels (BE)
    uint32_t height; // image height in pixels (BE)
    uint8_t channels; // 3 = RGB, 4 = RGBA
    uint8_t colorspace; // 0 = sRGB with linear alpha, 1 = all channels linear
} QOIHeaderType;
#pragma pack(pop)


RGBImage* qoiRead(char* filePath);
void qoi3Save(RGBImage* img, char* filepath);

#endif