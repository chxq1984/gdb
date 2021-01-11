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
	int getRandom(int min);//��ȡ>min�������
public:
	//������������������ýӿں���
	int getB(string r);//��ȡ���ɹ�ϵr����Ԫ������Ŀ���
	int getT(string r);//��ȡ��ϵr��Ԫ����
	int getV(string r, string a);//��ȡ��ϵr������a��ֵͬ����Ŀ
	vector<string> getAttribute(string tableName);//��ȡtableName�����е�����
	bool hasIndex(string tablename, string attribute);//�ж��Ƿ�ӵ������

	long long int calConnect(vector<ConnectorNode*>& connect);//����������������,���ӷ�ʽ��vector˳�����
};