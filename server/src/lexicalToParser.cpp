#include<fstream>
#include "lexicalToParser.h"
#include "json.hpp"
using json = nlohmann::json;

void load_lexical(vector<lexicalNode*> & lexical_node) 
{
    ifstream in_file;
    in_file.open("../jsonFiles/lexicalAns.json");
    json lexical_vec;
    in_file >> lexical_vec;
    for(json::iterator it = lexical_vec.begin(); it != lexical_vec.end(); ++it)
    {
        json j = *it;
        lexical_node.push_back(new(lexicalNode){j["value"], j["lx"], j["bh"], j["l"], j["r"]});

    }
    in_file.close();
    return;
}