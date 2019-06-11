#include "input.h"
#include "base.h"
#include "node.h"
#include <iostream>
#include <map>
#include <vector> 
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

map<string, base*> save;       //  定义一个map save,可以通过变量名直接找到变量位置
vector <base*> save_for_delete;//存储结点重名时将即将被覆盖的结点存储起来，便于释放内存 

void InputNode()
{
	//变量的输入
    int n;  //  变量数
    cin >> n;
    string name, type, val;


    for(int i = 0; i < n; i++)
    {
        cin >> name >> type;
        //  判断当前变量的类型
        if(type == "P") 
        {
            base* Newplace = new placeholder();
            Newplace -> setname(name);
            save[name]=Newplace;
        }
        else
        {
            cin >> val;
            if(type == "C") 
            {
                base* Newconstant = new constant(stof(val));
                Newconstant -> setname(name);
                save[name]= Newconstant;
            }
            
            else if(type == "V") 
            {
                base* Newvariable = new variable(stof(val));
                Newvariable -> setname(name);
                save[name]= Newvariable;
            }

        }
    }
}

void Inputoperate()
{
    //节点的输入
	int m;  //  节点数
    cin >> m;
    stringstream s;
    cin.ignore();      //排除换行符对getline的影响
    for(int i = 0; i < m; i++)
    {
        string line;
        string a;
        getline(cin, line);   //    读入一行数据，并将其按空格拆分开
        s.clear();
        s.str(line);
        string Name, Equal;
        s >> Name >> Equal;      //   获取节点名,去掉‘=’符号
        vector <string> buffer;
        base* point = new node; 
        point -> setname(Name);
        while(s>>a)
        {
            buffer.push_back(a);
        }
        if(save.find(Name)!=save.end()) //查找之前是否存在同名结点（指单目、双目等运算符类型），如果存在，将其push_back进save_for_delete以便后来删除而防止内存泄漏 
	    {
		    save_for_delete.push_back(save[Name]);
    	}
	
    	if(buffer.size()==2)//单目运算符
    	{
    		point->insert(save[buffer[1]]);
            point->setoperator(buffer[0]);
            save[Name] = point;
    	} 
    	if(buffer.size()==3)//双目运算符 
    	{
	    	point->insert(save[buffer[0]]);
            point->insert(save[buffer[2]]);
            point->setoperator(buffer[1]);
            save[Name] = point;
	    }
    	if(buffer.size()==4)//COND
    	{
    		point->insert(save[buffer[1]]);
            point->insert(save[buffer[2]]);
            point->insert(save[buffer[3]]);
            point->setoperator(buffer[0]);
            save[Name] = point;
	    }
    }
}

void Inputevalnum()
{
	int q;  //  操作数
    cin >> q;
    stringstream ss;
    float *res = new float [q];     //  记录每一个操作得到的结果
    if(q == 0)  return ;            //  操作数为0则结束程序
    cin.ignore();
    for(int i = 0; i < q; i++)
    {
        string line, command, Name;
        getline(cin, line);
        ss.clear();
        ss.str(line);
        ss >> command >> Name;
        if(command == "EVAL")
        {
            if(!ss.eof())   //  进行变量的赋值操作
            {
                string howmany_s;
                ss >> howmany_s;
                int howmany = stoi(howmany_s);  //  得到赋值操作的次数
                if(howmany > 0)
                {
                    for(int j = 0; j < howmany; j++)    //  进行赋值
                    {
                        string name1, val2;
                        ss >> name1 >> val2;
                        float val = stof(val2);
                        save[name1]->isassigned(val);
                    }
                }
            }

           if(save[Name]->cansolve())
           {
                res[i] = save[Name]->solve();
                cout << setiosflags(ios::fixed) << setprecision(4) << res[i] << endl;
           }
			
            save[Name]->remove();

        }
        else if(command == "SETCONSTANT")   //  进行setconstant操作
        {
            string val_s;
            ss >> val_s;
            float val = stof(val_s);
            res[i] = val;
            save[Name] -> isassigned(val);
        }
        else if(command == "SETANSWER")     //  进行setanswer操作
        {
            string number_s;
            ss >> number_s;
            int number = stoi(number_s);
            res[i] = res[number - 1];
            save[Name] -> isassigned(res[i]);
        }
    }
    
    delete []res;
    
    for(auto it=save.begin();it!=save.end();it++)
	{
		delete it -> second;
	}
	for(auto it=save_for_delete.begin();it!=save_for_delete.end();it++)
	{ 
		delete (*it);
	}
}
