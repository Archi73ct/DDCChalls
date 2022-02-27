#include "parser.hpp"

using namespace std;
Parser::Parser() {
    pos = 0;
}
/*Get the next character*/
char Parser::consume() {
    if (peek() == -1) return -1;
    return source.at(pos++);
}
/*consume until kth char*/
char Parser::consume(size_t k) {
    if (peek(k) != -1) {
        pos += k;
        return source.at(pos);
    }
    return -1;
}

/*Peek the next character*/
char Parser::peek() {
    if (pos >= source.size()) return -1;
    return source.at(pos);
}
/*Peek kth char*/
char Parser::peek(size_t k) {
    if (pos+k >= source.size()) return -1;
    return source.at(pos+k);
}

void Parser::readUntil(char d) {
    while (peek() != d && peek() != -1) {
        consume();
    }
    return;
}

void Parser::readNextTagStart() {
    readUntil('<');
}

void Parser::readNextTagEnd() {
    readUntil('>');
}


char Parser::readChar() {
    if (isalpha(peek())) return consume();
    return -1;
}

char Parser::readAlNum() {
    if (isalnum(peek())) return consume();
    return -1;
}

string Parser::readAlNumString() {
    string res;
    char c = readAlNum();
    while (c != -1) {
        res.push_back(c);
        c = readAlNum();
    }
    return res;
}

Node Parser::readATag() {
    readNextTagStart();
    string t = readAlNumString();
    if (t == "html");
}


void Parser::printRest() {
    size_t i = 0;
    while (peek(i) != -1) {
        printf("%c", peek(i));
        i++;
    }
}