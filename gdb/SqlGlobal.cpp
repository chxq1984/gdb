#include "SqlGlobal.h"
SqlGlobal* SqlGlobal::instance = nullptr;
SqlGlobal* SqlGlobal::getInstance()
{
	if (instance == nullptr)
		instance = new SqlGlobal();
	return instance;
}

int SqlGlobal::getB(string r)
{
	return getRandom(60);
}

int SqlGlobal::getT(string r)
{
	if (r == "R")
		return 1000;
	else if (r == "S")
		return 2000;
	else if (r == "U")
		return 5000;
	return getRandom(10000);
}

int SqlGlobal::getV(string r, string a)
{
	if (r == "R" && a == "b")
		return 20;
	else if (r == "S" && a == "b")
		return 50;
	else if (r == "S" && a == "c")
		return 100;
	else if (r == "U" && a == "c")
		return 500;
	return getRandom(7000);
}


vector<string> SqlGlobal::getAttribute(string tableName)
{
	vector<string> attributes;
	if (tableName == "R") {
		//����1����
		attributes.push_back("b");
	}
	else if (tableName == "S") {
		//����2����
		attributes.push_back("b");
		attributes.push_back("c");
	}
	else if (tableName == "student") {
		attributes.push_back("age");
	}
	else {
		//������������
		attributes.push_back("c");
	}
	return attributes;
}

bool SqlGlobal::hasIndex(string tablename, string attribute)
{
	if (tablename == "A" && attribute == "b")
		return true;
	else if (tablename == "A" && attribute == "c")
		return true;
	else
		return false;
}

long long int SqlGlobal::calConnect(vector<ConnectorNode*>& connect)
{
	ConnectorNode* cnode = connect.front();
	vector<long long int> costs;//ͳ�ƴ���
	long long int size = cnode->T;//���Ӵ�С
	for (int m = 1;m < connect.size();m++) {
		ConnectorNode* nenode = connect.at(m);//��һ��node,��node��cnode���бȽ�
		size *= nenode->T;
		map<string, int>::iterator iter = cnode->Vs.begin();
		int divisor = 1;//����
		for (;iter != cnode->Vs.end();iter++) {
			//�������
			string attrName = iter->first;//Ԫ����
			if (nenode->Vs.count(attrName)) {
				//nenodeͬ�����ڴ�����
				divisor *= max(nenode->Vs[attrName], cnode->Vs[attrName]);//�õ��ϴ�ֵ
			}
		}
		size /= divisor;
		costs.push_back(size);
		cnode = nenode;
	}

	long long int result = 0;
	for (int m = 0;m < costs.size() - 1;m++) {
		result += costs.at(m);
	}
	return result;
}

int SqlGlobal::getRandom(int min)
{
	srand((unsigned)time(NULL));
	return min + int(rand());
}
