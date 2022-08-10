#include "main.h"

int main(int argc, char* argv[]) {
    CHECK_ARGU(1);
    
    char* cmd = argv[1];
    if (!strcmp(cmd, "version")) {
        printf("version 1.0.0");
        exit(0);
    }

    if (!strcmp(cmd, "png2qoi")) {
        CHECK_ARGU(3);
        char* sofile = argv[2];
        char* tafile = argv[3];

        RGBImage* im = getPNG(sofile);
        qoi3Save(im, tafile);
        free(im->data);
        free(im);

        exit(0);
    }    
    if (!strcmp(cmd, "bmp2qoi")) {
        CHECK_ARGU(3);
        char* sofile = argv[2];
        char* tafile = argv[3];

        RGBImage* im = bmpRead(sofile);
        qoi3Save(im, tafile);
        free(im->data);
        free(im);

        exit(0);
    }

    //test1();
    //test2();
    //test3();

    return 0;
}

void test1() {
    RGBImage* im;
    im = bmpRead("D:/Workspace/Elerrina/test/test1.bmp");
    bmpSave(im, "D:/Workspace/Elerrina/test/test1n.bmp");
    saveImageRaw(im, "D:/Workspace/Elerrina/test/test1.txt");
    qoi3Save(im, "D:/Workspace/Elerrina/test/test1.qoi");
    free(im->data);
    free(im);
}

void test2() {
    RGBImage* im;
    im = bmpRead("D:/Workspace/Elerrina/test/test2.bmp");
    bmpSave(im, "D:/Workspace/Elerrina/test/test2n.bmp");
    saveImageRaw(im, "D:/Workspace/Elerrina/test/test2.txt");
    qoi3Save(im, "D:/Workspace/Elerrina/test/test2.qoi");
    free(im->data);
    free(im);
}

void test3() {
    RGBImage* im = getPNG("D:/Workspace/Elerrina/test/test3.png");
    bmpSave(im, "D:/Workspace/Elerrina/test/test3.bmp");
    free(im->data);
    free(im);
}