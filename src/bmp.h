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
	uint16_t bfType; // 2�ֽڣ��ļ�����
	uint32_t bfSize; // 4�ֽڣ��ļ���С
	uint16_t bfReserved1; // 2�ֽڣ���������������Ϊ0
	uint16_t bfReserved2; // 2�ֽڣ���������������Ϊ0
	uint32_t bfOffBits; // 4�ֽڣ���ͷ��λͼ���ݵ�ƫ��
} BMPFileHeaderType;

#pragma pack (1)
typedef struct {
	uint32_t biSize;// 4�ֽڣ���Ϣͷ�Ĵ�С����40
	int32_t biWidth; // 4�ֽڣ�������Ϊ��λ˵��ͼ��Ŀ��
	int32_t biHeight; // 4�ֽڣ�������Ϊ��λ˵��ͼ��ĸ߶ȣ�ͬʱ���Ϊ����˵��λͼ�����������ݱ�ʾ��ͼ������½ǵ����Ͻǣ������Ϊ��˵������
	uint16_t biPlanes; // 2�ֽڣ�ΪĿ���豸˵����ɫƽ�������ܱ�����Ϊ1
	uint16_t biBitCount; // 2�ֽڣ�˵�������� / ��������ֵ��1��2��4��8��16��24��32
	uint32_t biCompression; // 4�ֽڣ�˵��ͼ���ѹ�����ͣ���õľ���0��BI_RGB������ʾ��ѹ��
	uint32_t biSizeImages; // 4�ֽڣ�˵��λͼ���ݵĴ�С������BI_RGB��ʽʱ����������Ϊ0
	int32_t biXPelsPerMeter; // 4�ֽڣ���ʾˮƽ�ֱ��ʣ���λ������ / �ף��з�������
	int32_t biYPelsPerMeter; // 4�ֽڣ���ʾ��ֱ�ֱ��ʣ���λ������ / �ף��з�������
	uint32_t biClrUsed; // 4�ֽڣ�˵��λͼʹ�õĵ�ɫ���е���ɫ��������Ϊ0˵��ʹ������
	uint32_t biClrImportant; // 4�ֽڣ�˵����ͼ����ʾ����ҪӰ�����ɫ��������Ϊ0˵������Ҫ
} BMPInfoHeaderType;
#pragma pack(pop)

RGBImage* bmpRead(char* filePath);
void bmpSave(RGBImage* rgbimg, char* filePath);

#endif