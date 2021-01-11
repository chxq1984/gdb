#pragma once
#include <queue>
#include "redisClient.h"

using namespace std;
			// Ŀǰ�������ȫ�����ӣ���Ҫ����insert�����ı�Ҳ�����м�����
class basicFlow
{
public:
	redisClient *c;				  // ��Ӧ�Ŀͻ���
	queue<string> testDemo1;       // ���ݿ������䣬������
	queue<string> testTable1;      // ת�������漰���ı�
	queue<string> testDemo2;       // ���ݿ������䣬������
	queue<string> testTable2;      // ת�������漰���ı�

	queue<string> execWords1;	  // Ҫִ�е����
	queue<string> execTables1;     // ִ���漰���ı�
	queue<string> execWords2;	  // Ҫִ�е����
	queue<string> execTables2;     // ִ���漰���ı�

public:
	basicFlow();
	~basicFlow();

	void initClientMultiState();
	void multiCommand();
	void queueMultiCommand();
	bool execCommand();
	void discardTransaction();
	void discardCommand();

	vector<string> split(string str, string pattern)
	{
		int pos;
		vector<string> result;

		str += pattern;//��չ�ַ����Է������
		int size = str.size();

		for (int i = 0; i<size; i++) {
			pos = str.find(pattern, i);
			if (pos<size) {
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}
	 
	bool transaction(queue<string> tables, vector<string> type) {
		int count = type.size();
		for (int i = 0; i < count; i++)
		{
			string table = tables.front();
			vector<string> str = split(table, " ");
			int k = str.size();
			if (type.at(i) == "SELECT" || type.at(i) == "select") {
				testDemo1.push(type.at(i));
				execWords1.push(type.at(i));
				for (int j = 0; j < k; j++) {
				   testTable1.push(str.at(j));
				   execTables1.push(str.at(j));
				}
			}
			else if (type.at(i) == "UPDATE" || type.at(i) == "update") {
				testDemo2.push(type.at(i));
				execWords2.push(type.at(i));
				for (int j = 0; j < k; j++) {
					testTable2.push(str.at(j));
					execTables2.push(str.at(j));
				}
			}
		}
		queueMultiCommand();
		return execCommand();
	}
};

