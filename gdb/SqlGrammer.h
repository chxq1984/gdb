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
	static const int FROM = 1;//���ĸ����
	static const int CONNECTOR = 2;//���ӷ�
	static const int CONDITION = 3;//��ѯ����
	static const int PROJECT = 4;//ͶӰ����
	static const int DEDUPLICATE = 5;//ȥ�ط���
	static const int ORDERLIST = 6;//����
	static const int INSERT = 7;//����
	static const int UPDATE = 8;//����
	static const int DELETE = 9;//ɾ��
	static map<int, string> typeMap;
	static void initMap();
	static string getType(int type);
};

class GrammerNode {
	//�﷨���ڵ�
public:
	int type;//�ڵ�����
	vector<string> infos;//�洢���ͣ����������ݲ�ͬ�Ľڵ����ͽ��н��
	GrammerNode* left;//���ӽڵ�
	GrammerNode* right;//���ӽڵ�
	void addInfo(string st);
	void showInfo();//չʾ����

	PhyPlanNode* transform2PlanNode(GrammerNode* father);//���﷨���ڵ�ת��Ϊ����ƻ��ڵ�
private:
	PhyPlanNode* transFmFrom(GrammerNode* father);//��FROM����ת��Ϊ����ƻ��ڵ�
	PhyPlanNode* transFmCondition();//��Condition����ת��Ϊ����ƻ��ڵ�
	PhyPlanNode* transFmOrder();//��ORDER����ת��Ϊ����ƻ��ڵ�
	PhyPlanNode* transFmProject();//��PROJECT(ͶӰ)ת��Ϊ����ƻ��ڵ�
	PhyPlanNode* transFmConnector();//��CONNECTOR(����)ת��Ϊ����ƻ��ڵ�
	PhyPlanNode* transFmDelete();//��deleteת��Ϊ����ƻ����
	PhyPlanNode* transFmInsert();//��insertת��Ϊ����ƻ����
	PhyPlanNode* transFmUpdate();//��updateת��Ϊ�����Ͻ��
};

class SqlGrammer
{
public:
	GrammerNode* root;
	void showInfo();//��װ��������
	PhyPlanNode* transform2PhysicPlan();//�����ʽ��ת��Ϊ����ƻ���
	void optimiza();//�Ż����ʽ��

private:
	void bacLoopTree(GrammerNode* node);//��������������Ϣ
	PhyPlanNode* copyFromGrammer(GrammerNode* gnode);//�����ʽ��"����"Ϊ����ƻ���
	void optimizeSelect();//�Ż���ѯ��������ѯ����
	void optimizeConnect();//�Ż�����˳��
	void updateConnectOrder(GrammerNode*croot,queue<string>&order);//��������˳��
	int isAllNatural(GrammerNode* croot);//�ж��Ƿ�ȫΪ��Ȼ����
	
	//����Ϊ����������
	vector<string>* findTablesByAttr(GrammerNode* condition);//����condition��������Щ�����ر���
	//vector<string>* findConnectTables(GrammerNode* conRoot);//����connect�����ӵ����б���
	void findConnectTable(GrammerNode* conRoot,vector<ConnectorNode*>& cnodes);//��connect������Ϣ��װΪConnectorNode������
	ConnectorNode* createConnectNode(GrammerNode* target);//����Grammernode������Ӧ��Connectornode
	GrammerNode* findFatherNode(string childInfo, GrammerNode* head);//��head��ʼ�ҵ�info[0]ΪchildInfo�ĸ����
	GrammerNode* findFatherNode(GrammerNode* child, GrammerNode* head);//��head��ʼ�ҵ�child�ĸ����
	GrammerNode* findNodeByInfo(string info,GrammerNode* head);//����infos[0]==info�Ľ��
	GrammerNode* findConnect();//Ѱ�ҵ�һ��connect���

	string findAttrSource(string attrName,vector<string>&tableNames);//ͨ�������ֵ����attrName�������ű������������ű��򷵻�""

};

