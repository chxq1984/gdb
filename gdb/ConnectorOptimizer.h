#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <climits>
#include "SqlGlobal.h"

class SqlGlobal;
using namespace std;

class ConnectorNode {
	//用于进行优化的连接结点
public:
	map<string, int> Vs;//记录需要使用到的属性V值
	int T;//表的T值，即元组数
	string tableName;//表名
	void showInfo();
};

class Individual{
	//个体结构体
public:
	vector<ConnectorNode*> cnodeNames;
	long long int cost;//当前排序代价
	vector<int> order;
	Individual(vector<ConnectorNode*>names,vector<int>order);
};

class ConnectorOptimizer
{
	//连接优化器
private:
	vector<ConnectorNode*>* cnodes;
public:
	vector<ConnectorNode*>* best;//存储最终最优排序结果
	ConnectorOptimizer(vector<ConnectorNode*>& cnodes);
	void optimizer();//执行优化过程
private:
	vector<vector<int>> getRandomIndividual(int n);//获得n个随机排列的随机数组
	void RandomArray(vector<int>oldArray, vector<int>& newArray);//数组随机化
	int getChoosenIndex(int individualNum);//进行父体选择
	void getChild(vector<int>&fa1,vector<int>&fa2);//杂交获得子代，结果子代存放于fa2内
	void variation(vector<int>& fa);//变异
	int getPoolSize(int geqo_effort);//计算种群大小
};