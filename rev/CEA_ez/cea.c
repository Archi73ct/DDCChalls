#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void encrypt (uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0xdeadbeef;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

int main() {
    char buf[128];
    memset(buf, 0 , 128);
    scanf("%s", buf);
    if (strnlen(buf, 32) != 32) {
        printf("We only do 32byte buffers here...\n");
        exit(-1);
    }
    uint32_t k[4] = {0x1337beef, 0xfa11b33d, 0xcafebabe, 0x99669966};
    uint64_t *p = malloc(32);
    memcpy(p, buf, 32);
    for(int i = 0; i < 4; i++) {
        encrypt(&p[i], k);
    }


    printf("After: %s\n", p);
}