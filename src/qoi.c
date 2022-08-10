#include "qoi.h"

void qoi3Save(RGBImage* img, char* filepath) {
    QOIHeaderType* qoiHeader;
    qoiHeader = malloc(sizeof(QOIHeaderType));
    CHECK_MEMORY(qoiHeader);

    qoiHeader->magic = _byteswap_ulong(0x716f6966);
    qoiHeader->width = _byteswap_ulong(img->width);
    qoiHeader->height = _byteswap_ulong(img->height);
    qoiHeader->channels = 3;
    qoiHeader->colorspace = 0;

    FILE* fp;
    fp = fopen(filepath, "wb");
    CHECK_FILE(fp);
    fwrite(qoiHeader, sizeof(QOIHeaderType), 1, fp);

    RGBPixel* pix;
    RGBPixel* prev;
    RGBPixel* initPix = malloc(sizeof(RGBPixel));
    CHECK_MEMORY(initPix);
    memset(initPix, 0, sizeof(RGBPixel));
    prev = initPix;

    unsigned runNum = 0;

    RGBPixel runArray[64] = { 0 };
    RGBPixel* ra = (RGBPixel*)&runArray;
    for (unsigned i = 0; i < img->height; i++) {
        for (unsigned j = 0; j < img->width; j++) {
            pix = img->data + (i * (size_t)img->width) + j;

            if (runNum ==62) {
                uint8_t input = 0xc0;
                input = input | (uint8_t)(runNum - 1);
                WRITE_FILE_BYTE(input, fp);
                runNum = 0;
            }
            // run length
            if (PIXEL_EQUAL(pix, prev)) {
                runNum++;
                continue;
            }
            if (runNum >= 1) {
                uint8_t input = 0xc0;
                input = input | (uint8_t)(runNum - 1);
                WRITE_FILE_BYTE(input, fp);
                runNum = 0;
            }

            // running array
            int index = ((int)pix->red * 3 + (int)pix->green * 5 + (int)pix->blue * 7 + 255 * 11) % 64;
            if (PIXEL_EQUAL((ra + index), pix)) {
                uint8_t input = 0x00;
                input = input | index;
                WRITE_FILE_BYTE(input, fp);
                prev = pix;
                continue;
            }
            runArray[index].red = pix->red;
            runArray[index].green = pix->green;
            runArray[index].blue = pix->blue;

            // diff
            int dr = (int)pix->red - (int)prev->red;
            int dg = (int)pix->green - (int)prev->green;
            int db = (int)pix->blue - (int)prev->blue;
            if (dr >= -2 && dr <= 1 && dg >= -2 && dg <= 1 && db >= -2 && db <= 1) {
                uint8_t input = 0x40;
                input = input | ((dr + 2) << 4) | ((dg + 2) << 2) | (db + 2) << 0;
                WRITE_FILE_BYTE(input, fp);
                prev = pix;
                continue;
            }

            // luma
            int drmdg = dr - dg;
            int dbmdg = db - dg;
            if (dg >= -32 && dg <= 31 && drmdg >= -8 && drmdg <= 7 && dbmdg >= -8 && dbmdg <= 7) {
                uint8_t input = 0x80;
                input = input | (dg + 32);
                WRITE_FILE_BYTE(input, fp);

                input = 0x00;
                input = input | ((drmdg + 8) << 4) | ((dbmdg + 8));
                WRITE_FILE_BYTE(input, fp);

                prev = pix;
                continue;
            }

            // normal
            uint8_t input = 0xfe;
            WRITE_FILE_BYTE(input, fp);
            fwrite(pix, sizeof(RGBPixel), 1, fp);
            prev = pix;
            continue;

        }
    }
    if (runNum != 0) {
        uint8_t input = 0xc0;
        input = input | runNum;
        WRITE_FILE_BYTE(input, fp);
    }

    uint8_t endBytes[8] = { 0,0,0,0,0,0,0,1 };
    fwrite(&endBytes, 8, 1, fp);

    free(initPix);
    fclose(fp);
    free(qoiHeader);
}

RGBImage* qoiRead(char* filePath) {
    RGBImage* img;
    return img;
}