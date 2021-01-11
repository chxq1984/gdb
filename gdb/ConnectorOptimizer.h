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
	//���ڽ����Ż������ӽ��
public:
	map<string, int> Vs;//��¼��Ҫʹ�õ�������Vֵ
	int T;//���Tֵ����Ԫ����
	string tableName;//����
	void showInfo();
};

class Individual{
	//����ṹ��
public:
	vector<ConnectorNode*> cnodeNames;
	long long int cost;//��ǰ�������
	vector<int> order;
	Individual(vector<ConnectorNode*>names,vector<int>order);
};

class ConnectorOptimizer
{
	//�����Ż���
private:
	vector<ConnectorNode*>* cnodes;
public:
	vector<ConnectorNode*>* best;//�洢��������������
	ConnectorOptimizer(vector<ConnectorNode*>& cnodes);
	void optimizer();//ִ���Ż�����
private:
	vector<vector<int>> getRandomIndividual(int n);//���n��������е��������
	void RandomArray(vector<int>oldArray, vector<int>& newArray);//���������
	int getChoosenIndex(int individualNum);//���и���ѡ��
	void getChild(vector<int>&fa1,vector<int>&fa2);//�ӽ�����Ӵ�������Ӵ������fa2��
	void variation(vector<int>& fa);//����
	int getPoolSize(int geqo_effort);//������Ⱥ��С
};