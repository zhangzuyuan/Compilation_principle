#ifndef RESERVEDWORDS_H
#define RESERVEDWORDS_H

#include<vector>
#include<string>
#include "defs.h"
using namespace std;


class reservedWords
{
    private:
        vector <string> reserved_words;
        int start_symbol;
    public:
        void load_rw();
        reservedWords(/* args */);
        ~reservedWords();
};


#endif
