#include<cstdio>
#include "lexicalAnalyzer.h"
#include <iostream>
using namespace std;

void lexicalAnalyzer::load_rw()
{
    this->reserved_words.load_rw();

}

void lexicalAnalyzer::read_code()
{
    
    

    //读入缓冲区最初240个字符
    for( int i = 0; i < this->max_cache ; ++i )
    {
        if ( (this->cache[i]=getchar()) == EOF )
        {
            this->max_cache = i;
            break;
        }   
    }

}

void lexicalAnalyzer::solve()
{
    freopen("../source/code.source","r",stdin);
    freopen("../jsonFiles/lexicalAns.json","w",stdout);
    cin.clear();
    cin.sync();

    this->read_code();
    int l = 0, r = 0;
    int tot_l = 0,tot_r = 0;
    //划分 保留字/标识符/符号/常量
    
    //此循环每次读一词，产生一个“二元组”
    while (true)
    {
        //进入此处时，有 l == r && tot_l == tot_r ，且均为新开头
        //过滤不可见字符
        while (isspace(this->cache[l])){l++;r++;tot_l++;tot_r++;}

        string tmp = "";
        int id = 0,x = 0;
        //判断读取类别并读取完 全部内容

        //是字母开头，为保留字/标识符
        if(isalpha(this->cache[r])) 
        {
            //到非字母/数字停止（空格/符号/EOF）
            while (isdigit(this->cache[r]) || isalpha(this->cache[r]))
            {
                tmp+= this->cache[r++];
            }

            //确定为保留字
            for(int i =0 ;i< (int)this->reserved_words.rw.size(); ++i)
            {
                if(this->reserved_words.rw[i] == tmp)
                {
                    id = RW;
                    x = STARTRW + i;
                    goto maintain;
                }
            }
            //否则为标识符
            for(int i =0 ;i< (int)this->identifier.size() ; ++i)
            {
                if(this->identifier[i] == tmp)
                {
                    id = IDENTIFIER;
                    x = i;
                    goto maintain;
                }
            }

            // 为新标识符
            this->identifier.push_back(tmp);
            id = IDENTIFIER;
            x = (int)this->identifier.size() - 1;
            goto maintain;
        }
        //数字开头，为数字常量
        else if (isdigit(this->cache[r]))
        {
            while (isdigit(this->cache[r]))
                tmp += this->cache[r++];

            //确定为数字常量
            for(int i = 0 ; i < (int)this->constant.size();i++)
            {
                if (this->constant[i] == tmp)
                {
                    id =  CONSTANT;
                    x = i;
                    goto maintain;
                }
            }
            //为新数字常量
            this->constant.push_back(tmp);
            id = CONSTANT;
            x = (int)this->constant.size() - 1;
            goto maintain;
        }
        //其他情况，即为符号/其他字符
        else 
        {
            do
            {
                if (!isdigit(this->cache[r]) && !isalpha(this->cache[r]) && !isspace(this->cache[r]))
                    tmp += this->cache[r++];
                else
                    break;
            }while (find(this->reserved_words.rw.begin() ,this->reserved_words.rw.end() , tmp + this->cache[r] ) != this->reserved_words.rw.end());

            for (int i = this->reserved_words.get_start_symbol();i <(int) this->reserved_words.rw.size(); ++i)
            {
                if(this->reserved_words.rw[i] == tmp)
                {
                    id = SYMBOL;
                    x = STARTRW + i;
                    goto maintain;
                }
            }
            //出现错误
            fprintf(stderr,"Symbols that do not exist: %s\n",tmp.c_str());
            FILE *f = fopen("../errFiles/lexicalErr.err","w");
            fprintf(f,"Symbols that do not exist: %s %d %d\n",tmp.c_str(),l,r);
            fclose(stdin);
            fclose(stdout);
            
        }
    maintain:
        //更新tot_l与tot_r
        tot_r = tot_l + r -l;
        json tmp_j = {
            {"id", this->jsons.size()},
		    {"value", tmp},
		    {"lx", id},
		    {"bh", x},
		    {"l", tot_l},
		    {"r", tot_r}
        };
        this->jsons.push_back(tmp_j);
        //过滤不可见字符
        while (r< this->max_cache && isspace(this->cache[r])){r++;tot_r++;}
        tot_l = tot_r;
        //如果 r == max_cache 则读到文章尾
        if (r >= this->max_cache)
            break;
        //更新cache 与l,r
        if (r >= this->DIVCACHE)
        {
            r -= this->DIVCACHE;
            //max_cache != 240 说明已经被改变过,也即已读到文章尾, 并且没被搬到第一cache
            if(this->max_cache !=CACHESIZE << 1 && this->max_cache >=CACHESIZE)
            {
                this->max_cache -= DIVCACHE;
            }
            for(int i = 0;i < DIVCACHE && i < this->max_cache ; ++i)
            {
                this->cache[i] = cache[i+DIVCACHE] ;
            }
            for(int i = DIVCACHE ; i< this->max_cache; i++)
            {
                if((this->cache[i] = getchar())== EOF )
                {
                    this->max_cache = i;
                    break;
                }
            }
        }
        l = r;
    }
    

    json j_vec(this->jsons);
    cout<<j_vec;

    // fclose(stdin);
	// fclose(stdout);
    freopen("CON", "r", stdin);
    freopen("CON", "w", stdout);
    cout<<"end sovle" << endl;
	return;
}

void lexicalAnalyzer::out_rw()
{
    ofstream out_file;
    out_file.open("../tableFiles/reservedWords.table.json");
    vector <json> jsons;
    jsons.clear();
    for( int i=0; i < this->reserved_words.get_start_symbol(); ++i)
    {
        jsons.push_back({
            {"value",this->reserved_words.rw[i]},
            {"id", i + STARTRW}
        });
    }
    json j_vec(jsons);
    out_file << j_vec;
    out_file.close();
    return;
}

void lexicalAnalyzer::out_symbol()
{
    ofstream out_file;
	out_file.open("../tableFiles/symbol.table.json");
	vector<json> jsons;
	jsons.clear();
    for (int i = this->reserved_words.get_start_symbol(); i < (int)this->reserved_words.rw.size(); i++)
    {
        jsons.push_back({
            {"value",this->reserved_words.rw[i]},
            {"id", i + STARTRW}
        });
    }
    json j_vec(jsons);
    out_file<< j_vec;
    out_file.close();
    return;
    
}

void lexicalAnalyzer::out_identifier()
{
    ofstream out_file;
	out_file.open("../tableFiles/identifier.table.json");
	vector <json> jsons;
	jsons.clear();
	for (int i = 0; i < (int)this->identifier.size(); i++)
		jsons.push_back({
			{"value", this->identifier[i]},
			{"id", i}
		});
	json j_vec(jsons);
	out_file << j_vec;
	out_file.close();
	return;
}

void lexicalAnalyzer::out_constant()
{
    ofstream out_file;
	out_file.open("../tableFiles/constant.table.json");
	vector <json> jsons;
	jsons.clear();
	for (int i = 0; i < (int)this->constant.size(); i++)
		jsons.push_back({
			{"value", this->constant[i]},
			{"id", i}
		});
	json j_vec(jsons);
	out_file << j_vec;
	out_file.close();
	return;
}

void lexicalAnalyzer::out_table()
{
    this->out_rw();
    this->out_symbol();
    this->out_identifier();
    this->out_constant();
}


lexicalAnalyzer::lexicalAnalyzer(/* args */)
{
}

lexicalAnalyzer::~lexicalAnalyzer()
{
}