#include "SqlGlobal.h"
SqlGlobal* SqlGlobal::instance = nullptr;
SqlGlobal* SqlGlobal::getInstance()
{
	if (instance == nullptr)
		instance = new SqlGlobal();
	return instance;
}

int SqlGlobal::getB(string r)
{
	return getRandom(60);
}

int SqlGlobal::getT(string r)
{
	if (r == "R")
		return 1000;
	else if (r == "S")
		return 2000;
	else if (r == "U")
		return 5000;
	return getRandom(10000);
}

int SqlGlobal::getV(string r, string a)
{
	if (r == "R" && a == "b")
		return 20;
	else if (r == "S" && a == "b")
		return 50;
	else if (r == "S" && a == "c")
		return 100;
	else if (r == "U" && a == "c")
		return 500;
	return getRandom(7000);
}


vector<string> SqlGlobal::getAttribute(string tableName)
{
	vector<string> attributes;
	if (tableName == "R") {
		//测试1数据
		attributes.push_back("b");
	}
	else if (tableName == "S") {
		//测试2数据
		attributes.push_back("b");
		attributes.push_back("c");
	}
	else if (tableName == "student") {
		attributes.push_back("age");
	}
	else {
		//其他测试数据
		attributes.push_back("c");
	}
	return attributes;
}

bool SqlGlobal::hasIndex(string tablename, string attribute)
{
	if (tablename == "A" && attribute == "b")
		return true;
	else if (tablename == "A" && attribute == "c")
		return true;
	else
		return false;
}

long long int SqlGlobal::calConnect(vector<ConnectorNode*>& connect)
{
	ConnectorNode* cnode = connect.front();
	vector<long long int> costs;//统计代价
	long long int size = cnode->T;//连接大小
	for (int m = 1;m < connect.size();m++) {
		ConnectorNode* nenode = connect.at(m);//下一个node,此node与cnode进行比较
		size *= nenode->T;
		map<string, int>::iterator iter = cnode->Vs.begin();
		int divisor = 1;//除数
		for (;iter != cnode->Vs.end();iter++) {
			//计算除数
			string attrName = iter->first;//元素名
			if (nenode->Vs.count(attrName)) {
				//nenode同样存在此属性
				divisor *= max(nenode->Vs[attrName], cnode->Vs[attrName]);//得到较大值
			}
		}
		size /= divisor;
		costs.push_back(size);
		cnode = nenode;
	}

	long long int result = 0;
	for (int m = 0;m < costs.size() - 1;m++) {
		result += costs.at(m);
	}
	return result;
}

int SqlGlobal::getRandom(int min)
{
	srand((unsigned)time(NULL));
	return min + int(rand());
}
