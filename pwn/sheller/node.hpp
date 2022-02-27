#pragma once
#include <string>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <stdio.h>
#include <regex>
using namespace std;

enum NodeType {
    INV,
    H1,
    H2,
    H3,
    H4,
    H5,
    P,
    DIV,
    A,
};

class Node {
    public:
        Node();
        NodeType T;
        string content;
        string inner;
        map<string, string> attrib;
        vector<Node> children;
};