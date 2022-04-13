#include <stdio.h>

int main() {
    char buffer[128];
    gets(buffer);
    puts(buffer);
    return 0;
}

__attribute__((constructor))
void myconstructor() {
    printf("Welcome to the challenge\n");
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
}