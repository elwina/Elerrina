#include <stdio.h>
#include "img.h"
#include "bmp.h"
#include "qoi.h"

void test1();
void test2();
void test3();

#define ARGU_ERROR(str) printf("Arguments Error: %s",str);\
abort()

#define CHECK_ARGU(num) if (argc < (num)+1) {\
ARGU_ERROR("No Enough Arguments!");\
}

