#include"ast_sysy.h"
#include<stdio.h>
#include<string>
#include<fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include<string.h>
#include"../build/parser.tab.hpp"
using namespace std;
extern FILE *sysyin;
extern FILE *sysyout;

AST *root_sysy;
TABLE *root_symtable;
std::vector<TABLE *> symtable_vector;
TABLE * symtable_ptr;
int func_begin_t;
int Max_t_i = 0;
int return_l;
int return_t;
int op_t;
int array_t;
int lvalArray_t1;
int lvalArray_t2;
bool is_neg = false;
std::vector <std::string> vectorArray;
std::vector <std::string> condition;
std::vector <std::string> dymaticArray;
std::vector <int> dymaticArrayval;
int dymaticArraySize = 0;
int G_i = 0;
int t_i = 0;    //temp var
int indent = 0; //global indent
int label = 0;  //global label
int symtable_i = 1; //下一个要打开的符号表编号
int label_in_global;   //最内层代码块的进入标号
int label_out_global;
int global_shape_num = 0;  
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
static std::string irgen_EqExp(AST *th,bool &isVar);
static std::string irgen_RelExp(AST *th,bool &isVar);

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
        if(table->val[i]->shape.size() == 1 && table->val[i]->shape[0]==1) {
            fprintf(sysyout,"declare i32* %s", table->val[i]->eeyore_id.c_str());
        }
        else {
            fprintf(sysyout,"declare i32 %s", table->val[i]->eeyore_id.c_str());
            for(auto shape : table->val[i]->shape)
            {
                fprintf(sysyout,"[%d]", shape);
            }
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
    /*
    int t_i_temp = t_i;
    for(int i=0;i<numberoftemp;i++){
        print_indent();
        fprintf(sysyout,"declare i32 %%t");
        fprintf(sysyout,"%d\n",t_i);
        t_i++;
    }
    t_i = t_i_temp;
    */
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
                if(val2[0]!='%') {//应该不会使用数组值作为数组索引
                    print_indent();
                    fprintf(sysyout,"%%l%d = %s\n",op_t, val2.c_str());
                    print_indent();
                    fprintf(sysyout,"%s = mul %%l%d,%d\n",val1.c_str(),op_t,size_temp);
                }
                else 
                {
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
                fprintf(sysyout,"%%t%d = add %s,%s\n",t_i,val1.c_str(),val3.c_str());
                val1 = "%t" + std::to_string(t_i);
                t_i++;
                val3 = "%t" + std::to_string(t_i);
                t_i++;
                /*
                array_t = t_i;
                t_i++;
                */
            }
        }
        print_indent();
        fprintf(sysyout,"%%t%d = add %s,%s\n",t_i,entry_temp->eeyore_id.c_str(),val1.c_str());
        val1 = "%t" + std::to_string(t_i);
        t_i++;
        if(entry_temp->shape.size() > th->son.size()-1) {
            dymaticArraySize = entry_temp->shape[entry_temp->shape.size()-1];
        }
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
        if(th->son[0]->son[0]->op == '-'){
            val1 = "%t"+std::to_string(t_i);
            t_i++;
            val2 = irgen_UnaryExp(th->son[1]);
            print_indent();
            fprintf(sysyout,"%s = neg %s\n",val1.c_str(),val2.c_str());
        }
        else if(th->son[0]->son[0]->op == '!') {
            if(val2[0]=='%') {
                val1 = "%t"+std::to_string(t_i);
                t_i++;
                val2 = irgen_UnaryExp(th->son[1]);
                print_indent();
                fprintf(sysyout,"%s = cmp le %s, 0\n",val1.c_str(),val2.c_str());
            }
            else {
                val1 = "%t"+std::to_string(t_i);
                t_i++;
                val2 = irgen_UnaryExp(th->son[1]);
                print_indent();
                fprintf(sysyout,"%%t%d = %s\n",t_i,val2.c_str());
                //val2 = "%t" + std::to_string(t_i);
                print_indent();
                is_neg = true;
                fprintf(sysyout,"%s = cmp le %%t%d, 0\n",val1.c_str(),t_i);
                t_i++;
            }
            condition.push_back(val1);
        } 
        else{
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
        //printf("function: %s\n",func_temp->id.c_str());
        for(int i=0; i < param_num;i++) {
            if(vector_param[i][0]=='*' && func_temp->id != "putarray")
            {
                print_indent();
                fprintf(sysyout,"%%t%d = %s\n",t_i,vector_param[i].c_str());
                vector_param[i] = "%t" + std::to_string(t_i);
                t_i++;
            }
        }
        if(func_temp->isreturn){
            val1 = "%t"+std::to_string(t_i);
            t_i++;
            fprintf(sysyout,"  %s = call i32 @%s(",val1.c_str(),func_temp->id.c_str());
        } else{
            t_i++;
            /*
            if(func_temp->id == "starttime"){
                fprintf(sysyout,"  param %d\n", th->lineno);
                fprintf(sysyout,"  call @sysy_starttime\n");
            } else if(func_temp->id == "stoptime"){
                fprintf(sysyout,"  param %d\n", th->lineno);
                fprintf(sysyout,"  call @sysy_stoptime\n");
            } else{
                fprintf(sysyout,"  call void @%s(",func_temp->id.c_str());
            }
            */
           fprintf(sysyout,"  call void @%s(",func_temp->id.c_str());
        }
        for(int i=0; i < param_num;i++) {
            if(func_temp->id == "getarray") {
                fprintf(sysyout,"i32 %s[%d]",vector_param[i].c_str(),dymaticArraySize);
                dymaticArrayval.push_back(dymaticArraySize);
                dymaticArray.push_back(vector_param[i].c_str());
                break;
            }
            else if(func_temp->id == "putarray") {
                fprintf(sysyout,"i32 %s,",vector_param[i].c_str());
                fprintf(sysyout,"i32 %s[%d]",vector_param[i+1].substr(1,vector_param[i+1].size()-1).c_str(),dymaticArraySize);
                dymaticArrayval.push_back(dymaticArraySize);
                dymaticArray.push_back(vector_param[i+1].substr(1,vector_param[i+1].size()-1));
                break;
            }
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
                        lvalArray_t1 = t_i;
                        t_i++;
                        lvalArray_t2 = t_i;
                        t_i++;

                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mul %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mul %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                        lvalArray_t2 = t_i;
                        t_i++;
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
                        lvalArray_t1 = t_i;
                        t_i++;
                        lvalArray_t2 = t_i;
                        t_i++;
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = div %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = div %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                        lvalArray_t2 = t_i;
                        t_i++;
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
                        lvalArray_t1 = t_i;
                        t_i++;
                        lvalArray_t2 = t_i;
                        t_i++;
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mod %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = mod %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                        lvalArray_t2 = t_i;
                        t_i++;
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
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = mul %s,%%t%d\n",t_i, val3.c_str(),lvalArray_t1);
                        val3 = "%t" + std::to_string(t_i);
                        t_i++; 
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else {
                        fprintf(sysyout,"%%t%d = mul %s,%s\n",t_i, val3.c_str(),val2.c_str());
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                    }
                    break;
                case '/':
                    if(val2[0] == '*') {
                        fprintf(sysyout,"%%t%d = div %s,%s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = div %s,%%t%d\n",t_i, val3.c_str(),lvalArray_t1);
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else {
                        fprintf(sysyout,"%%t%d = div %s,%s\n",t_i, val3.c_str(),val2.c_str());
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                    }
                    break;
                case '%':
                    if(val2[0] == '*') {
                        fprintf(sysyout,"%%t%d = mod %s,%s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = mod %s,%%t%d\n",t_i, val3.c_str(),lvalArray_t1);
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else {
                        fprintf(sysyout,"%%t%d = mod %s,%s\n",t_i, val3.c_str(),val2.c_str());
                        val3 = "%t" + std::to_string(t_i);
                        t_i++; 
                    }
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
                        lvalArray_t1 = t_i;
                        t_i++;
                        lvalArray_t2 = t_i;
                        t_i++;
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = add %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = add %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                        lvalArray_t2 = t_i;
                        t_i++;
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
                        lvalArray_t1 = t_i;
                        t_i++;
                        lvalArray_t2 = t_i;
                        t_i++;
                    }
                    else if(val1[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1, val1.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = sub %%t%d,%s\n",val3.c_str(),lvalArray_t1 ,val2.c_str());
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t2, val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%s = sub %s,%%t%d\n",val3.c_str(),val1.c_str(),lvalArray_t2);
                        lvalArray_t2 = t_i;
                        t_i++;
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
                        fprintf(sysyout,"%%t%d = add %s,%%t%d\n",t_i, val3.c_str(),lvalArray_t1);
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else {
                        fprintf(sysyout,"%%t%d = add %s,%s\n",t_i, val3.c_str(),val2.c_str());
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                    }
                    break;
                case '-':
                    if(val2[0]=='*') {
                        fprintf(sysyout,"%%t%d = %s\n",lvalArray_t1,val2.c_str());
                        print_indent();
                        fprintf(sysyout,"%%t%d = sub %s,%%t%d\n",t_i, val3.c_str(),lvalArray_t1);
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                        lvalArray_t1 = t_i;
                        t_i++;
                    }
                    else {
                        fprintf(sysyout,"%%t%d = sub %s,%s\n",t_i, val3.c_str(),val2.c_str());
                        val3 = "%t" + std::to_string(t_i);
                        t_i++;
                    }
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

static std::string irgen_RelExp(AST *th,bool &isVar){
    std::string val1, val2, val3, op;
    val1 = irgen_AddExp(th->son[0]);
    isVar = false;
    if(th->son.size() == 1){
        isVar = true;
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
                    lvalArray_t1 = t_i;
                    t_i++;
                    lvalArray_t2 = t_i;
                    t_i++;
                }
                else if (val1[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %s\n",val3.c_str(),op.c_str() ,lvalArray_t1,val2.c_str());
                    lvalArray_t1 = t_i;
                    t_i++;
                }
                else if (val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %s, %%t%d\n",val3.c_str(),op.c_str() ,val1.c_str(),lvalArray_t2);
                    lvalArray_t2 = t_i;
                    t_i++;
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

static std::string irgen_EqExp(AST *th,bool &isVar){
    std::string val1, val2, val3, op;
    isVar = false;
    bool flag = false;
    val1 = irgen_RelExp(th->son[0],flag);
    if(th->son.size() == 1){
        if(flag && !is_neg) {
            isVar = true;
        }
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
            val2 = irgen_RelExp(th->son[i+1],flag);
            condition.push_back(val3);
            if(i == 1){
                if(val1[0]=='*' && val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %%t%d\n",val3.c_str(),op.c_str() ,lvalArray_t1,lvalArray_t2);
                    lvalArray_t1 = t_i;
                    t_i++;
                    lvalArray_t2 = t_i;
                    t_i++;
                }
                else if (val1[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t1,val1.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %%t%d, %s\n",val3.c_str(),op.c_str() ,lvalArray_t1,val2.c_str());
                    lvalArray_t1 = t_i;
                    t_i++;
                }
                else if (val2[0]=='*') {
                    fprintf(sysyout,"  %%t%d = %s\n",lvalArray_t2,val2.c_str());
                    print_indent();
                    fprintf(sysyout,"  %s = cmp %s %s, %%t%d\n",val3.c_str(),op.c_str() ,val1.c_str(),lvalArray_t2);
                    lvalArray_t2 = t_i;
                    t_i++;
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
        bool isVar;
        val1 = irgen_EqExp(th->son[i],isVar);
        if(!isVar)
            fprintf(sysyout,"  bf %s,label .L%d\n",val1.c_str(),label_false);
        else {
            if(val1[0] == '*') {
                fprintf(sysyout,"  %%t%d = %s\n", t_i, val1.c_str());
                t_i++;
                fprintf(sysyout,"  %%t%d = cmp gt %%t%d, 0\n",t_i,t_i-1,val1.c_str());
                std::string s = "%t" + std::to_string(t_i);
                condition.push_back(s);
                fprintf(sysyout,"  bf %%t%d,label .L%d\n",t_i,label_false);
                t_i++;
            }
            else {
                fprintf(sysyout,"  %%t%d = cmp gt %s, 0\n",t_i,val1.c_str());
                std::string s = "%t" + std::to_string(t_i);
                condition.push_back(s);
                fprintf(sysyout,"  bf %%t%d,label .L%d\n",t_i,label_false);
                t_i++;
            }
        }
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
            return_t = t_i;
            t_i++;
        }
    } else if(th->son[0]->type == _LVal){
        //LVal '=' Exp ';'
        std::string left_temp = irgen_LVal(th->son[0],true);
        std::string right_temp = irgen_AddExp(th->son[1]->son[0]);
        if(right_temp[0]=='*') {
            fprintf(sysyout,"  %%t%d = %s\n",t_i,right_temp.c_str());
            fprintf(sysyout,"  %s = %%t%d\n",left_temp.c_str(),t_i);
            t_i++;
        }
        else
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
                auto entry = (ENTRY_VAL *)next->son[i]->son[1]->entry;
                if(entry->shape.size() == 1 && entry->shape[0]==1) {
                    fprintf(sysyout,"i32* %%t%d",t_i);
                }
                else {
                    fprintf(sysyout,"i32 %%t%d",t_i);
                    for(int j = 0;j < entry->shape.size();j++)
                    {
                        fprintf(sysyout,"[%d]",entry->shape[j]);
                    }
                }
                t_i++;
            }
            if(i != next->son.size()-1)
                fprintf(sysyout,", ");
        }
        fprintf(sysyout,"){\n");
    }
    indent++;
    print_decl(func_ptr->symtable,func_ptr->NumberOfTemp);
    for(int i=0;i< 300;i++){
        print_indent();
        fprintf(sysyout,"declare i32 %%t");
        fprintf(sysyout,"%d\n",t_i);
        t_i++;
    }
    print_indent();
    fprintf(sysyout,"declare i32 %%l%d\n",t_i);//返回值栈中分配空间
    return_l = t_i;
    t_i++;
    print_indent();
    fprintf(sysyout,"declare i32 %%t%d\n",t_i);//返回值临时变量
    return_t = t_i;
    t_i++;
    print_indent();
    fprintf(sysyout,"declare i32 %%l%d\n",t_i);//操作符不能对两个栈变量使用引一个中间变量
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
    Max_t_i = t_i + 1;
    t_i -= (305);

    print_indent();
    fprintf(sysyout,"entry\n");
    for(int j=0;j<func_ptr->NumberOfParam;j++)
    {
        int i = j + func_begin_t;
        print_indent();
        fprintf(sysyout,"%%l%d = %%t%d\n",i + func_ptr->NumberOfParam,i);
    }
    print_indent();
    irgen_Block(th->son[th->son.size()-1]);
    if(func_ptr->isreturn){
        
        print_indent();
        fprintf(sysyout,"%%l%d = 0\n",return_l);
        print_indent();
        fprintf(sysyout,"%%t%d = %%l%d\n",return_t,return_l);
        print_indent();
        fprintf(sysyout,"  exit %%t%d\n",return_t);
    } else{
        fprintf(sysyout,"  exit\n");
    }
    indent--;
    fprintf(sysyout,"}\n");
    t_i = Max_t_i;
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
            #ifdef DEBUG
                printf("%d\n",Max_t_i);
            #endif
            irgen_FuncDef(th->son[i]);
        }
    }
}
/*
//打印抽象语法树，同时返回当前节点的string值
string print_ast(AST *ast,string parent,int index, FILE *output_file) {
    string s;
    switch (ast->type)
    {
        case _CompUnit://只有一个节点
            return "CompUnit";
            break;
        case _Decl:
            s = parent + "_Decl_" + to_string(index);
            break;
        case _FuncDef:
            s = parent + "_FuncDef_" + to_string(index);
            break;
        case _ConstDecl:
            s = parent + "_ConstDecl_" + to_string(index);
            break;
        case _INT:
            s = parent + "_INTTYPE_" + to_string(index);
            break;
        case _VOID:
            s = parent + "_VOIDTYPE_" + to_string(index);
            break;
        case _CONST:
            return s;
            break;
        case _IF:
            s = parent + "_IF_" + to_string(index);
            break;
        case _ELSE:
            s = parent + "_ELSE_" + to_string(index);
            break;
        case _WHILE:
            s = parent + "_WHILE_" + to_string(index);
            break;
        case _BREAK:
            s = parent + "_BREAK_" + to_string(index);
            break;
        case _CONTINUE:
            s = parent + "_CONTINUE_" + to_string(index);
            break;
        case _RETURN:
            s = parent + "_RETURN_" + to_string(index);
            break;
        case _LE:
            s = parent + "_LE_" + to_string(index);
            break; 
        case _EQ:
            s = parent + "_EQ_" + to_string(index);
            break;
        case _NE:
            s = parent + "_NE_" + to_string(index);
            break;  
        case _AND:
            s = parent + "_AND_" + to_string(index);
            break;
        case _OR:
            s = parent + "_OR_" + to_string(index);
            break;
        case _IDENT:
            //这里由于同一个域中不可能出现相同的ident
            s = parent + "_IENT_" + ast->id;
            break;
        case _INT_CONST:
            s = parent + "_INT_CONST_" + to_string(ast->val);
            break;
        case _OP:
            s = parent + "_OP_" + ast->op;
            break;
        case _ConstDef_temp:
            s = parent + "_ConstDef_temp_" + to_string(index);
            break;
        case _BType:
            s = parent + "_BType_" + to_string(index);
            break;
        case _ConstDef:
            s = parent + "_ConstDef_" + to_string(index);
            break;
        case _ConstExp_temp:
            s = parent + "_ConstExp_temp_" + to_string(index);
            break;
        case _ConstInitVal:
            s = parent + "_ConstInitVal_" + to_string(index);
            break;
        case _ConstInitVal_temp:
            s = parent + "_ConstInitVal_temp_" + to_string(index);
            break;
        case _VarDecl:
            s = parent + "_VarDecl_" + to_string(index);
            break;
        case _VarDef_temp:
            s = parent + "_VarDef_temp_" + to_string(index);
            break;
        case _VarDef:
            s = parent + "_VarDef_" + to_string(index);
            break;
        case _InitVal:
            s = parent + "_InitVal_" + to_string(index);
            break;
        case _InitVal_temp:
            s = parent + "_InitVal_temp_" + to_string(index);
            break;
        case _FuncFParams:
            s = parent + "_FuncFParams_" + to_string(index);
            break;
        case _FuncFParam:
            s = parent + "_FuncFParam_" + to_string(index);
            break;
        case _Block:
            s = parent + "_Block_" + to_string(index);
            break;
        case _BlockItem_temp:
            s = parent + "_BlockItem_temp_" + to_string(index);
            break;
        case _BlockItem:
            s = parent + "_BlockItem_" + to_string(index);
            break;
        case _Stmt:
            s = parent + "_Stmt_" + to_string(index);
            break;
        case _Exp:
            s = parent + "_Exp_" + to_string(index);
            break;
        case _Cond:
            s = parent + "_Cond_" + to_string(index);
            break;
        case _LVal:
            s = parent + "_LVal_" + to_string(index);
            break;
        case _PrimaryExp:
            s = parent + "_PrimaryExp_" + to_string(index);
            break;
        case _Number:
            s = parent + "_Number_" + to_string(index);
            break;
        case _UnaryExp:
            s = parent + "_UnaryExp_" + to_string(index);
            break;
        case _UnaryOp:
            s = parent + "_UnaryOp_" + to_string(index);
            break;
        case _FuncRParams:
            s = parent + "_FuncRParams_" + to_string(index);
            break;
        case _MulExp:
            s = parent + "_MulExp_" + to_string(index);
            break;
        case _AddExp:
            s = parent + "_AddExp_" + to_string(index);
            break;
        case _RelExp:
            s = parent + "_RelExp_" + to_string(index);
            break;
        case _EqExp:
            s = parent + "_EqExp_" + to_string(index);
            break;
        case _LAndExp:
            s = parent + "_LAndExp_" + to_string(index);
            break;
        case _LOrExp:
            s = parent + "_LOrExp_" + to_string(index);
            break;
        case _ConstExp:
            s = parent + "_ConstExp_" + to_string(index);
            break;
        default:
            break;
    }
    fprintf(output_file,"   \"%s\" -> \"%s\"\n", parent.c_str(), s.c_str());
    return s;
}
void traverse_ast(AST *ast,string parent,int index,FILE *output_file) {
    if(ast == nullptr)
        return;
    string temp_parent = print_ast(ast,parent,index,output_file);
    for(int i=0;i<ast->son.size();i++)
    {
        traverse_ast(ast->son[i],temp_parent,i,output_file);
    }
}
*/
string print_ast(AST *ast,string &parent,int index, FILE *output_file, AST *parentast, int size) {
    string s;
    switch (ast->type) {
        case _CompUnit://只有一个节点
            fprintf(output_file,"shape%d [ label = \"CompUnit\" ];\n", global_shape_num);
            s = "shape" + to_string(global_shape_num);
            global_shape_num++;
            return s;
            break;
        case _FuncDef:
            fprintf(output_file,"shape%d [ label = \"", global_shape_num);
            if(ast->son.size() == 3) {//无参数函数
                fprintf(output_file, "%s()", ast->son[1]->id.c_str());
            }
            else {
                fprintf(output_file, "%s(", ast->son[1]->id.c_str());
                for(int i = 0; i < ast->son[2]->son.size(); i++) {
                    if(i != ast->son[2]->son.size() - 1) {
                        fprintf(output_file, "%s, ", ast->son[2]->son[i]->id.c_str());
                    }
                    else {
                        fprintf(output_file, "%s)", ast->son[2]->son[i]->id.c_str());
                    }
                }
            }
            s = "shape" + to_string(global_shape_num);
            global_shape_num++;
            fprintf(output_file, "\" ];\n");
            fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
            return s;
            break;
        case _Stmt:
            if(ast->son.size() >= 1) {
                if(ast->son[0]->type == _LVal) {
                    fprintf(output_file,"shape%d [ label = \"=\" ];\n", global_shape_num);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                }
                if(ast->son[0]->type == _IF) {
                    fprintf(output_file,"shape%d [ label = \"if\" ];\n", global_shape_num);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                }
                if(ast->son[0]->type == _WHILE) {
                    fprintf(output_file,"shape%d [ label = \"while\" ];\n", global_shape_num);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                }
                if(ast->son[0]->type == _RETURN) {
                    fprintf(output_file,"shape%d [ label = \"return\" ];\n", global_shape_num);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                    break;
                }
            }
            return parent;
            break;
        case _ELSE:
            fprintf(output_file,"shape%d [ label = \"else\" ];\n", global_shape_num);
            s = "shape" + to_string(global_shape_num);
            fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
            global_shape_num++;
            parent = s;
            return s;
            break;
        case _LOrExp:
            if(ast->son.size() > 1) {
                fprintf(output_file,"shape%d [ label = \"or\" ];\n", global_shape_num);
                s = "shape" + to_string(global_shape_num);
                fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                global_shape_num++;
                return s;
            }
            else {
                return parent;
            }
            break;
        case _LAndExp:
            if(ast->son.size() > 1) {
                fprintf(output_file,"shape%d [ label = \"and\" ];\n", global_shape_num);
                s = "shape" + to_string(global_shape_num);
                fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                global_shape_num++;
                return s;
            }
            else {
                return parent;
            }
            break;
        case _EqExp:
            if(ast->son.size() > 1) {
                if(ast->son[1]->type == _EQ) {
                    fprintf(output_file,"shape%d [ label = \"eq\" ];\n", global_shape_num);
                }
                else {
                    fprintf(output_file,"shape%d [ label = \"nq\" ];\n", global_shape_num);
                }
                s = "shape" + to_string(global_shape_num);
                fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                global_shape_num++;
                return s;
            }
            else {
                return parent;
            }
            break;
        case _RelExp:
            if(ast->son.size() > 1) {
                switch(ast->son[1]->type) {
                    case _LE:
                        fprintf(output_file,"shape%d [ label = \"<=\" ];\n", global_shape_num);
                        break;
                    case _GE:
                        fprintf(output_file,"shape%d [ label = \">=\" ];\n", global_shape_num);
                        break;
                    case _OP:
                        fprintf(output_file,"shape%d [ label = \"%c\" ];\n", global_shape_num, ast->son[1]->op);
                        break;
                    default:
                        fprintf(output_file,"shape%d [ label = \"%c\" ];\n", global_shape_num, ast->son[1]->op);
                        break;
                }
                s = "shape" + to_string(global_shape_num);
                fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                global_shape_num++;
                return s;
            }
            else {
                return parent;
            }
            break;
        case _UnaryExp:
    
            if(parentast->type == _MulExp) {
                if(index < size-1) {
                    fprintf(output_file,"shape%d [ label = \"%c\" ];\n",global_shape_num,parentast->son[index + 1]->op);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    parent = s;
                    global_shape_num++;
                }
            }
            if(ast->son.size() == 1) {
                if(ast->son[0]->type == _PrimaryExp) {
                    return parent;
                }   
                else {
                    fprintf(output_file,"shape%d [ label = \"call %s()\" ];\n",global_shape_num,ast->son[0]->id.c_str());
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                }
            }
            else {
                if(ast->son[0]->type == _UnaryOp) {
                    fprintf(output_file,"shape%d [ label = \"%c\" ];\n",global_shape_num,ast->son[0]->son[0]->op);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                }
                else {
                    fprintf(output_file,"shape%d [ label = \"", global_shape_num);
                    fprintf(output_file, "call %s(", ast->son[0]->id.c_str());
                    for(int i = 0; i < ast->son[1]->son.size(); i++) {
                        if(i != ast->son[1]->son.size() - 1) {
                            fprintf(output_file, "%s, ", ast->son[1]->son[i]->id.c_str());
                        }
                        else {
                            fprintf(output_file, "%s)", ast->son[1]->son[i]->id.c_str());
                        }
                    }
                    fprintf(output_file,"\" ];\n");
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                }
            }
            break;
        case _PrimaryExp:
            switch (ast->son[0]->type)
            {
                case _Exp:
                    return parent;
                    break;
                case _INT_CONST:
                    fprintf(output_file,"shape%d [ label = \"%s\" ];\n",global_shape_num,to_string(ast->son[0]->val).c_str());
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    global_shape_num++;
                    return s;
                    break;
                default:
                    return parent;
                    break;
            }
            break;
        case _MulExp:
            if(parentast->type == _AddExp) {
                if(index < size-1) {
                    fprintf(output_file,"shape%d [ label = \"%c\" ];\n",global_shape_num,parentast->son[index + 1]->op);
                    s = "shape" + to_string(global_shape_num);
                    fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                    parent = s;
                    global_shape_num++;
                }
            }
            return parent;
            break;
        case _LVal:
            if(ast->son[0]->id.size()!=0){
                fprintf(output_file,"shape%d [ label = \"%s\" ];\n",global_shape_num,ast->son[0]->id.c_str());
                s = "shape" + to_string(global_shape_num);
                fprintf(output_file, "%s -> %s;\n", parent.c_str(), s.c_str());
                global_shape_num++;
                return s;
            }
            else
                return parent;
            break;
        default:
            return parent;
    }
}
void traverse_ast(AST *ast,string &parent,int index,FILE *output_file,AST *parentast,int size) {
    if(ast == nullptr)
        return;
    string temp_parent = print_ast(ast,parent,index,output_file,parentast,size);
    for(int i=0;i<ast->son.size();i++)
    {
        traverse_ast(ast->son[i],temp_parent,i,output_file, ast, ast->son.size());
    }
}
//打印符号表
void print_table(TABLE *table,string s,FILE* file)
{
    string space = table->space;
    int ValSize = table->val.size();
    int FuncSize = table->func.size();
    if(ValSize > 0 || FuncSize > 0) {
        fprintf(file,"%sspace: %s\n",s.c_str(),space.c_str());
    }
    for(int i=0;i<ValSize;i++) {
        if(i==0)
            fprintf(file,"%sval:\n",s.c_str());
        
        fprintf(file,"%s%s  ",s.c_str(),table->val[i]->id.c_str());
        if(table->val[i]->isConst) {
            fprintf(file,"val:%d    ",table->val[i]->val);
        }
        if(table->val[i]->isArray) {
            fprintf(file,"shape: [");
            for(int j = 0; j < table->val[i]->shape.size(); j++) {
                if(j == 0) {
                    fprintf(file, "%d",table->val[i]->shape[j]);
                }
                else {
                    fprintf(file,",%d",table->val[i]->shape[j]);
                }
            }
            fprintf(file,"]");
        }
        fprintf(file,"\n");
    }
    fprintf(file,"\n");
    for(int j=0;j<FuncSize;j++) {
        if(j==0)
            fprintf(file,"func: \n");
        fprintf(file,"%s%s  ",s.c_str(),table->func[j]->id.c_str());
        if(table->func[j]->isreturn) {
            fprintf(file,"type: int\n");
        }
        else {
            fprintf(file,"type: void\n");
        }
    }
    fprintf(file,"\n");
}
//这里需要使用深度优先来得到符号表
void traverse_table(TABLE *tableItem,int depth,FILE* file)
{
    if(tableItem == nullptr)
        return;
    string s;
    for(int i=0;i<depth;i++) {
        s += "  ";
    }
    print_table(tableItem,s,file);
    for(auto index : tableItem->son) {
        traverse_table(index,depth+1,file);
    }
}

int findIndex(int lineNum, vector<int> startLine) {
    for(int i = 0; i < startLine.size(); i++) {
        if(lineNum > startLine[i]) {
            continue;
        }
        else if(lineNum == startLine[i]) {
            return i;
        }
        else {
            return i-1;
        }
    }
}
void getLinearIR(char *file, string functionName) {
    ifstream inFile;
    inFile.open(file,ios::in);
    string textLine;
    int lineNum = 1;
    int endLineNum = 0;
    bool flag = true;
    bool isEnd = false;
    bool firstIn = true;
    vector<int> startLine;//获取第一行和跳转后面的块
    unordered_set<int> labelSet;//获取可跳转的label集合
    vector<int> labelVec;//记录所有label的标签
    unordered_map<int,int> labelToLine;//获取所有有标号的块
    unordered_set<int> labelLineSet;
    vector<pair<int, int> > jrLine;//获取jr跳转的块对
    vector<pair<int, int> > jrIndex;
    vector<pair<int, int> > jumpLine;//其它跳转
    vector<pair<int, int> > jumpIndex;
    //找到函数定义
    while(getline(inFile,textLine,'\n')) {
        auto idx = textLine.find(functionName);
        if(idx == string::npos) {
            lineNum++;
            continue;
        }
        lineNum++;
        break;
    }
    //判断跳转和标号
    while(getline(inFile,textLine,'\n')) {
        if(flag) {//跳过declare
            auto idx = textLine.find("declare");
            if(idx != string::npos) {
                lineNum++;
                continue;
            }
            startLine.push_back(lineNum);
            flag = false;
        }
    
        if(textLine=="}") {//函数结束符结束
            endLineNum = lineNum;
            break;
        }
    
        if(textLine[0] == '.') {
            int label = atoi(textLine.substr(2, textLine.length()-2).c_str());
            labelVec.push_back(label);
            labelToLine[label] = lineNum;
        }

        auto idx = textLine.find("label .L");
        if(idx != string::npos) {
            int label = atoi(textLine.substr(idx + 8, textLine.length()- idx - 8).c_str());
            auto idx = textLine.find("br");
            if(idx != string::npos) {
                jrLine.push_back(make_pair(lineNum,label));
                startLine.push_back(lineNum+1);
            }
            else {
                startLine.push_back(lineNum+1);
                jumpLine.push_back(make_pair(lineNum,label));
            }
        }
        lineNum++;
    }
    //得到基本块的开始行
    for(auto label : labelVec) {
        if(labelSet.count(label) != 0) {
            if(find(startLine.begin(), startLine.end(),labelToLine[label])==startLine.end()) {
                startLine.push_back(labelToLine[label]);
                labelLineSet.insert(labelToLine[label]);
            }
        }
    }
    //得到跳转关系
    for(auto label : jrLine) {
        jrIndex.push_back(make_pair(findIndex(label.first,startLine), findIndex(labelToLine[label.second],startLine)));
    }
    for(auto label : jumpLine) {
        jumpIndex.push_back(make_pair(findIndex(label.first,startLine), findIndex(labelToLine[label.second],startLine)));
    }
    //基本块的内容
    vector<vector<string> > baseBlock;
    vector<string> strVector;
    inFile.seekg(0,std::ios::beg);
    sort(startLine.begin(),startLine.end());
    lineNum = 1;
    int index = 0;//基本块的索引
    int end = startLine.size() > 1?startLine[1]:0;
    while(getline(inFile,textLine,'\n')) {
        if(lineNum < startLine[0]) {
            lineNum++;
        }
        else {
            lineNum++;
            break;
        }
    }
    while(getline(inFile,textLine,'\n')) { 
        if(end <= lineNum) {
            if(!firstIn) {
                index++;
                baseBlock.push_back(strVector);
            }
            firstIn = false;
            strVector.clear();
            //判断是否是最后一个块
            if(index+1 == startLine.size()) {
                end = endLineNum;
            }
            else if(index == startLine.size()) {
                break;
            }
            else {
                end = startLine[index+1];
            }
        }
        firstIn = false;
        strVector.push_back(textLine);
        lineNum++;
    }
    inFile.close();
    inFile.clear();
    ofstream outFile;
    outFile.open(file,ios::out);
    outFile<<"digraph streamgraph\n";
    outFile<<"{\n";
    for(int i = 0; i < baseBlock.size(); i++) {
        outFile<<"  shape"<<i<<" [ shape=box, label=\"";
        for(int j = 0; j < baseBlock[i].size(); j++) {
            if(j != baseBlock[i].size() - 1)
                outFile<<baseBlock[i][j]<<"\\n";
            else {
                outFile<<baseBlock[i][j]<<"\""<<"]\n";
            }
        }
    }
    for(auto line : jrIndex) {
        outFile<<"  shape"<<line.first<<" -> " <<"shape"<<line.second<<"\n";
    }
    for(auto line : jumpIndex) {
        if(line.first < startLine.size() - 1) {
            outFile<<"  shape"<<line.first<<" -> " <<"shape"<< line.first+1<<"\n";
        }
        outFile<<"  shape"<<line.first<<" -> " <<"shape" << line.second<<"\n";
    }
    outFile<<"}";
    outFile.close();
}

void codeToIR(char *input_file_path, char *output_file_path,int type,std::string function)
{
    bool isPrintAst = false;
    bool isToLinearIR = false;
    bool isToFunction = false;
    string temp_string;
    FILE *input_file = fopen(input_file_path,"r");
    FILE *output_file;
    if(type == 4) 
    {
        output_file = fopen("./temp.dot","w");
    }
    else
        output_file = fopen(output_file_path,"w");
    FILE *temp_dot;

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
    switch (type)
    {
    case 1:
        isPrintAst = true;
        temp_dot = fopen("temp.dot","w");
        fprintf(temp_dot,"   digraph G {\n");
        traverse_ast(root_sysy,temp_string,0,temp_dot,nullptr,0);
        fprintf(temp_dot,"}");
        fclose(temp_dot);
        break;
    case 2:
        traverse_table(root_symtable,0,sysyout);
        break;
    case 3:
        isToLinearIR = true;
        irgen(root_sysy);
        break;
    case 4:
        isToFunction = true;
        irgen(root_sysy);
        break;
    }
    fclose(input_file);
    fclose(output_file);
    sysyin = stdin;
    sysyout = stdout;
    if(isPrintAst)
    {
        char command[300];
        sprintf(command,"dot -Tpng temp.dot -o %s", output_file_path);
        system(command);
        system("rm -rf temp.dot");
    }
    if(isToLinearIR) {
        for(auto i : vectorArray)
        {
            char s[100];
            sprintf(s,"sed -i '0,/declare i32 %s/s/declare i32 %s/declare i32* %s/' %s",i.c_str(),i.c_str(),i.c_str(),output_file_path);
            system(s);
        }
        for(auto i : condition)
        {
            char s[100];
            sprintf(s,"sed -i '0,/declare i32 %s/s/declare i32 %s/declare i1 %s/' %s",i.c_str(),i.c_str(),i.c_str(),output_file_path);
            system(s);
        }
        for(int i = 0; i < dymaticArray.size(); i++) {
            char s[120];
            sprintf(s,"sed -i '0,/declare i32 %s/s/declare i32 %s/declare i32 %s[%d]/' %s",dymaticArray[i].c_str(),dymaticArray[i].c_str(),dymaticArray[i].c_str(),dymaticArrayval[i],output_file_path);
            system(s);
        }
    }
    if(isToFunction) {
        for(auto i : vectorArray)
        {
            char s[100];
            sprintf(s,"sed -i '0,/declare i32 %s/s/declare i32 %s/declare i32* %s/' %s",i.c_str(),i.c_str(),i.c_str(),"./temp.dot");
            system(s);
        }
        for(auto i : condition)
        {
            char s[100];
            sprintf(s,"sed -i '0,/declare i32 %s/s/declare i32 %s/declare i1 %s/' %s",i.c_str(),i.c_str(),i.c_str(),"./temp.dot");
            system(s);
        }
        for(int i = 0; i < dymaticArray.size(); i++) {
            char s[120];
            sprintf(s,"sed -i '0,/declare i32 %s/s/declare i32 %s/declare i32 %s[%d]/' %s",dymaticArray[i].c_str(),dymaticArray[i].c_str(),dymaticArray[i].c_str(),dymaticArrayval[i],"./temp.dot");
            system(s);
        }
        char *file = "./temp.dot";
        getLinearIR(file, function);
        char s[100];
        sprintf(s,"dot -Tpng ./temp.dot -o %s",output_file_path);
        system(s);
        system("rm -rf temp.dot");
    }
}
