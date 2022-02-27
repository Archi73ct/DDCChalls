#include "player.hpp"


void Document::printSource() {
    for(int i = 0; i < source.size(); i++) {
        printf("%c", source.at(i));
    }
}

int main() {
    Document myDoc;
    Parser p;
    int c = getchar();
    while(c != EOF) {
        p.source.push_back((char) c);
        c = getchar();
    }
    p.readNextTagStart();
    p.consume();
    printf("%s", p.readAlNumString().c_str());
    p.readNextTagStart();
    p.consume();
    printf("%s", p.readAlNumString().c_str());
    
}