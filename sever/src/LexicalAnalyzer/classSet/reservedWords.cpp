#include <iostream>
#include <fstream>
#include "reservedWords.h"

void reservedWords::load_rw()//加载保留字表,格式为blz[i] = 保留字i
{
    ifstream in_file;
    in_file.open("../inFiles/ReservedWords.in");//保留字表，第i个字符串为保留字i

    //一词一类记作STARTBLZ号开始的固定类别号
    string s = "";
    while (in_file >> s)
    {
        this->reserved_words.push_back(s);
    }
    this->start_symbol = (int)this->reserved_words.size();

    in_file.close();
    in_file.open("../inFiles/Symbol.in");//符号表源文件,第i个字符串为符号i,包括算符和界符

    while (in_file >> s)
    {
        this->reserved_words.push_back(s);
    }
    in_file.close();

    // cout<<(int)this->reserved_words.size()<<endl;
    // for (int i=0;i<(int)this->reserved_words.size();++i)
    // {
    //     cout<<this->reserved_words[i]<<endl;

    // }
    return;
    

    
}

reservedWords::reservedWords(/* args */)
{
}

reservedWords::~reservedWords()
{
}