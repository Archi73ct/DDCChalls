#include <stdio.h>
#include <memory.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>


void here_cause_you_need_it_probably() {
    __asm__(".intel_syntax\n"
            "jmp rsp");
}

void vulnerable() {
    char b[48];
    read(0, b, 128);
    return;
}

int main(int argc, char **argv) {
    puts("Show me your pwn-fu");
    setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
    vulnerable();
}
