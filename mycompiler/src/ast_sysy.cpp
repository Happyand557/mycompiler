#include"ast_sysy.h"
#include<stdio.h>
#include<string>
#include<fstream>
#include<sstream>
#include <regex>
#include <vector>
#include<string.h>
#include"parser.tab.hpp"
//TODO 加减乘除函数的修改，函数返回的修改包括跳转
extern FILE *sysyin;
extern FILE *sysyout;

//数组前面星号未解决
AST *root_sysy;
TABLE *root_symtable;
std::vector<TABLE *> symtable_vector;
TABLE * symtable_ptr;
int func_begin_t;
int return_l;
int return_t;
int op_t;
int array_t;
int lvalArray_t1;
int lvalArray_t2;
std::vector <std::string> vectorArray;
std::vector <std::string> condition;
int G_i = 0;
int t_i = 0;    //temp var
int indent = 0; //global indent
int label = 0;  //global label
int symtable_i = 1; //下一个要打开的符号表编号
int label_in_global;   //最内层代码块的进入标号
int label_out_global;  
bool wait_for_pointer = false;  //用于判断对于数组的引用是否生成指针

static void irgen(AST *th);
static void irgen_Decl(AST *th);
static void irgen_FuncDef(AST *th);
static void irgen_Block(AST *th);
static void irgen_Stmt(AST *th);
static void irgen_ConstInitVal(AST *th, int addr, int layer, ENTRY_VAL *e);
static void irgen_InitVal(AST *th, int addr, int layer, ENTRY_VAL *e);
static std::string irgen_AddExp(AST *th);
static std::string irgen_MulExp(AST *th);
static std::string irgen_UnaryExp(AST *th);
static std::string irgen_LVal(AST *th, bool isleft);
static void irgen_LOrExp(AST *th, int label_true, int label_false);
static void irgen_LAndExp(AST *th, int label_false);
static std::string irgen_EqExp(AST *th);
static std::string irgen_RelExp(AST *th);

bool TABLE::Find(bool isVal, std::string id, bool recursive){
    if(isVal){
        for(int i=0;i<this->val.size();i++){
            if(id == this->val[i]->id){
                return true;
            }
        }
        if(recursive){
            if(this != root_symtable){
                return this->father->Find(isVal,id,recursive);
            }
        }
    } else{
        for(int i=0;i<this->func.size();i++){
            if(id == this->func[i]->id){
                return true;
            }
        }
    }
    return false;
}

ENTRY * TABLE::FindAndReturn(bool isVal, std::string id){
    if(isVal){
        for(int i=0;i<this->val.size();i++){
            if(id == this->val[i]->id){
                return this->val[i];
            }
        }
        if(this != root_symtable){
            return this->father->FindAndReturn(isVal,id);
        }
    } else{
        for(int i=0;i<this->func.size();i++){
            if(id == this->func[i]->id){
                return this->func[i];
            }
        }
    }
}

static void print_indent(){
    for(int indent_temp=0;indent_temp<indent;indent_temp++){
        fprintf(sysyout,"  ");
    }
}

static void print_decl(TABLE *table, int numberoftemp){
    //作用域中的变量打印
    for(int i=0;i<table->val.size();i++){
        if(table->val[i]->isParam){
            table->val[i]->eeyore_id = "%l"+std::to_string(t_i);
            t_i++;
        } else{
            if(table == root_symtable) {
                table->val[i]->eeyore_id = "@g"+std::to_string(G_i);
                G_i++;
            }
            else {
                table->val[i]->eeyore_id = "%l"+std::to_string(t_i);
                t_i++;
            }
        }
        if(table->val[i]->isArray){
        print_indent();
        fprintf(sysyout,"declare i32 %s", table->val[i]->eeyore_id.c_str());
        for(auto shape : table->val[i]->shape)
        {
            fprintf(sysyout,"[%d]", shape);
        }
        fprintf(sysyout,"\n");
        } else{
        print_indent();
        fprintf(sysyout,"declare i32 %s\n", table->val[i]->eeyore_id.c_str());
        }
    }
    //这里在函数内部默认变量所有都需要打印
    if(table != root_symtable){
        for(int i=0;i<table->son.size();i++){
            print_decl(table->son[i],0);
        }
    }
    //打印中间变量
    int t_i_temp = t_i;
    for(int i=0;i<numberoftemp;i++){
        print_indent();
        fprintf(sysyout,"declare i32 %%t");
        fprintf(sysyout,"%d\n",t_i);
        t_i++;
    }
    t_i = t_i_temp;
}
/*
static void print_decl(TABLE *table, int numberoftemp){
    for(int i=0;i<table->val.size();i++){
        if(table->val[i]->isParam){
            table->val[i]->eeyore_id = "p"+std::to_string(t_i);
            t_i++;
        } else{
            table->val[i]->eeyore_id = "T"+std::to_string(t_i);
            t_i++;
            if(table->val[i]->isArray){
                print_indent();
                fprintf(sysyout,"var %d %s\n", table->val[i]->size, table->val[i]->eeyore_id.c_str());
            } else{
                print_indent();
                fprintf(sysyout,"var %s\n", table->val[i]->eeyore_id.c_str());
            }
        }
    }
    if(table != root_symtable){
        for(int i=0;i<table->son.size();i++){
            print_decl(table->son[i],0);
        }
    }
    int t_i_temp = t_i;
    for(int i=0;i<numberoftemp;i++){
        print_indent();
        fprintf(sysyout,"var t%d\n",t_i);
        t_i++;
    }
    t_i = t_i_temp;
}
*/
static std::string irgen_LVal(AST *th, bool isleft){
    if(th->son.size() == 1){
        return ((ENTRY_VAL *)th->son[0]->entry)->eeyore_id;
    } else{
        std::string val1, val2, val3;
        ENTRY_VAL *entry_temp = (ENTRY_VAL *)th->son[0]->entry;
        int size_temp = entry_temp->size;
        val1 = "%t"+std::to_string(t_i);
        t_i++;
        if(th->son.size() > 2){
            val3 = "%t"+std::to_string(t_i);
            t_i++;
        }
        for(int i=1;i<th->son.size();i++){
            size_temp /= entry_temp->shape[i-1];
            val2 = irgen_AddExp(th->son[i]->son[0]);
            if(i==1){
                if(val2[0]!='%') {
                    print_indent();
                    fprintf(sysyout,"%%l%d = %s\n",op_t, val2.c_str());
                    print_indent();
                    fprintf(sysyout,"%%t%d = mul %%l%d,%d\n",array_t,op_t,size_temp);
                }
                else {//这里应该不会到达
                    print_indent();
                    fprintf(sysyout,"%s = mul %s,%d\n",val1.c_str(),val2.c_str(),size_temp);
                }
            } else{
                if(val2[0]!='%') {
                    print_indent();
                    fprintf(sysyout,"%%l%d = %s\n",op_t, val2.c_str());
                    print_indent();
                    fprintf(sysyout,"%s = mul %%l%d,%d\n",val3.c_str(),op_t,size_temp);
                }
                else {
                    print_indent();
                    fprintf(sysyout,"%s = mul %s,%d\n",val3.c_str(),val2.c_str(),size_temp);
                }
                //print_indent();
                //fprintf(sysyout,"%s = mul %s,%d\n",val3.c_str(),val2.c_str(),size_temp);
                print_indent();
                fprintf(sysyout,"%%t%d = add %%t%d,%s\n",array_t,array_t,val3.c_str());
            }
        }
        print_indent();
        fprintf(sysyout,"%s = add %s,%%t%d\n",val1.c_str(),entry_temp->eeyore_id.c_str(),array_t);
        if(wait_for_pointer){
            return val1;
        }
        if(isleft){
            vectorArray.push_back(val1);
            return "*" + val1;

        } else{
            //print_indent();
            fflush(sysyout);
            vectorArray.push_back(val1);
            val1 = "*" + val1;
           // fprintf(sysyout,"%s = %s\n",val1.c_str(),val1.c_str());
            return val1;
        }
    }
}
//右值:立即数函数调用以及单目运算结合的立即数
static std::string irgen_UnaryExp(AST *th){
    std::string val1, val2;
    if(th->son[0]->type == _PrimaryExp){
        AST *ptr = th->son[0]; //PrimaryExp
        if(ptr->son[0]->type == _INT_CONST){
            //fprintf(sysyout,"");
            val1 = std::to_string(ptr->son[0]->val);
        } else if(ptr->son[0]->type == _LVal){
            val1 = irgen_LVal(ptr->son[0],false);
        } else{
            val1 = irgen_AddExp(ptr->son[0]->son[0]);
        }
    } else if(th->son[0]->type == _UnaryOp){
        if(th->son[0]->son[0]->op != '+'){
            val1 = "%t"+std::to_string(t_i);
            t_i++;
            val2 = irgen_UnaryExp(th->son[1]);
            print_indent();
            fprintf(sysyout,"%s = neg %s\n",val1.c_str(),val2.c_str());
        } else{
            val1 = irgen_UnaryExp(th->son[1]);
        }
    } else if(th->son[0]->type == _IDENT){
        if(root_symtable->Find(false,th->son[0]->id,false)){
            th->son[0]->entry = root_symtable->FindAndReturn(false,th->son[0]->id);
        }
        ENTRY_FUNC *func_temp = (ENTRY_FUNC *)th->son[0]->entry;
        int param_num = 0;
        std::vector<std::string> vector_param;
        if(th->son.size() == 2){
            param_num = th->son[1]->son.size();
            std::string params[param_num];
            for(int i=0;i<param_num;i++){
                if(func_temp->symtable){
                    std::string p_temp = "%t"+std::to_string(i);
                    for(int j=0;j<func_temp->symtable->val.size();j++){
                        if(func_temp->symtable->val[j]->isParam && p_temp == func_temp->symtable->val[j]->eeyore_id){
                            wait_for_pointer = func_temp->symtable->val[j]->isArray;
                        }
                    }
                } else{
                    if((func_temp->id == "getarray" && i == 0)
                        || (func_temp->id == "putarray" == 0 && i == 1)){
                            wait_for_pointer = true;
                    }
                }
                val1 = irgen_AddExp(th->son[1]->son[i]->son[0]);
                wait_for_pointer = false;
                params[i] = val1;
            }
            for(int i=0;i<param_num;i++){
                vector_param.push_back(params[i]);
                //fprintf(sysyout,"  param %s\n", params[i].c_str());
            }
        }
        if(func_temp->isreturn){
            val1 = "%t"+std::to_string(t_i);
            t_i++;
            fprintf(sysyout,"  %s = call i32 @%s(",val1.c_str(),func_temp->id.c_str());
        } else{
            t_i++;
            if(func_temp->id == "starttime"){
                fprintf(sysyout,"  param %d\n", th->lineno);
                fprintf(sysyout,"  call @sysy_starttime\n");
            } else if(func_temp->id == "stoptime"){
                fprintf(sysyout,"  param %d\n", th->lineno);
                fprintf(sysyout,"  call @sysy_stoptime\n");
            } else{
                fprintf(sysyout,"  call void @%s(",func_temp->id.c_str());
            }
        }
        for(int i=0; i < param_num;i++) {
            if(i != param_num - 1)
                fprintf(sysyout,"i32 %s,",vector_param[i].c_str());
            else
                fprintf(sysyout,"i32 %s",vector_param[i].c_str());
        }
        fprintf(sysyout,")\n");
    }
    return val1;
}
//需改乘除法
static std::string irgen_MulExp(AST *th){
    std::string val1, val2, val3;
    val1 = irgen_UnaryExp(th->son[0]);
    if(th->son.size() == 1){//只有一个unaryexp
        return val1;
    } else{
        val3 = "%t"+std::to_string(t_i);
        t_i++;
        for(int i=1;i<th->son.size();i+=2){
            val2 = irgen_UnaryExp(th->son[i+1]);
            if(i == 1){
                print_indent();
                switch (th->son[i]->op)
                {
                case '*':
                    if(val1[0]=='*' && val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mul %%t%d,%%t%d\n",val3.c_str(),lvalArray_t1 ,lvalArray_t2);
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mul %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mul %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                    }
                    else
                        fprintf(sysyout,"%s = mul %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    break;
                case '/':
                    if(val1[0]=='*' && val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = div %%t%d,%%t%d\n",val3.c_str(),lvalArray_t1 ,lvalArray_t2);
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = div %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = div %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                    }
                    else
                        fprintf(sysyout,"%s = div %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    //fprintf(sysyout,"%s = div %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    break;
                case '%':
                    if(val1[0]=='*' && val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mod %%t%d,%%t%d\n",val3.c_str(),lvalArray_t1 ,lvalArray_t2);
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mod %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mod %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                    }
                    else
                        fprintf(sysyout,"%s = mod %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    //fprintf(sysyout,"%s = mod %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    break;
                default:
                    break;
                }
            } else{
                print_indent();
                switch (th->son[i]->op)
                {
                case '*':
                    if(val2[0] == '*') {
                        fprintf(sysyout,"%%t%d = mul %s,%s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mul %s,%%t%d\n",val3.c_str(), val3.c_str(),lvalArray_t1);
                    }
                    else
                        fprintf(sysyout,"%s = mul %s,%s\n",val3.c_str(), val3.c_str(),val2.c_str());
                    break;
                case '/':
                    if(val2[0] == '*') {
                        fprintf(sysyout,"%%t%d = div %s,%s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = div %s,%%t%d\n",val3.c_str(), val3.c_str(),lvalArray_t1);
                    }
                    else
                        fprintf(sysyout,"%s = div %s,%s\n",val3.c_str(), val3.c_str(),val2.c_str());
                    break;
                case '%':
                    if(val2[0] == '*') {
                        fprintf(sysyout,"%%t%d = mod %s,%s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mod %s,%%t%d\n",val3.c_str(), val3.c_str(),lvalArray_t1);
                    }
                    else
                        fprintf(sysyout,"%s = mod %s,%s\n",val3.c_str(), val3.c_str(),val2.c_str());
                    break;
                default:
                    break;
                }
            }
        }
        return val3;
    }
}
//加减在这里修改
static std::string irgen_AddExp(AST *th){
    std::string val1, val2, val3;
    val1 = irgen_MulExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "%t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < th->son.size(); i+=2){
            val2 = irgen_MulExp(th->son[i+1]);
            if(i == 1){//区别前一个是var1还是var3
                print_indent();
                switch (th->son[i]->op)
                {
                case '+':
                    if(val1[0]=='*' && val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = add %%t%d,%%t%d\n",val3.c_str(),lvalArray_t1 ,lvalArray_t2);
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = add %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = add %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                    }
                    else
                        fprintf(sysyout,"%s = add %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    //fprintf(sysyout,"%s = add %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    break;
                case '-':
                    if(val1[0]=='*' && val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = sub %%t%d,%%t%d\n",val3.c_str(),lvalArray_t1 ,lvalArray_t2);
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = sub %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = sub %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                    }
                    else
                        fprintf(sysyout,"%s = sub %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    //fprintf(sysyout,"%s = sub %s,%s\n",val3.c_str(), val1.c_str(),val2.c_str());
                    break;
                default:
                    break;
                }
                
            } else{
                print_indent();
                switch (th->son[i]->op)
                {
                case '+':
                    if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = add %s,%%t%d\n",val3.c_str(), val3.c_str(),lvalArray_t1);
                    }
                    else
                        fprintf(sysyout,"%s = add %s,%s\n",val3.c_str(), val3.c_str(),val2.c_str());
                    break;
                case '-':
                    if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = sub %s,%%t%d\n",val3.c_str(), val3.c_str(),lvalArray_t1);
                    }
                    else
                        fprintf(sysyout,"%s = sub %s,%s\n",val3.c_str(), val3.c_str(),val2.c_str());
                    break;
                default:
                    break;
                }
            }
        }
        return val3;
    }
}

static void irgen_InitVal(AST *th, int addr, int layer, ENTRY_VAL *e){
    int nval = e->size/4;
    int nval_temp = 0;
    for(int i=0;i<layer;i++){
        nval /= e->shape[i];
    }
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->son.size() == 0){
            irgen_InitVal(th->son[i], addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        } else if(th->son[i]->son[0]->type == _Exp){
            if(symtable_ptr == root_symtable){
                print_indent();
                fprintf(sysyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, th->son[i]->son[0]->val);
                addr += 4;
                nval_temp++;
            } else{
                std::string init_temp = irgen_AddExp(th->son[i]->son[0]->son[0]);
                print_indent();
                fprintf(sysyout,"%s[%d] = %s\n", e->eeyore_id.c_str(), addr, init_temp.c_str());
                addr += 4;
                nval_temp++;
            }
        } else{
            irgen_InitVal(th->son[i],addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        }
    }
    for(;nval_temp<nval;nval_temp++){
        print_indent();
        fprintf(sysyout,"%s[%d] = 0\n", e->eeyore_id.c_str(), addr);
        addr += 4;
    }
}

static void irgen_ConstInitVal(AST *th, int addr, int layer, ENTRY_VAL *e){
    int nval = e->size/4;
    int nval_temp = 0;
    for(int i=0;i<layer;i++){
        nval /= e->shape[i];
    }
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->son.size() == 0){
            irgen_ConstInitVal(th->son[i],addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        } else if(th->son[i]->son[0]->type == _ConstExp){
            int init_temp = th->son[i]->son[0]->val;
            //e->arr[nval_temp] = init_temp;
            print_indent();
            fprintf(sysyout,"%s[%d] = %d\n", e->eeyore_id.c_str(), addr, init_temp);
            addr += 4;
            nval_temp++;
        } else{
            irgen_ConstInitVal(th->son[i], addr,layer+1,e);
            nval_temp += nval/e->shape[layer];
            addr += nval/e->shape[layer]*4;
        }
    }
    for(;nval_temp<nval;nval_temp++){
        //e->arr[nval_temp] = 0;
        print_indent();
        fprintf(sysyout,"%s[%d] = 0\n", e->eeyore_id.c_str(), addr);
        addr += 4;
    }
}

static std::string irgen_RelExp(AST *th){
    std::string val1, val2, val3, op;
    val1 = irgen_AddExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "%t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < th->son.size(); i+=2){
            if(th->son[i]->type == _LE){
                op = "le";
            } else if(th->son[i]->type == _GE){
                op = "ge";
            } else{
                switch (th->son[i]->op)
                {
                case '<':
                    op = "lt";
                    break;
                case '>':
                    op = "gt";
                    break;
                default:
                    op = "else";
                    break;
                }
            }
            val2 = irgen_AddExp(th->son[i+1]);
            condition.push_back(val3);
            if(i == 1){
                if(val1[0]=='*' && val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %%t%d\n",val3.c_str(),op.c_str() ,lvalArray_t1,lvalArray_t2);
                }
                else if (val1[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %s\n",val3.c_str(),op.c_str() ,lvalArray_t1,val2.c_str());
                }
                else if (val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %s, %%t%d\n",val3.c_str(),op.c_str() ,val1.c_str(),lvalArray_t2);
                }
                else
                    fprintf(sysyout,"  %s = cmp %s %s, %s\n",val3.c_str(),op.c_str(),val1.c_str(),val2.c_str());
            } else{
                fprintf(sysyout,"  %s = cmp %s %s %s\n",val3.c_str(), op.c_str(),val3.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

static std::string irgen_EqExp(AST *th){
    std::string val1, val2, val3, op;
    val1 = irgen_RelExp(th->son[0]);
    if(th->son.size() == 1){
        return val1;
    } else{
        val3 = "%t"+std::to_string(t_i);
        t_i++;
        for(int i=1; i < th->son.size(); i+=2){
            if(th->son[i]->type == _EQ){
                op = "eq";
            } else{
                op = "ne";
            }
            val2 = irgen_RelExp(th->son[i+1]);
            condition.push_back(val3);
            if(i == 1){
                if(val1[0]=='*' && val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %%t%d\n",val3.c_str(),op.c_str() ,lvalArray_t1,lvalArray_t2);
                }
                else if (val1[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %s\n",val3.c_str(),op.c_str() ,lvalArray_t1,val2.c_str());
                }
                else if (val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %s, %%t%d\n",val3.c_str(),op.c_str() ,val1.c_str(),lvalArray_t2);
                }
                else
                    fprintf(sysyout,"  %s = cmp %s %s, %s\n",val3.c_str(),op.c_str() ,val1.c_str(),val2.c_str());
            } else{
                fprintf(sysyout,"  %s = cmp %s %s, %s\n",val3.c_str(), op.c_str(),val3.c_str(),val2.c_str());
            }
        }
        return val3;
    }
}

static void irgen_LAndExp(AST *th, int label_false){
    std::string val1;
    for(int i=0;i< th->son.size();i+=2){
        val1 = irgen_EqExp(th->son[i]);
        fprintf(sysyout,"  bf %s,label .L%d\n",val1.c_str(),label_false);
    }
}

static void irgen_LOrExp(AST *th, int label_true, int label_false){
    int size_temp = th->son.size();
    for(int i=0;i< size_temp;i+=2){
        if(i+2 < size_temp){
            irgen_LAndExp(th->son[i], label);
            fprintf(sysyout,"  br label .L%d\n",label_true);
            fprintf(sysyout,".L%d:\n",label);
            label++;
        } else{
            irgen_LAndExp(th->son[i], label_false);
        }
    }
}

static void irgen_Stmt(AST *th){
    if(th->son.size() == 0){
        //';'
        return;
    }
    if(th->son[0]->type == _RETURN){
        if(th->son.size() == 1){
            //RETURN ';'
            fprintf(sysyout,"  exit\n");
        } else{
            //RETURN Exp ';'
            std::string return_temp = irgen_AddExp(th->son[1]->son[0]);
            fprintf(sysyout,"  %%l%d = %s\n",return_l,return_temp.c_str());
            fprintf(sysyout,"  %%t%d = %%l%d\n",return_t,return_l);
            fprintf(sysyout,"  exit %%t%d\n",return_t);
        }
    } else if(th->son[0]->type == _LVal){
        //LVal '=' Exp ';'
        std::string left_temp = irgen_LVal(th->son[0],true);
        std::string right_temp = irgen_AddExp(th->son[1]->son[0]);
        fprintf(sysyout,"  %s = %s\n",left_temp.c_str(),right_temp.c_str());
    } else if(th->son[0]->type == _Exp){
        //Exp ';'
        irgen_AddExp(th->son[0]->son[0]);
    } else if(th->son[0]->type == _Block){
        //Block
        irgen_Block(th->son[0]);
    } else if(th->son[0]->type == _WHILE){
        //WHILE '(' Cond ')' Stmt
        int label_in_temp = label_in_global;
        int label_out_temp = label_out_global;
        th->label_in = label;
        th->label_in2 = label+1;
        th->label_out = label+2;
        label += 3;
        label_in_global = th->label_in;
        label_out_global = th->label_out;
        fprintf(sysyout,".L%d:\n",th->label_in);
        irgen_LOrExp(th->son[1]->son[0], th->label_in2, th->label_out);
        fprintf(sysyout,".L%d:\n",th->label_in2);
        irgen_Stmt(th->son[2]);
        fprintf(sysyout,"  br label .L%d\n",th->label_in);
        fprintf(sysyout,".L%d:\n",th->label_out);
        label_in_global = label_in_temp;
        label_out_global = label_out_temp;
    } else if(th->son[0]->type == _IF && th->son.size() == 5){
        //IF '(' Cond ')' Stmt ELSE Stmt
        th->label_in = label;
        th->label_in2 = label+1;
        th->label_out = label+2;
        label += 3;
        irgen_LOrExp(th->son[1]->son[0],th->label_in,th->label_in2);
        fprintf(sysyout,".L%d:\n",th->label_in);
        irgen_Stmt(th->son[2]);
        fprintf(sysyout,"  br label .L%d\n",th->label_out);
        fprintf(sysyout,".L%d:\n",th->label_in2);
        irgen_Stmt(th->son[4]);
        fprintf(sysyout,".L%d:\n",th->label_out);
    } else if(th->son[0]->type == _IF && th->son.size() == 3){
        //IF '(' Cond ')' Stmt
        th->label_in = label;
        th->label_out = label+1;
        label += 2;
        irgen_LOrExp(th->son[1]->son[0], th->label_in,th->label_out);
        fprintf(sysyout,".L%d:\n",th->label_in);
        irgen_Stmt(th->son[2]);
        fprintf(sysyout,".L%d:\n",th->label_out);
    } else if(th->son[0]->type == _BREAK){
        //BREAK ';'
        fprintf(sysyout,"  br label .L%d\n",label_out_global);
    } else if(th->son[0]->type == _CONTINUE){
        //CONTINUE ';'
        fprintf(sysyout,"  br label .L%d\n",label_in_global);
    }
}

static void irgen_Block(AST *th){
    symtable_ptr = symtable_vector[symtable_i];
    symtable_i++;
    for(int i=0;i<th->son.size();i++){
        if(th->son[i]->son[0]->type == _Decl){
            irgen_Decl(th->son[i]->son[0]);
        } else{
            irgen_Stmt(th->son[i]->son[0]);
        }
    }
    symtable_ptr = symtable_ptr->father;
}
//处理函数定义
static void irgen_FuncDef(AST *th){
    ENTRY_FUNC *func_ptr = (ENTRY_FUNC *)th->son[1]->entry;
    if(!func_ptr->NumberOfParam) {//无参数
        if(!func_ptr->isreturn)
            fprintf(sysyout,"define void @%s(){\n",func_ptr->id.c_str());
        else
            fprintf(sysyout,"define i32 @%s(){\n",func_ptr->id.c_str());
    }
    else {
        AST *next = th->son[2];
        std::string voidTemp = "define void ";
        std::string intTemp = "define i32 ";
        std::string TypeTemp = func_ptr->isreturn?intTemp:voidTemp;
        fprintf(sysyout,"%s@%s(",TypeTemp.c_str(),func_ptr->id.c_str());
        for(int i = 0; i < next->son.size();i++)
        {
            if(next->son[i]->son.size() == 2) {//单个变量
                fprintf(sysyout,"i32 %%t%d",t_i);
                t_i++;
            }
            else {
                fprintf(sysyout,"i32 %%t%d",t_i);
                t_i++;
                auto entry = (ENTRY_VAL *)next->son[i]->son[1]->entry;
                for(int j = 0;j < entry->shape.size();j++)
                {
                    fprintf(sysyout,"[%d]",entry->shape[j]);
                }
            }
            if(i != next->son.size()-1)
                fprintf(sysyout,", ");
        }
        fprintf(sysyout,"){\n");
    }
    indent++;
    print_decl(func_ptr->symtable,func_ptr->NumberOfTemp);
    if(func_ptr->isreturn) {
        t_i += func_ptr->NumberOfTemp;
        print_indent();
        fprintf(sysyout,"declare i32 %%l%d\n",t_i);
        return_l = t_i;
        t_i++;
        print_indent();
        fprintf(sysyout,"declare i32 %%t%d\n",t_i);
        return_t = t_i;
        t_i++;
        print_indent();
        fprintf(sysyout,"declare i32 %%l%d\n",t_i);
        op_t = t_i;
        t_i++;
        print_indent();
        fprintf(sysyout,"declare i32 %%t%d\n",t_i);
        array_t = t_i;
        t_i++;
        print_indent();
        fprintf(sysyout,"declare i32 %%t%d\n",t_i);
        lvalArray_t1 = t_i;
        t_i++;
        print_indent();
        fprintf(sysyout,"declare i32 %%t%d\n",t_i);
        lvalArray_t2 = t_i;
        t_i -= (func_ptr->NumberOfTemp+5);
    }
    print_indent();
    fprintf(sysyout,"entry\n");
    for(int j=0;j<func_ptr->NumberOfParam;j++)
    {
        int i = j + func_begin_t;
        print_indent();
        fprintf(sysyout,"%%l%d = %%t%d\n",i + func_ptr->NumberOfParam,i);
    }
    irgen_Block(th->son[th->son.size()-1]);
    //TODO这里函数的返回问题
    /*
    if(func_ptr->isreturn){
        fprintf(sysyout,"  exit 0\n");
    } else{
        fprintf(sysyout,"  exit\n");
    }
    */
    indent--;
    fprintf(sysyout,"}\n");
}

static void irgen_Decl(AST *th){
    AST *ptr = th->son[0];
    //判断是否是常量
    if(ptr->type == _VarDecl){
        ptr = ptr->son[1];  //VarDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //VarDef
            //变量的符号表项
            ENTRY_VAL *entry_temp = (ENTRY_VAL *)ptr_temp->son[0]->entry;
            if(ptr_temp->son[1]->son.size() == 0){//如果不是数组
                if(ptr_temp->son.size() > 2){//赋初始值
                    if(symtable_ptr == root_symtable){
                        entry_temp->val = ptr_temp->son[2]->son[0]->val;
                        print_indent();
                        fprintf(sysyout,"%s = %d\n", entry_temp->eeyore_id.c_str(), entry_temp->val);
                    } else{
                        //获取值
                        std::string val_temp = irgen_AddExp(ptr_temp->son[2]->son[0]->son[0]);
                        print_indent();
                        fprintf(sysyout,"%s = %s\n", entry_temp->eeyore_id.c_str(), val_temp.c_str());
                    }
                } else{
                    if(symtable_ptr == root_symtable){
                        entry_temp->val = 0;
                    }
                }
            } else {
                if(ptr_temp->son.size() > 2){
                    //entry_temp->arr = new int [entry_temp->size/4];
                    //数组赋初始值
                    irgen_InitVal(ptr_temp->son[2], 0, 0, entry_temp);
                }
            }
        }
    } else if(ptr->type == _ConstDecl){
        ptr = ptr->son[2];  //ConstDef_temp
        for(int i=0;i<ptr->son.size();i++){
            AST *ptr_temp = ptr->son[i];    //ConstDef
            ENTRY_VAL *entry_temp = (ENTRY_VAL *)ptr_temp->son[0]->entry;
            if(ptr_temp->son[1]->son.size() == 0){
                entry_temp->val = ptr_temp->son[2]->son[0]->val;
                print_indent();
                fprintf(sysyout,"%s = %d\n", entry_temp->eeyore_id.c_str(), entry_temp->val);
            } else {
                if(ptr_temp->son.size() > 2){
                    //entry_temp->arr = new int [entry_temp->size/4];
                    irgen_ConstInitVal(ptr_temp->son[2], 0, 0, entry_temp);
                }
            }
        }
    }
}

static void irgen(AST *th){
    //先把全局变量打印出来
    print_decl(root_symtable, 0);

    for(int i=0;i<th->son.size();i++){
        //处理变量定义
        if(th->son[i]->type==_Decl){
            irgen_Decl(th->son[i]);
        } else if(th->son[i]->type==_FuncDef){
            func_begin_t = t_i;
            irgen_FuncDef(th->son[i]);
        }
    }
}

void codegen_eeyore(char *input_file_path, char *output_file_path){
    FILE *input_file = fopen(input_file_path,"r");
    FILE *output_file = fopen(output_file_path,"w");
    sysyin = input_file;
    sysyout = output_file;

    root_symtable = new TABLE("root");
    symtable_vector.push_back(root_symtable);
    symtable_ptr = root_symtable;
    new ENTRY_FUNC("getint",root_symtable,true,nullptr,0,0);
    new ENTRY_FUNC("getch",root_symtable,true,nullptr,0,0);
    new ENTRY_FUNC("getarray",root_symtable,true,nullptr,0,1);
    new ENTRY_FUNC("putint",root_symtable,false,nullptr,0,1);
    new ENTRY_FUNC("putch",root_symtable,false,nullptr,0,1);
    new ENTRY_FUNC("putarray",root_symtable,false,nullptr,0,2);
    new ENTRY_FUNC("starttime",root_symtable,false,nullptr,0,0);
    new ENTRY_FUNC("stoptime",root_symtable,false,nullptr,0,0);
    sysyparse();
    irgen(root_sysy);

    fclose(input_file);
    fclose(output_file);
    for(auto i : vectorArray)
    {
        char s[100];
        sprintf(s,"sed -i 's/declare i32 %s/declare i32* %s/g' %s",i.c_str(),i.c_str(),output_file_path);
        system(s);
    }
    for(auto i : condition)
    {
        char s[100];
        sprintf(s,"sed -i 's/declare i32 %s/declare i1 %s/g' %s",i.c_str(),i.c_str(),output_file_path);
        system(s);
    }
    sysyin = stdin;
    sysyout = stdout;
}
