#pragma once
#include<iostream>
#include<sstream>
#include<string>
#include<vector>
#include<map>
#include<iomanip>
#include<cmath>
#include"base.h"

using namespace std;

class node : public base
{
private:
    string theoperator;     //  得到当前变量所使用的运算符
public:
    node();
    node(float val);
    ~node();
    void setval(float val);     //  为当前节点赋值
    virtual void setoperator(string s);  //将theoperator赋值
    virtual void insert(base* p);   //  在rely中插入当前变量所依赖的变量
    bool cansolve();   //  判断当前变量是否是可计算的
    float solve(); //  计算当前变量
}; 
