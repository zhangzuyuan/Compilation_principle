#ifndef LEXICALANALYZER_H
#define  LEXICALANALYZER_H

#include "reservedWords.h"
#include "defs.h"

class lexicalAnalyzer
{
    private:
        const int MAXCACHE = 240 + 5;
        reservedWords reserved_words;
    public:
        void load_rw();
        void solve();
        lexicalAnalyzer(/* args */);
        ~lexicalAnalyzer();
};

#endif
