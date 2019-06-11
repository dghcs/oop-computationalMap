#include"base.h"

using namespace std;

//  base:
//  构造与析构
base::base(){}
base::base(float val) : value(val) {}
base::~base(){}

//  获取变量值
float base::getval()
{
    return value;
}

void base::setname(string Name)
{
    name = Name;
}

string base::getname()
{
    return name;
}

//  判断当前变量是否赋值
bool base::isassigned()
{
    return assigned;
}
//  为当前占位符赋值
void base::isassigned(float val)
{
    assigned = true;
    value = val;
}
//  将占位符的赋值状态撤回
void base::remove()
{
    assigned = false;
    for(int i=0;i<rely.size();i++)
    {
        rely[i] -> remove();
    }

}

//  placeholder:
placeholder::placeholder(){}
placeholder::~placeholder(){}

//  constant:
constant::constant(float val)
{
    isassigned(val);
}
constant::~constant(){}

//  variable:
variable::variable(float val)   
{
    isassigned(val);
}
variable::~variable(){}
