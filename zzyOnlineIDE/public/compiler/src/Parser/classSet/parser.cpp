#include "parser.h"

void Parser::parse_err(char const* err,int t)
{
    fprintf(stderr,"%s on %d ", err,this->tmp_lexical_nodes[t]->l);
    fputs(this->tmp_lexical_nodes[t]->value.c_str(),stderr);
    FILE *f = fopen("../errFiles/parseErr.err", "w");
    fprintf(f, "%s on %d",err,this->tmp_lexical_nodes[t]->l);
    fputs(this->tmp_lexical_nodes[t]->value.c_str(),f);
    fclose(f);
    exit(EXIT_FAILURE);
}

void Parser::init(const vector<lexicalNode*> &lexical_nodes)
{
    this->t = 0;
    this->tmp_lexical_nodes = lexical_nodes;
    this->codes = new vector<Code*>();
    this->root_table = this->now_table = new Table("main", nullptr, 0);

    ifstream infile;
    infile.open("../inFiles/opr.json");
	infile >> this->opr_table;
	infile.close();

    return;
}


void Parser::out()
{
    ofstream out_file;
    out_file.open("../jsonFiles/semanticAns.json");

    vector<json> jsons;
	jsons.clear();
	for (int i = 0; i < (int)codes->size(); i++)
		jsons.push_back({
			{"id", i},
			{"f", (*codes)[i]->f},
			{"l", (*codes)[i]->l},
			{"a", (*codes)[i]->a}
		});
	json j_vec(jsons);
	out_file << j_vec;
	
	out_file.close();
	return;
}

void Parser::try_push_identifier(string name)
{
    if (Table::can_push(name,this->now_table))
        this->now_table->var_table->push_back(new TableItem(name,this->now_table->lev,this->now_table->var_table->size()));
    else
        parse_err(("Redefining variables" + name).c_str(),this->t);//重复定义变量
}

void Parser::try_LITLOD(string name)
{
    pair<string,pair<int,int>> find = Table::find_identifier(name,this->now_table);
    if(find.first == "const")
    {
        this->codes->push_back(new Code("LIT",0,find.second.first));
        return;
    }

    if(find.first == "var")
    {
        this->codes->push_back(new Code("LOD",find.second.first,find.second.second));
        return;
    }

    parse_err(("Undefined variable"+name).c_str(),this->t);//未定义的变量
    return;
}



void Parser::bfs(ParserTreeNode *x)
{
    queue<pair<ParserTreeNode*,int>> q;
    vector<json> jsons;
    while (!q.empty())
		q.pop();
    q.push(make_pair(x, -1));// pair<节点, 父亲编号>
    while (!q.empty())
    {
        pair<ParserTreeNode*,int> u = q.front();//弹出队列中第一个
        q.pop();

        ParserTreeNode *x = u.first;//得到该节点
        for (int i = 0;i < (int)u.first->son->size();++i)
        {
            q.push(make_pair(x->son->at(i),jsons.size()));
        }

        jsons.push_back({
			{"id", jsons.size()},
			{"l", x->l},
			{"r", x->r},
			{"codel", x->code_l},
			{"coder", x->code_r},
			{"value", x->value},
			{"lx", x->type_name},
			{"pid", u.second},
		});
    }
    
    ofstream ofile;
    ofile.open("../jsonFiles/parseAns.json");
    json j_vec(jsons);
	ofile << j_vec;
	return;
}

void Parser::get_root(const vector<lexicalNode*> &lexical_nodes)
{
    this->root=this->program(lexical_nodes);
}

void Parser::bfs_from_root()
{
    this->bfs(this->root);
}

ParserTreeNode *Parser:: program(const vector<lexicalNode*> &lexical_nodes)
{
    this->init(lexical_nodes);

    ParserTreeNode *p = new ParserTreeNode(nullptr,0,(int)this->tmp_lexical_nodes.size(),"program");//程序
    p->code_l = this->codes->size();
    this->codes->push_back(new Code("JMP",0,0));

    p->son->push_back(this->block(p));

    if(this->tmp_lexical_nodes[this->t]->value != ".")
        this->parse_err("Missing '.' at end of program",this->t);//程序末尾缺少'.'
    
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    if(this->t < (int)this->tmp_lexical_nodes.size())
    {
        this->parse_err("There is still code after 'end.",this->t);//"在 'end.' 之后仍有代码"
    }
    p->code_r = this->codes->size();
    
    this->out();
    return p;
}

ParserTreeNode *Parser::block(ParserTreeNode *f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"block");//分程序
    p->code_l = codes->size();

    pair<string,pair<ul,ul>> find;
    //进入常量声明
    if(this->tmp_lexical_nodes[this->t]->value == "const")
    {
        p->son->push_back(this->constant_declaration(p));
    }
    //进入变量声明
    if(this->tmp_lexical_nodes[this->t]->value == "var")
    {
        p->son->push_back(this->variable_declaration(p));
    }
    //进入过程声明
    if(this->tmp_lexical_nodes[this->t]->value == "procedure")
    {
        p->son->push_back(this->procedure_declaration(p));
    }

    if(this->now_table->f)
    {
        find = Table::find_identifier(this->now_table -> pro_name, this->now_table->f);
        if (find.first != "procedure")//应认为此语句永不执行
            this->parse_err(("This is not a procedure name" + this->now_table->pro_name).c_str(),this->t);//这不是一个过程名
        
        this->now_table->f->pro_table->back()->adr = this->codes->size();
    }
    else
    {
        (*this->codes)[0]->a = this->codes->size();
    }
    this->codes->push_back(new Code("INT",0,this->now_table->var_table->size()));

    p->son->push_back(this->statement(p));

    this->codes->push_back(new Code("OPR",0,this->opr_table["return"]));

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::constant_declaration(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,t,0,"constant_declaration");//常量说明
    p->code_l = this->codes->size();

    if(this->tmp_lexical_nodes[this->t]->value != "const")
        this->parse_err("Constant indicates missing 'const' in front",this->t);//常量说明首部缺少 'const'
    
    p->son->push_back(new ParserTreeNode(p,this->t, this->t + 1, "reserved words", "const"));//保留字
    this->t++;
    if(this->tmp_lexical_nodes[this->t]->lx != IDENTIFIER)
        this->parse_err("Definition of a constant less than one",this->t);//"小于一个的常量定义"
    p->son->push_back(this->constant_definition(p));

    //{,常量定义}
    while (this->tmp_lexical_nodes[this->t]->value == ",")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",","));//符号
        this->t++;
        p->son->push_back(this->constant_definition(p));
    }

    if(this->tmp_lexical_nodes[t]->value == ";")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",";"));//符号
        this->t++;
    }
    else
    {
        if(this->tmp_lexical_nodes[this->t]->lx == IDENTIFIER)
            this->parse_err("Constant definitions are not separated by ','",this->t);//常量定义之间没有使用 ',' 分隔
        else
            this->parse_err("Constant indicates that part of the statement is missing ';'",this->t);//常量说明部分语句缺少 ';'
    }

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::variable_declaration(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,t,0,"variable declaration");//变量说明
    p->code_l = this->codes->size();
    
    string name;

    if(this->tmp_lexical_nodes[this->t]->value != "var")
        parse_err("Variable description missing 'var' in header",t);//变量说明首部缺少 'var'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words","var"));//保留字
    this->t++;

    //标识符
    if(this->tmp_lexical_nodes[this->t]->lx != IDENTIFIER)
        parse_err("Less than one variable definition",this->t);//小于一个的变量定义
    
    name = this->tmp_lexical_nodes[this->t]->value;
    p->son->push_back(this->identifier(p));
    this->try_push_identifier(name);

    //{,标识符}
    while (this->tmp_lexical_nodes[this->t]->value == ",")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",","));//符号
        this->t++;

        name = this->tmp_lexical_nodes[this->t]->value;
        p->son->push_back(this->identifier(p));
        this->try_push_identifier(name);
    }

    if(this->tmp_lexical_nodes[this->t]->value == ";")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",";"));//符号
        this->t++;
    }
    else
    {
        if(this->tmp_lexical_nodes[this->t]->lx == IDENTIFIER)
            parse_err("There is no ',' separation between variable definitions",this->t);//变量定义之间没有使用 ',' 分隔
        else if (this->tmp_lexical_nodes[this->t]->value == "=")
            parse_err("You may not assign values to variables in the variable description section",this->t);//不可在变量说明部分为变量赋值
        else 
            parse_err("Variable description Some statements are missing ';'",this->t);//变量说明部分语句缺少 ';' 
    }

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;

}

ParserTreeNode *Parser::procedure_declaration(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,t,0,"procedure declaration");//过程说明
    p->code_l = this->codes->size();

    do
    {
        p->son->push_back(this->procedure_header(p));
        p->son->push_back(this->block(p));
        if(this->tmp_lexical_nodes[this->t]->value != ";")
            parse_err("Procedure description missing after end ';'",this->t);//过程说明结束后缺少 ';'
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",";"));//符号
        this->t++;
        this->now_table = this->now_table->f;
    } while (this->tmp_lexical_nodes[this->t]->value == "procedure");

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;  
}

ParserTreeNode *Parser::statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"statement");//语句
    p->code_l = this->codes->size();

    if(this->tmp_lexical_nodes[this->t]->lx == IDENTIFIER)
        p->son->push_back(this->assignment_statement(p));
    else if(this->tmp_lexical_nodes[this->t]->value == "if")
        p->son->push_back(this->conditional_statement(p));
    else if(this->tmp_lexical_nodes[this->t]->value == "while")
        p->son->push_back(this->while_loop(p));
    else if(this->tmp_lexical_nodes[this->t]->value == "call")
        p->son->push_back(this->procedure_call_statement(p));
    else if(this->tmp_lexical_nodes[this->t]->value == "read")
        p->son->push_back(this->read_statement(p));
    else if(this->tmp_lexical_nodes[this->t]->value == "write")
        p->son->push_back(this->write_statement(p));
    else if(this->tmp_lexical_nodes[this->t]->value == "begin")
        p->son->push_back(this->compound_statement(p));
    
    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::constant_definition(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"constant definition");//常量定义
    p->code_l = this->codes->size();

    string name,value;
    //标识符
    if(this->tmp_lexical_nodes[this->t]->lx != IDENTIFIER)
        parse_err("Constant lvalue must be a valid identifier name",this->t);//常量左值必须为合法的标识符名
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"identifier",name = this->tmp_lexical_nodes[this->t]->value));//标识符
    this->t++;

    // =
    if(this->tmp_lexical_nodes[this->t]->value != "=")
    {
        if(this->tmp_lexical_nodes[this->t]->lx == CONSTANT)
            parse_err("Constant definitions must be linked with initial values by '='",this->t);//常量定义与初值之间必须以 '=' 链接
        else
            parse_err("Constant definitions must be initialized",this->t);//常量定义必须初始化
    }
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol","="));//符号
    this->t++;

    //常量
    if(this->tmp_lexical_nodes[this->t]->lx != CONSTANT)
        parse_err("Constants must be initialized as unsigned integers",this->t);//常量必须初始化为无符号整数
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"constant",value = this->tmp_lexical_nodes[this->t]->value));//常量
    this->t++;

    if(Table::can_push(name,this->now_table))
        this->now_table->const_table->push_back(new TableItem(name,atoi(value.c_str()),0));
    else
        parse_err(("Redefining constants"+name).c_str(),this->t);//重复定义常量
    
    p->code_r=this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::identifier(ParserTreeNode* f)
{
    if(this->tmp_lexical_nodes[this->t]->lx != IDENTIFIER)
        parse_err("There should be an identifier",this->t);//此处应有一标识符
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"identifier",this->tmp_lexical_nodes[this->t]->value);//标识符
    p->code_l = this->codes->size();
    this->t++;

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::procedure_header (ParserTreeNode* f)
{
	ParserTreeNode *p = new ParserTreeNode(f,this->t, 0, "procedure header");//过程首部
	p->code_l =this->codes->size();
	
	string name;
	
	if (this->tmp_lexical_nodes[this->t]->value != "procedure")
		parse_err("Procedure header missing 'procedure'", this->t);//过程首部缺少 'procedure'
	p->son->push_back(new ParserTreeNode(p, this->t, this->t + 1, "reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
	this->t++;
	
	if (this->tmp_lexical_nodes[this->t]->lx != IDENTIFIER)
		parse_err("Procedure names are not valid identifiers", this->t);//过程名不是合法的标识符
	p->son->push_back(new ParserTreeNode(p, this->t, this->t + 1, "identifier",name = this->tmp_lexical_nodes[this->t]->value));//标识符
	this->t++;
	
	if (this->tmp_lexical_nodes[this->t]->value == ";")
	{
		p->son->push_back(new ParserTreeNode(p, this->t, this->t + 1, "symbol", ";"));//符号
		this->t++;
	}
	else
		parse_err("Procedure header statement missing ';'", this->t);//过程首部语句缺少 ';' 
	
	if (Table::can_push(name, this->now_table))
		this->now_table->pro_table->push_back(new TableItem(name, this->now_table->lev, 0));
	else
		parse_err(("Redefinition process" + name).c_str(), this->t);//重复定义过程
	
	this->now_table = new Table(name, this->now_table, this->now_table->lev);
	
	p->code_r = this->codes->size();
	p->r = t;
	return p;
}

ParserTreeNode *Parser::assignment_statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"assignment statement");//赋值语句
    p->code_l = this->codes->size();

    string name;
    pair<string,pair<ul,ul>> find;

    if(this->tmp_lexical_nodes[this->t]->lx !=IDENTIFIER)
        parse_err("An assignment statement lvalue is not an identifier",this->t);//赋值语句左值不是标识符
    name = this->tmp_lexical_nodes[this->t]->value;
    find = Table::find_identifier(name,now_table);
    if(find.first == "")
        parse_err("An undefined identifier",this->t);//未定义的标识符
    if(find.first == "const")
        parse_err("Cannot assign to a constant",this->t);//无法向常量赋值
    if(find.first == "procedure")
        parse_err("Cannot assign a value to a procedure",this->t);//无法向过程赋值

    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"identifier",this->tmp_lexical_nodes[this->t]->value));//标识符
    this->t++;

    if(this->tmp_lexical_nodes[this->t]->value != ":=")
        parse_err("Assignment operator error",this->t);//赋值操作符错误
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    p->son->push_back(this->expression(p));

    this->codes->push_back(new Code("STO",find.second.first,find.second.second));

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::compound_statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"compound statement");//复合语句
    p->code_l = this->codes->size();
    if(this->tmp_lexical_nodes[this->t]->value != "begin")
        parse_err("Compound statement missing 'begin'",this->t);//复合语句缺少 'begin'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    p->son->push_back(this->statement(p));
    while(this->tmp_lexical_nodes[this->t]->value == ";")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
        this->t++;
        p->son->push_back(this->statement(p));
    }

    if(this->tmp_lexical_nodes[this->t]->value != "end")
        parse_err("Compound statement missing 'end' or statement missing ';'",this->t);//复合语句缺少 'end' 或 语句缺少 ';'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::conditional_statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"conditional statement");//条件语句
    p->code_l = this->codes->size();
    if(this->tmp_lexical_nodes[this->t]->value !="if")
        parse_err("Conditional statement missing 'if'",this->t);//条件语句缺少 'if'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    p->son->push_back(this->condition(p));

    if(this->tmp_lexical_nodes[this->t]->value != "then")
        parse_err("Conditional statements missing 'then'",this->t);//条件语句缺少 'then'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    this->codes->push_back(new Code("JPC",0,0));
    Code *jpc = this->codes->back();

    p->son->push_back(this->statement(p));

    jpc->a = this->codes->size();

    p->code_r = this->codes->size();
    p->r = this->t;
    return p; 
}

ParserTreeNode *Parser::condition(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"condition");//条件
    p->code_l = this->codes->size();
    ParserTreeNode *son;

    if(this->tmp_lexical_nodes[this->t]->value == "odd")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
        this->t++;
        p->son->push_back(this->expression(p));
    }
    else
    {
        p->son->push_back(this->expression(p));
        p->son->push_back(son = this->relational_operator(p));//关系算符
        p->son->push_back(this->expression(p));
        this->codes->push_back(new Code("OPR",0,this->opr_table[son->value]));
    }

    p->code_r = this->codes->size();
    p->r = t;
    return p;
}

ParserTreeNode *Parser::expression(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"expression");//表达式
    p->code_l = this->codes->size();

    if (this->tmp_lexical_nodes[this->t]->value == "+" || this->tmp_lexical_nodes[this->t]->value == "-")
    {
        string symbol = this->tmp_lexical_nodes[this->t]->value;
        p->son->push_back(this->add_and_subtract_operator(p));
        this->t++;
        if(symbol == "-")
        {
            this->codes->push_back(new Code("LIT",0,0));
            p->son->push_back(this->item(p));
            this->codes->push_back(new Code("OPR",0,this->opr_table["-"]));
        }
    }
    else
        p->son->push_back(this->item(p));
    
    while (this->tmp_lexical_nodes[this->t]->value == "+" || this->tmp_lexical_nodes[this->t]->value == "-")
    {
        string symbol = this->tmp_lexical_nodes[this->t]->value;
        p->son->push_back(this->add_and_subtract_operator(p));
        p->son->push_back(this->item(p));
        this->codes->push_back(new Code("OPR",0,this->opr_table[symbol.c_str()]));
    }

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;   
}

ParserTreeNode *Parser::item(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"item");//项
    p->code_l = this->codes->size();

    p->son->push_back(this->factor(p));

    while(this->tmp_lexical_nodes[this->t]->value == "*" || this->tmp_lexical_nodes[this->t]->value == "/")
    {
        string symbol = this->tmp_lexical_nodes[this->t]->value;
        p->son->push_back(this->multiply_divide_operator(p));
        p->son->push_back(this->factor(p));
        this->codes->push_back(new Code("OPR",0,this->opr_table[symbol]));
    }

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::factor(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"factor");//因子
    p->code_l = this->codes->size();

    if(this->tmp_lexical_nodes[this->t]->lx == IDENTIFIER)
    {
        string name= this->tmp_lexical_nodes[this->t]->value;
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"identifier",this->tmp_lexical_nodes[this->t]->value));//标识符
        this->t++;

        this->try_LITLOD(name);
    }
    else if(this->tmp_lexical_nodes[this->t]->lx == CONSTANT)
    {
        string value = this->tmp_lexical_nodes[this->t]->value;
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"constant",this->tmp_lexical_nodes[this->t]->value));//常量
        this->t++;

        this->codes->push_back(new Code("LIT",0,atoi(value.c_str())));
    }
    else if(this->tmp_lexical_nodes[this->t]->value == "(")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
        this->t++;

        p->son->push_back(this->expression(p));

        if(this->tmp_lexical_nodes[this->t]->value != ")")
            parse_err("No matching ')'",this->t);//没有匹配的 ')'
        
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
        this->t++;
    }
    else
        parse_err("Illegal factor",this->t);//不合法的因子

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::add_and_subtract_operator(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"add_and_subtract operator",this->tmp_lexical_nodes[this->t]->value);//加减算符
    p->code_l = this->codes->size();
    if(this->tmp_lexical_nodes[this->t]->value != "+" && this->tmp_lexical_nodes[this->t]->value != "-")
        parse_err("Non-addition and subtraction operators",this->t);//非加减算符
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::multiply_divide_operator(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"multiply_divide operator",this->tmp_lexical_nodes[this->t]->value);//乘除算符
    p->code_l = this->codes->size();

    if(this->tmp_lexical_nodes[this->t]->value != "*" && this->tmp_lexical_nodes[this->t]->value != "/")
        parse_err("Nonmultiplication and division operators",this->t);//非乘除算符
    p->son->push_back(new ParserTreeNode(p, this->t, this->t+1, "symbol", this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::relational_operator(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"relational operator",this->tmp_lexical_nodes[this->t]->value);//关系算符
    p->code_l = this->codes->size();

    const string relationalOperator[] = {"=","#","<","<=",">",">="};
    for (int i = 0; i < 6; ++i)
    {
        if(this->tmp_lexical_nodes[this->t]->value == relationalOperator[i])
        {
            p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
            this->t++;

            p->code_r = this->codes->size();
            p->r = t;
            return p;
        }
    }
    parse_err("Nonrelational operators",this->t);//非关系算符'
    return p;
}

ParserTreeNode *Parser::procedure_call_statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"procedure_call statement");//过程调用语句
    ParserTreeNode *son = nullptr;
    p->code_l = this->codes->size();

    pair<string,pair<ul,ul>> find;

    if(this->tmp_lexical_nodes[this->t]->value != "call")
        parse_err("Conditional statement missing 'call'",this->t);//条件语句缺少 'call'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    if(this->tmp_lexical_nodes[this->t]->lx == IDENTIFIER)
    {
        p->son->push_back(son = new ParserTreeNode(p,this->t,this->t+1,"identifier",this->tmp_lexical_nodes[this->t]->value));//标识符
        this->t++;
    }
    else
        parse_err("Missing invoked procedures",this->t);//

    find = Table::find_identifier(son->value,this->now_table);
    if(find.first == "procedure")
        this->codes->push_back(new Code("CAL",find.second.first,find.second.second));
    else if(find.first == "const")
        parse_err("Cannot call a constant",this->t);//无法调用一个常量
    else if(find.first == "var")
        parse_err("A variable cannot be called",this->t);//无法调用一个变量
    else if(find.first == "")
        parse_err(("Undefined procedure"+son->value).c_str(),this->t);//未定义的过程
    
    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::while_loop(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"while_loop");//当型循环
    p->code_l = this->codes->size();

    if(this->tmp_lexical_nodes[this->t]->value != "while")
        parse_err("When loop missing 'while'",this->t);//当型循环缺少 'while'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    ul m = this->codes->size();
    p->son->push_back(this->condition(p));
    this->codes->push_back(new Code("JPC",0,0));
    Code *jpc = this->codes->back();
    if(this->tmp_lexical_nodes[this->t]->value != "do")
        parse_err("When loop lacks 'do'",this->t);//当型循环缺少 'do'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    p->son->push_back(this->statement(p));
    this->codes->push_back(new Code("JMP",0,m));
    jpc->a = this->codes->size();

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::read_statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"read statement");//读语句
    p->code_l = this->codes->size();

    ParserTreeNode *son;
    pair<string,pair<ul,ul>> find;

    if(this->tmp_lexical_nodes[this->t]->value != "read")
        parse_err("Read statement missing 'read'",this->t);//读语句缺少 'read'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    if(this->tmp_lexical_nodes[this->t]->value != "(")
        parse_err("Read statement missing '('",this->t);//读语句缺少 '('
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    p->son->push_back(son = identifier(p));
    find = Table::find_identifier(son->value, this->now_table);
    if (find.first == "")
        parse_err(("Undefined variable"+son->value).c_str(),this->t);//未定义的变量
    this->codes->push_back(new Code("OPR",0,this->opr_table["read"]));
    this->codes->push_back(new Code("STO",find.second.first,find.second.second));

    while(this->tmp_lexical_nodes[this->t]->value == ",")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
        this->t++;
        p->son->push_back(son = this->identifier(p));
        find = Table::find_identifier(son->value,this->now_table);
        if(find.first == "")
            parse_err(("Undefined variable"+son->value).c_str(),this->t);//未定义的变量
        this->codes->push_back(new Code("OPR",0,this->opr_table["read"]));
        this->codes->push_back(new Code("STO",find.second.first,find.second.second));
    }

    if(this->tmp_lexical_nodes[this->t]->value != ")")
        parse_err("No matching ')'",this->t);//没有匹配的 ')'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}

ParserTreeNode *Parser::write_statement(ParserTreeNode* f)
{
    ParserTreeNode *p = new ParserTreeNode(f,this->t,0,"write statement");//写语句
    p->code_l = this->codes->size();

    if(this->tmp_lexical_nodes[this->t]->value != "write")
        parse_err("Write statement missing 'write'",this->t);//写语句缺少 'write'
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"reserved words",this->tmp_lexical_nodes[this->t]->value));//保留字
    this->t++;

    if(this->tmp_lexical_nodes[this->t]->value != "(")
        parse_err("Write statement missing '('",this->t);//写语句缺少 '('
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    if(this->tmp_lexical_nodes[this->t]->value == ")")
        parse_err("Variables that are not written",this->t);//没有被写的变量
    p->son->push_back(this->expression(p));
    this->codes->push_back(new Code("OPR",0,this->opr_table["write"]));
    while (this->tmp_lexical_nodes[this->t]->value == ",")
    {
        p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
        this->t++;
        p->son->push_back(this->expression(p));
        this->codes->push_back(new Code("OPR",0,this->opr_table["write"]));
    }

    if(this->tmp_lexical_nodes[this->t]->value != ")")
        parse_err("No matching ')'",this->t);
    p->son->push_back(new ParserTreeNode(p,this->t,this->t+1,"symbol",this->tmp_lexical_nodes[this->t]->value));//符号
    this->t++;

    p->code_r = this->codes->size();
    p->r = this->t;
    return p;
}