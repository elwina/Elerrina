#ifndef BMP_H_  
#define BMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "img.h"
#include "util.h"

#pragma pack(push)
#pragma pack (1)
typedef struct {
	uint16_t bfType; // 2字节，文件类型
	uint32_t bfSize; // 4字节，文件大小
	uint16_t bfReserved1; // 2字节，保留，必须设置为0
	uint16_t bfReserved2; // 2字节，保留，必须设置为0
	uint32_t bfOffBits; // 4字节，从头到位图数据的偏移
} BMPFileHeaderType;

#pragma pack (1)
typedef struct {
	uint32_t biSize;// 4字节，信息头的大小，即40
	int32_t biWidth; // 4字节，以像素为单位说明图像的宽度
	int32_t biHeight; // 4字节，以像素为单位说明图像的高度，同时如果为正，说明位图倒立（即数据表示从图像的左下角到右上角），如果为负说明正向
	uint16_t biPlanes; // 2字节，为目标设备说明颜色平面数，总被设置为1
	uint16_t biBitCount; // 2字节，说明比特数 / 像素数，值有1、2、4、8、16、24、32
	uint32_t biCompression; // 4字节，说明图像的压缩类型，最常用的就是0（BI_RGB），表示不压缩
	uint32_t biSizeImages; // 4字节，说明位图数据的大小，当用BI_RGB格式时，可以设置为0
	int32_t biXPelsPerMeter; // 4字节，表示水平分辨率，单位是像素 / 米，有符号整数
	int32_t biYPelsPerMeter; // 4字节，表示垂直分辨率，单位是像素 / 米，有符号整数
	uint32_t biClrUsed; // 4字节，说明位图使用的调色板中的颜色索引数，为0说明使用所有
	uint32_t biClrImportant; // 4字节，说明对图像显示有重要影响的颜色索引数，为0说明都重要
} BMPInfoHeaderType;
#pragma pack(pop)

RGBImage* bmpRead(char* filePath);
void bmpSave(RGBImage* rgbimg, char* filePath);

#endif