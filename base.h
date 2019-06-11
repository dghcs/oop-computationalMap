#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class base
{
protected:
    float value;
    string name;    //  当前变量名
    bool assigned = false;  //判断当前变量是否赋值,初始化为false
    vector <base*> rely;     //  得到当前node所依赖的node
public:
    base();
    base(float val);
    virtual ~base();
    float getval();     //  获取value
    string getname();   //  获取变量名称
    void setname(string Name);  //  为变量命名
    virtual void setoperator(string s){};
    virtual void insert(base* p){};   //  在rely中插入当前变量所依赖的变量
    bool isassigned();      //     判断当前变量是否赋值
    void isassigned(float val);     //  为当前变量赋值
    void remove();  //  撤销变量赋值状态
    virtual bool cansolve()=0;
    virtual float solve() = 0;
};

class placeholder : public base
{
public:
    placeholder();
    ~placeholder();
    bool cansolve()
    {
    	if(!assigned){
    		cout<<"ERROR: Placeholder missing"<<endl;
    		return false;
		}
        return true;
    }
    float solve(){
    	return value;
	}
};

class constant : public base
{
public:
    constant(float val);
    ~constant();
    bool cansolve() {return true;}
    float solve(){
    	return value;
	}
};


class variable : public base
{
public:
    variable(float val);
    ~variable();
    bool cansolve() {return true;}
    float solve(){
    	return value;
	}
};
