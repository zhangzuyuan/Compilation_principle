#include <iostream>
#include "lexical.h"

void Lexical_main()
{
    lexicalAnalyzer lexical_analyzer;
    lexical_analyzer.load_rw();
    lexical_analyzer.solve();
    lexical_analyzer.out_table();
}
