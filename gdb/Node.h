#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include "SqlGrammer.h"
#include "Translator.h"
#include "PhysicalPlan.h"

using namespace std;
class Query;
class Node
{
public:
	
	virtual void showInfo() = 0;
	GrammerNode* transform2Grammer() {};//将Node转换为语法树节点
	int type;
};

class Name :public Node {
	//名字
public:
	string attrName;//名字
	string alias = "";//别名
	string tableName = "";//所属表名
	bool isDistinct = false;//是否定义distinct
	string aggFunc = "";//聚集函数名
	void showInfo(){}
};

class Attribute:public Node {
	//属性
public:
	string attrName;//属性名
	string alias = "";//别名
	string tableName = "";//所属表名
	bool isDistinct = false;//是否定义distinct
	string aggFunc = "";//是否被聚集函数所作用
	void setName(string attrName,string tableName);
	void setName(string name);//name既可能为a.b也可能为b形式
	void setName(Name* name);
	void showInfo();
	string getAttributes();//获取字符串形式的属性信息
};

class Number :public Node {
	//数值
public:
	string number;//数值字符串
	void showInfo();
};

class ParaString :public Node {
	//字符串参数
public:
	string parameter;
	void showInfo();
};

class OrderNode :public Node {
	//orderList内的节点
public:
	Attribute attr;
	string rule = "asc";//排序规则，默认为asc
	void showInfo();
};

class Relation :public Node {
	//关系(表/视图...)
public:
	string relationName;//关系名
	string alias = "";//别名
	int type;//类型-表/视图...
	void showInfo();
};

class Operator :public Node{
	//操作符
public:
	string opName;//操作名:==/and...
	void showInfo();
};

class SelList :public Node {
private:
	vector<Attribute*> selList;
public:
	void addAttribute(Attribute* attr);
	void showInfo();
	GrammerNode* transform2Grammer();
};

class FromList :public Node{
private:
	vector<Relation*> fromList;//存放relation与query(子查询)
	vector<Query*> queryList;
public:
	void addNode(Relation* node);
	void addNode(Query* node);
	void showInfo();
	GrammerNode* transform2Grammer();
};


class Condition :public Node{
	//即whereList

public:
	Attribute* Lattr;//操作符左侧
	Operator* soperator;//操作符
	Attribute* Rattr;//操作符右侧

	Condition* lCnode;
	Condition* rCnode;

	Number* rNumber;//可能为数字
	ParaString* pString;//可能为字符串

	Query* query;//子查询

	void showInfo();

	GrammerNode* transform2Grammer();
	string getInfo();//获取无子节点的condition字符串信息
	string getLoopInfo();//循环获取condition的全部数据并以字符串形式返回
	string setGrammerVec(vector<string>& infos,int count,int leafCount);//用后根遍历的方式填充容器
	int getCount();//获取节点数目

	vector<Condition*>* getSubQueryCondition();//获取拥有子查询的condition结点
	
};

class OrderList :public Node {
private:
	vector<OrderNode*> orderList;
public:
	void addOrderNode(OrderNode* ornode);
	void showInfo();
	GrammerNode* transform2Grammer();
};

class GroupList :public Node {
private:
	vector<Attribute*> groupList;
public:
	void addAttribute(Attribute* attr);
	GrammerNode* transform2Grammer();
};

class Query :public Node {
public:
	SelList* selList;
	FromList* fromList;
	Condition* condition = nullptr;
	OrderList* orderList = nullptr;
	GroupList* groupList = nullptr;
	void showInfo();
	GrammerNode* transform2Grammer();

private:
	GrammerNode* transform2GrammerWithSubQuery(vector<Condition*>* conditionWithSub);//condition内含有子查询的转换
	GrammerNode* transform2GrammerWithSimple();//condition为简单条件
	GrammerNode* solveConnect(GrammerNode* root);//将condition中的a.b=c.e调整到connector处
	void turnCondition2Connect(GrammerNode* sroot, string condition);//将condition内的条件转移至对应的connector下
	
};

class Insert :public Node {
public:
	string tableName;//插入的表名
	vector<string> attributes;//具体的值信息
public:
	void showInfo();
	GrammerNode* transform2Grammer();
};

class Delete :public Node {
public:
	string tableName;//删除的表名
	Condition* condition;//所删除的表名需要满足的条件
public:
	void showInfo();
	GrammerNode* transform2Grammer();
};

class Update :public Node {
public:
	string tableName;//更新的表名
	map<string, string> attr_indexs;//存储属性名-具体值
	Condition* condition;//更新的表需要满足的条件
public:
	void showInfo();
	GrammerNode* transform2Grammer();
};

class NodeStorage {
public:
	//查询
	Attribute *attribute;
	OrderNode *orderNode;
	Relation *relation;
	Operator *soperator;
	SelList	*selList;
	FromList *fromList;
	Condition *condision;
	OrderList *orderList;
	GroupList *groupList;
	Query *query;
	Number* rNumber;
	ParaString* pString;

	Name* name;
	//暂存name_node信息
	string text;
	//存储字段信息
	vector<Name*> nameList;
	int type;
	
	//插入
	Insert* insert;
	vector<string> values;//插入值

	//删除
	Delete* del;

	//更新
	Update* upd;
	string attr_index[2];//键值对
	map<string, string> attr_indexs;

	//最终的物理计划树
	PhyPlanNode* phyNode;//物理计划树节点
	vector<PhyPlanNode*> phyNodes;//物理计划树节点容器
};