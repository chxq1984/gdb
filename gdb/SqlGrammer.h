#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "PhysicalPlan.h"
#include "Translator.h"
#include <queue>
#include <stack>
#include "ConnectorOptimizer.h"
#include "SqlGlobal.h"
using namespace std;

class GrammerParameter {
public:
	static const int FROM = 1;//从哪个表查
	static const int CONNECTOR = 2;//连接符
	static const int CONDITION = 3;//查询条件
	static const int PROJECT = 4;//投影运算
	static const int DEDUPLICATE = 5;//去重符号
	static const int ORDERLIST = 6;//排序
	static const int INSERT = 7;//插入
	static const int UPDATE = 8;//更新
	static const int DELETE = 9;//删除
	static map<int, string> typeMap;
	static void initMap();
	static string getType(int type);
};

class GrammerNode {
	//语法树节点
public:
	int type;//节点类型
	vector<string> infos;//存储类型，解读规则根据不同的节点类型进行解读
	GrammerNode* left;//左子节点
	GrammerNode* right;//右子节点
	void addInfo(string st);
	void showInfo();//展示内容

	PhyPlanNode* transform2PlanNode(GrammerNode* father);//由语法树节点转换为物理计划节点
private:
	PhyPlanNode* transFmFrom(GrammerNode* father);//将FROM类型转换为物理计划节点
	PhyPlanNode* transFmCondition();//将Condition类型转换为物理计划节点
	PhyPlanNode* transFmOrder();//将ORDER类型转换为物理计划节点
	PhyPlanNode* transFmProject();//将PROJECT(投影)转换为物理计划节点
	PhyPlanNode* transFmConnector();//将CONNECTOR(连接)转换为物理计划节点
	PhyPlanNode* transFmDelete();//将delete转换为物理计划结点
	PhyPlanNode* transFmInsert();//将insert转换为物理计划结点
	PhyPlanNode* transFmUpdate();//将update转换为物理结合结点
};

class SqlGrammer
{
public:
	GrammerNode* root;
	void showInfo();//封装遍历函数
	PhyPlanNode* transform2PhysicPlan();//将表达式树转换为物理计划树
	void optimiza();//优化表达式树

private:
	void bacLoopTree(GrammerNode* node);//后根遍历树输出信息
	PhyPlanNode* copyFromGrammer(GrammerNode* gnode);//将表达式树"复制"为物理计划树
	void optimizeSelect();//优化查询，即将查询后移
	void optimizeConnect();//优化连接顺序
	void updateConnectOrder(GrammerNode*croot,queue<string>&order);//更新连接顺序
	int isAllNatural(GrammerNode* croot);//判断是否全为自然连接
	
	//以下为树操作函数
	vector<string>* findTablesByAttr(GrammerNode* condition);//查找condition作用于哪些表，返回表名
	//vector<string>* findConnectTables(GrammerNode* conRoot);//查找connect所连接的所有表名
	void findConnectTable(GrammerNode* conRoot,vector<ConnectorNode*>& cnodes);//将connect连接信息封装为ConnectorNode并返回
	ConnectorNode* createConnectNode(GrammerNode* target);//根据Grammernode创建对应的Connectornode
	GrammerNode* findFatherNode(string childInfo, GrammerNode* head);//由head开始找到info[0]为childInfo的父结点
	GrammerNode* findFatherNode(GrammerNode* child, GrammerNode* head);//由head开始找到child的父结点
	GrammerNode* findNodeByInfo(string info,GrammerNode* head);//查找infos[0]==info的结点
	GrammerNode* findConnect();//寻找第一个connect结点

	string findAttrSource(string attrName,vector<string>&tableNames);//通过数字字典查找attrName属于哪张表，若存在于两张表则返回""

};

