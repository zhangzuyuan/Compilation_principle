#ifndef PARSERDEFS_H
#define PARSERDEFS_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <fstream>
#include "defs.h"
#include "json.hpp"
#include "lexicalToParser.h"
using namespace std;
using namespace nlohmann;

typedef unsigned long ul;

struct ParserTreeNode
{
    ParserTreeNode *father;
    vector<ParserTreeNode*> *son;
    int l,r;
    ul code_l,code_r;
    string type_name;
    string value;
    ParserTreeNode(ParserTreeNode *father, int l, int r, string type_name = "", string value = "")
	:father(father), l(l), r(r), type_name(type_name), value(value)
	{
		code_l = code_r = 0;
		son = new vector<ParserTreeNode*>;
	}
};
struct Code
{
    string f;
    unsigned long l,a;
    Code(string f, unsigned long l, unsigned long a):
	f(f), l(l), a(a){}
};
struct TableItem
{
    string name;
    unsigned long val, adr;
	TableItem(string name, unsigned long val, unsigned long adr):
	name(name), val(val), adr(adr){}
};
struct Table
{
    string pro_name;
	Table *f;
	int lev;

    static pair<string, pair<ul, ul>> find_identifier(string name, Table *table)
    {
        Table *tmp_table = table;
        unsigned long l = 0;
        do
		{
			for (TableItem *item : *(tmp_table->const_table))
				if (item->name == name)
					return make_pair("const", make_pair(item->val, 0));
			
			for (TableItem *item : *(tmp_table->var_table))
				if (item->name == name)
					return make_pair("var", make_pair(l, item->adr));
			
			for (TableItem *item : *(tmp_table->pro_table))
				if (item->name == name)
					return make_pair("procedure", make_pair(l, item->adr));
			
			l++;
			tmp_table = tmp_table->f;
		}while (tmp_table != nullptr);
		
		return make_pair("", make_pair(0, 0));    
    }

    static bool can_push(string name, Table *table)
	{
		return find_identifier(name, table).first == "";
	}

    vector<TableItem*> *const_table;
	vector<TableItem*> *var_table;
	vector<TableItem*> *pro_table;
	vector<Table *> *son;
    Table(string pro_name, Table* f, int lev)
	{
		this->pro_name = pro_name;
		this->f = f;
		this->lev = lev;
		const_table = new vector<TableItem*>();
		var_table = new vector<TableItem*>(3, new TableItem("", 0, 0));
		pro_table = new vector<TableItem*>();
		son = new vector<Table*>();
	}
};

#endif