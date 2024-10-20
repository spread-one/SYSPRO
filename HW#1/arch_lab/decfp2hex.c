#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef unsigned char* pointer;

bool is64bit() {
    return sizeof(void*) == 8;
}

bool isBigEndian() {
    unsigned int x = 1;
    return ((unsigned char*)&x)[0] == 0;
}

void le_show_bytes(pointer start, size_t len) {
    for (size_t i = 0; i < len; i++)
        printf("%.2X", start[i]);
    printf("\n");
}

void be_show_bytes(pointer start, size_t len) {
    for (size_t i = len; i > 0; i--)
        printf("%.2X", start[i - 1]);
    printf("\n");
}

int main(int argc, char* argv[]) {
    if(argc < 2){
        printf("Usage: %s number\n", argv[0]);
        exit(0);
    }
    double a = atof(argv[1]);

    printf("ARCH=%d\n", is64bit()? 64 : 32);
    printf("ORDERING=%s\n", isBigEndian()? "BIG_ENDIAN": "LITTLE_ENDIAN");

    printf("MYANS: DEC=%f HEX=", a);
    if (isBigEndian()) {
        be_show_bytes((pointer)&a, sizeof(double));
    } else {
        le_show_bytes((pointer)&a, sizeof(double));
    }

    return 0;
}

