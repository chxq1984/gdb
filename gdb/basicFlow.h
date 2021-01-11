#pragma once
#include <queue>
#include "redisClient.h"

using namespace std;
			// 目前的这版是全部监视，将要进行insert操作的表也给进行监视了
class basicFlow
{
public:
	redisClient *c;				  // 对应的客户端
	queue<string> testDemo1;       // 数据库基本语句，包括查
	queue<string> testTable1;      // 转化后所涉及到的表
	queue<string> testDemo2;       // 数据库基本语句，包括改
	queue<string> testTable2;      // 转化后所涉及到的表

	queue<string> execWords1;	  // 要执行的语句
	queue<string> execTables1;     // 执行涉及到的表
	queue<string> execWords2;	  // 要执行的语句
	queue<string> execTables2;     // 执行涉及到的表

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

		str += pattern;//扩展字符串以方便操作
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

