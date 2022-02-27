#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <stdio.h>
#include <regex>
#include "parser.hpp"


using namespace std;


class Document {
    public:
        vector<char> source;
        Node root;
        void printSource();
};

