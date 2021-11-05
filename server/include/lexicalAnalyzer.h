#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
#include <cctype>
#include "reservedWords.h"
#include "defs.h"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


class lexicalAnalyzer
{
    private:
        reservedWords reserved_words;
        int DIVCACHE = CACHESIZE;

        int max_cache = CACHESIZE << 1;
        char cache[MAXCACHE];
        vector<string> identifier; // 标识符
        vector<string> constant; // 常量
        vector<json> jsons;

    public:
        void load_rw();
        void solve();
        void read_code();
        
        void out_table();
        void out_rw();
        void out_symbol();
        void out_identifier();
        void out_constant();

        lexicalAnalyzer(/* args */);
        ~lexicalAnalyzer();
};

#endif
