#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "Transaction.h"
using namespace std;

class PhyPlanNode {
	//物理计划树节点
private:
	vector<string> parameters;//参数
	vector<string> additions;//附加内容

public:
	PhyPlanNode* left;
	PhyPlanNode* right;
	string methodName;//所采用的方法名

public:
	void addParameter(string parameter);
	void addAddition(string addition);
	void showParameters();//展示参数信息-for debug
	void showAdditions();//展示附加信息
	vector<string>& getParameters();//获取参数
	vector<string>& getAddition();//获取附加内容
};

class PhysicalPlan
{
	//物理计划
public:
	PhyPlanNode* root;
	void showPlan();
private:
	void backLoopTree(PhyPlanNode* ppnode);//后根遍历计划树
public:
	static bool canFinish(vector<PhyPlanNode*>& phyNodes);//判断事务能否进行
	static string getTableName(PhyPlanNode* root);//获取计划树涉及的表名
};