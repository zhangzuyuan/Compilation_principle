#ifndef LEXICALTOPARSER_H
#define LEXICALTOPARSER_H

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
using namespace std;

struct lexicalNode
{
    string value;
    int lx;
    int bh;
    int l,r;
    lexicalNode(string value, int lx, int bh, int l, int r):
	value(value), lx(lx), bh(bh), l(l), r(r){}
};

void load_lexical(vector<lexicalNode*> & lexical_node);

#endif
