#include "parser.h"
#include "lexicalToParser.h"

using namespace std;

vector<lexicalNode*> lexical_nodes;

void Parser_main()
{
    load_lexical(lexical_nodes);
    Parser parser;
    parser.get_root(lexical_nodes);
    parser.bfs_from_root();
    return;
}