#ifndef RESERVEDWORDS_H
#define RESERVEDWORDS_H

#include<vector>
#include<string>
#include "defs.h"
using namespace std;


class reservedWords
{
    private:
        
        int start_symbol;
    public:
        vector <string> rw;
        
        void load_rw();
        int get_start_symbol();
        void set_start_symbol(int);

        reservedWords(/* args */);
        ~reservedWords();
};


#endif
