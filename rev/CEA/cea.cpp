#include <string.h>
#include <stdio.h>
#include <stdlib.h>
static unsigned char const k8[16] = {	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7 }; 
static unsigned char const k7[16] = {	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10 };
static unsigned char const k6[16] = {	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8 };
static unsigned char const k5[16] = {	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15 };
static unsigned char const k4[16] = {	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9 };
static unsigned char const k3[16] = {	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11 };
static unsigned char const k2[16] = {	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1 };
static unsigned char const k1[16] = {	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7 };
const unsigned long k = 0x428911efefa288e9;

unsigned int sb(unsigned int c) {
    char c1 = c & 0xff;
    char c2 = (c & 0xff00) >> 8;
    char c3 = (c & 0xff0000) >> 16;
    char c4 = (c & 0xff000000) >> 24;
    unsigned int s1 = k8[c1>>4] | k7[c1 & 15];
    unsigned int s2 = k6[c2>>4] | k5[c2 & 15];
    unsigned int s3 = k4[c3>>4] | k3[c3 & 15];
    unsigned int s4 = k2[c4>>4] | k1[c4 & 15];
    return s1 | (s2<<8) | (s3<<16) | (s4<<24);
}

int encrypt(char * inp, unsigned int len) {
    if (len < 8) {
        return -1;
    }
    if (len % 8 != 0) {
        return -1;
    }
    for (int i = 0; i < len / 8; i+=8) {
        printf("%lx\n", *(unsigned long*)(inp+i));
        unsigned long *t = (unsigned long*)inp+i;
        unsigned long r = sb((*t << 32)>>32);
        unsigned long l = sb((*t >> 32));
        *t = r | l;
        printf("%lx\n", *(unsigned long*)(inp+i));
    }
}

int main(int argc, char ** argv) {
    char* b = (char*) malloc(8);
    strncpy(b, "testtest", 8);
    encrypt(b, 8); 
}