#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include "ConnectorOptimizer.h"
using namespace std;

class ConnectorNode;
class SqlGlobal {
private:
	SqlGlobal(){}
	static SqlGlobal* instance;
public:
	bool exit = false;
	static SqlGlobal* getInstance();
private:
	int getRandom(int min);//获取>min的随机数
public:
	//以下五个函数均待调用接口函数
	int getB(string r);//获取容纳关系r所有元组所需的块数
	int getT(string r);//获取关系r的元组数
	int getV(string r, string a);//获取关系r中属性a不同值的数目
	vector<string> getAttribute(string tableName);//获取tableName所具有的属性
	bool hasIndex(string tablename, string attribute);//判断是否拥有索引

	long long int calConnect(vector<ConnectorNode*>& connect);//计算表连接所需代价,连接方式按vector顺序进行
};