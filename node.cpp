
#include"node.h"

using namespace std;


node::node(){}
node::node(float val)
{
    value = val;
    assigned = true;
}
node::~node(){}

void node::setval(float val)
{
    value = val;
    assigned = true;
}

void node::setoperator(string s)
{
    theoperator = s;
}

void node::insert(base* p)
{
    rely.push_back(p);
}

//  判断当前节点是否可以计算
bool node::cansolve()
{

    if(assigned) return true;   //  当前节点已计算过，且可计算

    //  根据得到该节点的运算方式，判断其依赖节点是否可计算（1、2、3个）
    if(theoperator == "+" || theoperator == "-" || theoperator == "*" || 
        theoperator == ">" || theoperator == "<" || theoperator == ">=" || 
        theoperator == "<=" || theoperator == "==")
        return (rely[0]->cansolve() && rely[1]->cansolve());
    
    if(theoperator == "/")
    {
        if(rely[0]->cansolve() == false || rely[1]->cansolve() == false)
            return false;
        if(rely[1]->solve() == 0.0000)     //  除法分母不能为0
        {
            cout << "ERROR: Division by zero" << endl;
            return false;
        }
        return true;
    }

    if(theoperator == "SIN" || theoperator == "EXP" || theoperator == "TANH" || 
        theoperator == "SIGMOID" || theoperator == "PRINT")
        return rely[0]->cansolve();

    if(theoperator == "LOG")
    {
        if(rely[0]->cansolve())
        {
            if(rely[0]->solve() > 0.0000) return true; //  对数运算参数必须大于0
            else
            {
                cout << "ERROR: LOG operator's input must be positive" << endl;
                return false;
            }
        }
        return false;
    }

    if(theoperator == "COND")
    {
        if(rely[0]->cansolve() )
        {
            if(rely[0]->solve()>0)
            {
                if(rely[1]->cansolve()) return true;
            }
            else
            {
                if(rely[2]->cansolve()) return true;
            }
        }
        return false;
    }

    return true;
}

//  计算当前节点的值
float node::solve()
{
    if(assigned)    //  当前节点已经计算过，直接返回
        return this->value;

    //  根据运算法则计算当前节点，递归运算
    float tmp;
    if(theoperator == "+")
    {
        tmp = (rely[0]->solve() + rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "-")
    {
        tmp = (rely[0]->solve() - rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "*")
    {
        tmp = (rely[0]->solve() * rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "/")
    {
        tmp = (rely[0]->solve() / rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == ">")
    {
        tmp = (rely[0]->solve() > rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "<")
    {
        tmp = (rely[0]->solve() < rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == ">=")
    {
        tmp = (rely[0]->solve() >= rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "<=")
    {
        tmp = (rely[0]->solve() <= rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "==")
    {
        tmp = (rely[0]->solve() == rely[1]->solve());
        this->setval(tmp);
    }

    if(theoperator == "SIN")
    {
        tmp = sin(rely[0]->solve());
        this->setval(tmp);
    }

    if(theoperator == "LOG")
    {
        tmp =log(rely[0]->solve());
        this->setval(tmp);
    }

    if(theoperator == "EXP")
    {
        tmp = exp(rely[0]->solve());
        this->setval(tmp);
    }

    if(theoperator == "TANH")
    {
        tmp = tanh(rely[0]->solve());
        this->setval(tmp);
    }

    if(theoperator == "SIGMOID")
    {
        tmp = (1.0 / (1 + exp(-rely[0]->solve())));
        this->setval(tmp);
    }

    if(theoperator == "PRINT")
    {
        tmp = (rely[0]->solve());
        this->setval(tmp);
        cout << "PRINT operator: " << rely[0]->getname() << " = " << 
            setiosflags(ios::fixed) << setprecision(4) 
            << rely[0]->getval() << endl;
    }

    if(theoperator == "COND")
    {
        if(rely[0]->solve() > 0) tmp = (rely[1]->solve());
        else tmp = (rely[2]->solve());
        this->setval(tmp);
    }
    return this->value;
}


