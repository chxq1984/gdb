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
	GrammerNode* transform2Grammer() {};//��Nodeת��Ϊ�﷨���ڵ�
	int type;
};

class Name :public Node {
	//����
public:
	string attrName;//����
	string alias = "";//����
	string tableName = "";//��������
	bool isDistinct = false;//�Ƿ���distinct
	string aggFunc = "";//�ۼ�������
	void showInfo(){}
};

class Attribute:public Node {
	//����
public:
	string attrName;//������
	string alias = "";//����
	string tableName = "";//��������
	bool isDistinct = false;//�Ƿ���distinct
	string aggFunc = "";//�Ƿ񱻾ۼ�����������
	void setName(string attrName,string tableName);
	void setName(string name);//name�ȿ���Ϊa.bҲ����Ϊb��ʽ
	void setName(Name* name);
	void showInfo();
	string getAttributes();//��ȡ�ַ�����ʽ��������Ϣ
};

class Number :public Node {
	//��ֵ
public:
	string number;//��ֵ�ַ���
	void showInfo();
};

class ParaString :public Node {
	//�ַ�������
public:
	string parameter;
	void showInfo();
};

class OrderNode :public Node {
	//orderList�ڵĽڵ�
public:
	Attribute attr;
	string rule = "asc";//�������Ĭ��Ϊasc
	void showInfo();
};

class Relation :public Node {
	//��ϵ(��/��ͼ...)
public:
	string relationName;//��ϵ��
	string alias = "";//����
	int type;//����-��/��ͼ...
	void showInfo();
};

class Operator :public Node{
	//������
public:
	string opName;//������:==/and...
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
	vector<Relation*> fromList;//���relation��query(�Ӳ�ѯ)
	vector<Query*> queryList;
public:
	void addNode(Relation* node);
	void addNode(Query* node);
	void showInfo();
	GrammerNode* transform2Grammer();
};


class Condition :public Node{
	//��whereList

public:
	Attribute* Lattr;//���������
	Operator* soperator;//������
	Attribute* Rattr;//�������Ҳ�

	Condition* lCnode;
	Condition* rCnode;

	Number* rNumber;//����Ϊ����
	ParaString* pString;//����Ϊ�ַ���

	Query* query;//�Ӳ�ѯ

	void showInfo();

	GrammerNode* transform2Grammer();
	string getInfo();//��ȡ���ӽڵ��condition�ַ�����Ϣ
	string getLoopInfo();//ѭ����ȡcondition��ȫ�����ݲ����ַ�����ʽ����
	string setGrammerVec(vector<string>& infos,int count,int leafCount);//�ú�������ķ�ʽ�������
	int getCount();//��ȡ�ڵ���Ŀ

	vector<Condition*>* getSubQueryCondition();//��ȡӵ���Ӳ�ѯ��condition���
	
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
	GrammerNode* transform2GrammerWithSubQuery(vector<Condition*>* conditionWithSub);//condition�ں����Ӳ�ѯ��ת��
	GrammerNode* transform2GrammerWithSimple();//conditionΪ������
	GrammerNode* solveConnect(GrammerNode* root);//��condition�е�a.b=c.e������connector��
	void turnCondition2Connect(GrammerNode* sroot, string condition);//��condition�ڵ�����ת������Ӧ��connector��
	
};

class Insert :public Node {
public:
	string tableName;//����ı���
	vector<string> attributes;//�����ֵ��Ϣ
public:
	void showInfo();
	GrammerNode* transform2Grammer();
};

class Delete :public Node {
public:
	string tableName;//ɾ���ı���
	Condition* condition;//��ɾ���ı�����Ҫ���������
public:
	void showInfo();
	GrammerNode* transform2Grammer();
};

class Update :public Node {
public:
	string tableName;//���µı���
	map<string, string> attr_indexs;//�洢������-����ֵ
	Condition* condition;//���µı���Ҫ���������
public:
	void showInfo();
	GrammerNode* transform2Grammer();
};

class NodeStorage {
public:
	//��ѯ
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
	//�ݴ�name_node��Ϣ
	string text;
	//�洢�ֶ���Ϣ
	vector<Name*> nameList;
	int type;
	
	//����
	Insert* insert;
	vector<string> values;//����ֵ

	//ɾ��
	Delete* del;

	//����
	Update* upd;
	string attr_index[2];//��ֵ��
	map<string, string> attr_indexs;

	//���յ�����ƻ���
	PhyPlanNode* phyNode;//����ƻ����ڵ�
	vector<PhyPlanNode*> phyNodes;//����ƻ����ڵ�����
};