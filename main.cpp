#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "base.h"
#include "node.h"
#include "input.h"

using namespace std;

int main()
{
    //变量的输入
    InputNode();
    
    //节点的输入
    Inputoperate();
    
    //操作的输入
    Inputevalnum();

    return 0;
}