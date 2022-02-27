// This challenge is about overflowing a size to malloc, and ruining my day with a heap overflow

#include <string>
#include <unistd.h>

using namespace std;

void printmenu() {
    printf("JSON Parser");
}

int main() {
    size_t size;
    char buffer[256];
    char c = getchar();
    // JSON is always "{" first right?
    if (c != '{') return -1;
    c = getchar();
    // next should be a key
    if (c != '"') return -1;

    // Get the key
    scanf("%s", buffer);
    c = getchar();
    
    while (c != EOF) {
        switch (expression)
        {
        case /* constant-expression */:
            /* code */
            break;
        
        default:
            break;
        }
    }
}