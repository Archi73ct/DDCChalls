#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
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

void decrypt (uint32_t v[2], const uint32_t k[4]) {
    uint32_t v0=v[0], v1=v[1], sum=3585596896, i;  /* set up; sum is (delta << 5) & 0xFFFFFFFF */
    uint32_t delta=0xdeadbeef;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

int main() {
    char* buf[128];
    memset(buf, 0 , 128);
    scanf("%s", buf);
    if (strlen(buf) != 32) {
        printf("We only do 32bit buffers here...\n");
        exit(-1);
    }
    uint32_t k[4] = {0x1337beef, 0xfa11b33d, 0xcafebabe, 0x99669966};
    uint64_t *p = malloc(32);
    strncpy(p, flag, 32);
    printf("Before: %s\n", p);

    for(int i = 0; i <= 4; i++) {
        encrypt(&p[i], k);
    }


    printf("After: %s\n", p);

    for (int i = 0; i <= 4; i++) {
        decrypt(&p[i], k);
    }

    printf("Dec: %s\n", p);
}