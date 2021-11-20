
#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>

#include "parserDefs.h"


class Parser
{
    private:
        ParserTreeNode *root;
        vector<lexicalNode*> tmp_lexical_nodes;
        vector<Code*> *codes;

        nlohmann::json opr_table;

        Table *root_table, *now_table;

        int t = 0;

    public:
        void bfs_from_root();
        void bfs(ParserTreeNode*);

        void parse_err(char const*,int);
        void init(const vector<lexicalNode*> &lexical_nodes);
        void out();
        void try_push_identifier(string);
        void try_LITLOD(string);

        void get_root(const vector<lexicalNode*> &lexical_nodes);

        ParserTreeNode *program(const vector<lexicalNode*> &lexical_nodes);//程序
    
    private:
        ParserTreeNode *block(ParserTreeNode *f);//分程序
        ParserTreeNode *constant_declaration(ParserTreeNode *f);//常量说明
        ParserTreeNode *variable_declaration(ParserTreeNode *f);//变量说明
        ParserTreeNode *procedure_declaration(ParserTreeNode *f);//过程说明
        ParserTreeNode *statement(ParserTreeNode *f);//语句
        ParserTreeNode *constant_definition(ParserTreeNode *f);//常量定义
        ParserTreeNode *identifier(ParserTreeNode *f);//标识符
        ParserTreeNode *procedure_header(ParserTreeNode *f);//过程首部
        ParserTreeNode *assignment_statement(ParserTreeNode *f);//赋值语句
        ParserTreeNode *compound_statement(ParserTreeNode *f);//复合语句
        ParserTreeNode *conditional_statement(ParserTreeNode *f);//条件语句
        ParserTreeNode *condition(ParserTreeNode *f);//条件
        ParserTreeNode *expression(ParserTreeNode *f);//表达式
        ParserTreeNode *item(ParserTreeNode *f);//项
        ParserTreeNode *factor(ParserTreeNode *f);//因子
        ParserTreeNode *add_and_subtract_operator(ParserTreeNode *f);//加减算符
        ParserTreeNode *multiply_divide_operator(ParserTreeNode *f);//乘除算符
        ParserTreeNode *relational_operator(ParserTreeNode *f);//关系算符
        ParserTreeNode *procedure_call_statement(ParserTreeNode *f);//过程调用语句
        ParserTreeNode *while_loop(ParserTreeNode *f);//当型循环
        ParserTreeNode *read_statement(ParserTreeNode *f);//读语句
        ParserTreeNode *write_statement(ParserTreeNode *f);//写语句

};


#endif