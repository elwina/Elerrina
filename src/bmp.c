#include "bmp.h"

RGBImage* bmpRead(char* filepath) {
	BMPFileHeaderType* bmpFileHeader;
	bmpFileHeader = (BMPFileHeaderType*)malloc(sizeof(BMPFileHeaderType));
	CHECK_MEMORY(bmpFileHeader);

	BMPInfoHeaderType* bmpInfoHeader;
	bmpInfoHeader = (BMPInfoHeaderType*)malloc(sizeof(BMPInfoHeaderType));
	CHECK_MEMORY(bmpInfoHeader);

	FILE* fp = NULL;
	fp = fopen(filepath, "rb");
	CHECK_FILE(fp);

	fread(bmpFileHeader, sizeof(BMPFileHeaderType), 1, fp);
	fread(bmpInfoHeader, sizeof(BMPInfoHeaderType), 1, fp);

	if (bmpInfoHeader->biBitCount != 24) {
		printf("Error: %s\n", "Support 24bits only!");
		abort();
	}

	BGRImage* img;
	img = malloc(sizeof(BGRImage));
	CHECK_MEMORY(img);

	img->height = bmpInfoHeader->biHeight;
	img->width = bmpInfoHeader->biWidth;

	img->data = malloc((size_t)(bmpInfoHeader->biWidth) * (size_t)(bmpInfoHeader->biHeight) * sizeof(BGRPixel));
	CHECK_MEMORY(img->data);

	unsigned offset = (3 * bmpInfoHeader->biWidth) % 4;
	if (offset != 0) {
		offset = 4 - offset;
	}

	uint8_t* rmbits;
	rmbits = (uint8_t * )malloc(offset);
	CHECK_MEMORY(rmbits);
	
	for (int32_t i = bmpInfoHeader->biHeight-1; i >=0 ; i--) {
	//for (int32_t i = 0; i < bmpInfoHeader->biHeight; i++) {
		fread((img->data) + (i* (size_t)bmpInfoHeader->biWidth), sizeof(BGRPixel), bmpInfoHeader->biWidth, fp);
		if (offset != 0) {
			fread(rmbits,offset,1,fp);
		}
	}

	free(rmbits);
	free(bmpFileHeader);
	free(bmpInfoHeader);
	fclose(fp);

	RGBImage* re = BGR2RGB(img);
	free(img->data);
	free(img);

	return re;
}

void bmpSave(RGBImage* rgbimg,char* filePath) {
	BGRImage* img;
	img = RGB2BGR(rgbimg);

	BMPFileHeaderType* bmpFileHeader;
	bmpFileHeader = (BMPFileHeaderType*)malloc(sizeof(BMPFileHeaderType));
	CHECK_MEMORY(bmpFileHeader);

	BMPInfoHeaderType* bmpInfoHeader;
	bmpInfoHeader = (BMPInfoHeaderType*)malloc(sizeof(BMPInfoHeaderType));
	CHECK_MEMORY(bmpInfoHeader);

	unsigned row = 3 * (unsigned)img->width;
	unsigned offset = row % 4;
	if (offset != 0)
	{
		offset = 4 - offset;
	}
	row+=offset;

	bmpFileHeader->bfType = 0x4d42;
	bmpFileHeader->bfSize = img->height * row+ sizeof(BMPFileHeaderType)+ sizeof(BMPInfoHeaderType);
	bmpFileHeader->bfReserved1 = 0x0000;
	bmpFileHeader->bfReserved2 = 0x0000;
	bmpFileHeader->bfOffBits = sizeof(BMPFileHeaderType) + sizeof(BMPInfoHeaderType);

	bmpInfoHeader->biSize = sizeof(BMPInfoHeaderType);
	bmpInfoHeader->biWidth = img->width;
	bmpInfoHeader->biHeight = img->height;
	bmpInfoHeader->biPlanes = 1;
	bmpInfoHeader->biBitCount = 24;
	bmpInfoHeader->biCompression = 0;
	bmpInfoHeader->biSizeImages = img->height * row;
	bmpInfoHeader->biXPelsPerMeter = 0;
	bmpInfoHeader->biYPelsPerMeter = 0;
	bmpInfoHeader->biClrUsed = 0;
	bmpInfoHeader->biClrImportant = 0;

	FILE* fp;
	fp = fopen(filePath, "wb");
	CHECK_FILE(fp);

	fwrite(bmpFileHeader, sizeof(BMPFileHeaderType), 1, fp);
	fwrite(bmpInfoHeader, sizeof(BMPInfoHeaderType), 1, fp);
	
	for (int32_t i = img->height - 1; i >= 0; i--) {
		fwrite((img->data) + (i * (size_t)img->width), sizeof(BGRPixel), img->width, fp);
		if (offset != 0) {
			WRITE_FILE_0(offset, fp);
		}
	}

	fclose(fp);
	free(bmpFileHeader);
	free(bmpInfoHeader);
	free(img->data);
	free(img);
}