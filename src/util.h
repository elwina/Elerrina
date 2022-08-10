#ifndef UTIL_H_
#define UTIL_H_

#define CHECK_MEMORY(pt) if ((pt) == NULL) {\
printf("Error: Memory Failed!\n");\
abort();\
}

#define CHECK_FILE(pt) if ((pt) == NULL) {\
printf("Error: File Failed!\n");\
abort();\
}

#define WRITE_FILE_0(num,fp) {struct { uint8_t b; } NULL_BYTE = { (uint8_t)0x00 };\
fwrite(&NULL_BYTE, 1, (num), (fp));}

#define WRITE_FILE_BYTE(byte,fp) {struct { uint8_t b; } IN_BYTE = { (uint8_t)(byte) };\
fwrite(&IN_BYTE,1,1,(fp));}

#define PIXEL_EQUAL(p1,p2) (((p1)->red==(p2)->red&&(p1)->green==(p2)->green&&(p1)->blue==(p2)->blue)?1:0)

#endif