#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include "Transaction.h"
using namespace std;

class PhyPlanNode {
	//����ƻ����ڵ�
private:
	vector<string> parameters;//����
	vector<string> additions;//��������

public:
	PhyPlanNode* left;
	PhyPlanNode* right;
	string methodName;//�����õķ�����

public:
	void addParameter(string parameter);
	void addAddition(string addition);
	void showParameters();//չʾ������Ϣ-for debug
	void showAdditions();//չʾ������Ϣ
	vector<string>& getParameters();//��ȡ����
	vector<string>& getAddition();//��ȡ��������
};

class PhysicalPlan
{
	//����ƻ�
public:
	PhyPlanNode* root;
	void showPlan();
private:
	void backLoopTree(PhyPlanNode* ppnode);//��������ƻ���
public:
	static bool canFinish(vector<PhyPlanNode*>& phyNodes);//�ж������ܷ����
	static string getTableName(PhyPlanNode* root);//��ȡ�ƻ����漰�ı���
};