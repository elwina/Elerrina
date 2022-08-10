#include "img.h"

RGBImage* BGR2RGB(BGRImage* oldimg) {
    RGBImage* newimg;
    newimg = malloc(sizeof(RGBImage));
    CHECK_MEMORY(newimg);
    newimg->width = oldimg->width;
    newimg->height = oldimg->height;
    newimg->data = malloc((size_t)(oldimg->width) * (size_t)(oldimg->height) * sizeof(RGBPixel));
    CHECK_MEMORY(newimg->data);

    //typedef uint8_t PixType[3];
    //PixType* nip = newimg->data;
    //PixType* oip = oldimg->data;
    uint8_t(*nip)[3] = (uint8_t(*)[3])newimg->data;
    uint8_t(*oip)[3] = (uint8_t(*)[3])oldimg->data;

    for (unsigned i = 0; i < oldimg->height; i++) {
        for (unsigned j = 0; j < oldimg->width; j++) {
            (*nip)[0] = (*oip)[2];
            (*nip)[1] = (*oip)[1];
            (*nip)[2] = (*oip)[0];
            nip++;
            oip++;
        }
    }

    return newimg;
}

BGRImage* RGB2BGR(RGBImage* oldimg) {
    return (BGRImage*)BGR2RGB((BGRImage*)oldimg);
}

void saveImageRaw(RGBImage* img, char* filepath) {
    FILE* fp = NULL;
    fp = fopen(filepath, "w");
    CHECK_FILE(fp);

    RGBPixel* tempPixel;
    putc('[', fp);
    for (unsigned i = 0; i < img->height; i++) {
        putc('[', fp);
        for (unsigned j = 0; j < img->width; j++) {
            tempPixel = (img->data + i * (long long int) img->width + j);
            fprintf(fp, "[%d,%d,%d]", tempPixel->red, tempPixel->green, tempPixel->blue);
            if (j != img->width - 1) { putc(',', fp); }
        }
        fprintf(fp, "]");
        if (i != img->height - 1) { putc(',', fp); }
    }
    fprintf(fp, "]");

    fclose(fp);
}


RGBImage* getPNG(char* filename) {
    FILE* fp = fopen(filename, "rb");
    CHECK_FILE(fp);

    // 1. Read first 8 bytes to check the file is png or not
    uint8_t header[8];
    int number_to_check = 8;
    fread(header, 1, number_to_check, fp);
    int is_png = !png_sig_cmp(header, 0, 4);
    if (!is_png) {
        PNG_ERROR;
    }

    // 2. Create png struct pointer
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
        PNG_ERROR;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        PNG_ERROR;
    }

    // Set file pointer to png struct 
    png_init_io(png_ptr, fp);
    // Inicidate how many bytes we already read;
    png_set_sig_bytes(png_ptr, number_to_check);

    // 3. Read png info
    png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_ALPHA | PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_GRAY_TO_RGB, NULL);
    png_uint_32 width, height;
    int bit_depth, color_type;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);
    if (color_type != PNG_COLOR_TYPE_RGB) {
        printf("Error: PNG Color_type Unsupported!");
        abort();
    }

    // 4. Read png image data
    // Set row pointer which will take pixel value from png file
    //png_bytepp row_pointers = (png_bytepp)png_malloc(png_ptr, sizeof(png_bytepp) * height);
    //for (int i = 0; i < height; i++) {
    //    row_pointers[i] = (png_bytep)png_malloc(png_ptr, (size_t)width * 3);
    //}
    //// Set row pointer to the png struct
    //png_set_rows(png_ptr, info_ptr, row_pointers);
    //// Read png image data and save in row pointer
    //// After reading the image, you can deal with the image data with row pointers
    //png_read_image(png_ptr, row_pointers);
    //png_read_end(png_ptr,end_info);
    //// Finish the reading process and reset each pointer

    png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

    RGBImage* img;
    img = malloc(sizeof(RGBImage));
    CHECK_MEMORY(img);
    img->data = malloc(sizeof(RGBPixel) * width * height);
    CHECK_MEMORY(img->data);

    img->width = width;
    img->height = height;
    RGBPixel* tempPixel;
    for (unsigned i = 0; i < height; i++) {
        for (unsigned j = 0; j < width; j++) {
            tempPixel = (img->data + i * (long long int) width + j);
            tempPixel->red = row_pointers[i][j * 3];
            tempPixel->green = row_pointers[i][j * 3 + 1];
            tempPixel->blue = row_pointers[i][j * 3 + 2];
        }
    }

    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL,-1);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    return img;
}