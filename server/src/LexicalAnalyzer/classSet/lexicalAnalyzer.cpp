#include<cstdio>
#include "lexicalAnalyzer.h"


void lexicalAnalyzer::load_rw()
{
    this->reserved_words.load_rw();

}
void lexicalAnalyzer::solve()
{
    int max_cache = CACHESIZE << 1;
    const int DIVCACHE = CACHESIZE;
    freopen("../source/code.source","r",stdin);
    freopen("../jsonFiles/cffxans.json","w",stdout);
    cin.clear();
    cin.sync();
    for(int i=0;)
    
}

lexicalAnalyzer::lexicalAnalyzer(/* args */)
{
}

lexicalAnalyzer::~lexicalAnalyzer()
{
}