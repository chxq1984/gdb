#include "Transaction.h"
Transaction* Transaction::m_instance = nullptr;
bool Transaction::check(queue<string> tables, vector<string> type)
{
	{
		bool flag;
		if (m_instance == nullptr)
		{
			vector<watchedObj> watchedObjs;
			redisDb* db = new redisDb;
			basicFlow* myBasicFlow = new basicFlow;
			watchedFlow* myWatchedFlow = new watchedFlow;
			redisClient* client = new redisClient;

			myWatchedFlow->watchedObjs = watchedObjs;
			client->id = 1;
			client->flags = 0;
			client->watchedTable1 = myWatchedFlow;
			client->watchedTable2 = myWatchedFlow;
			myBasicFlow->c = client;

			// 事务流程
			flag = myBasicFlow->transaction(tables, type);

			delete myBasicFlow;
			delete myWatchedFlow;
			delete client;
			delete db;

		}
		return flag;
	}
}

void Transaction::delInstance()
{
	if (m_instance)
	{
		delete m_instance;
		m_instance = nullptr;
	}
}
