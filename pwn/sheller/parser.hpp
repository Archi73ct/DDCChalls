#pragma once
#include <vector>
#include <iostream>
#include <stdio.h>
#include <map>
#include "node.hpp"
using namespace std;

class Parser {
    public:
        Parser();
        vector<char> source;
        size_t pos;

        // Help
        void printRest();

        // Funcs simpl
        char consume();
        char consume(size_t);
        char peek(size_t);
        char peek();

        // Medium
        char readChar();
        char readAlNum();
        string readAlNumString();
        // Harder
        void readUntil(char);
        void readNextTagStart();
        void readNextTagEnd();
        Node readATag();

};