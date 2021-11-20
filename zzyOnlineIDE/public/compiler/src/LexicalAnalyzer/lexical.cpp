#include <iostream>
#include "lexical.h"

void Lexical_main()
{
    lexicalAnalyzer lexical_analyzer;
    cout<< "load_rw" <<endl;
    lexical_analyzer.load_rw();
    cout<< "solve" <<endl;
    lexical_analyzer.solve();
    cout<< "out_table" <<endl;
    lexical_analyzer.out_table();
    cout<< "lexical ok" <<endl;
    return;
}
