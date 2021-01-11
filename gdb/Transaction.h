#pragma once
#include "redisClient.h"
#include "basicFlow.h"
#include "watchedFlow.h"

class Transaction
{
public:
	~Transaction() {}
	static bool check(queue<string> tables, vector<string> type);

	static void delInstance();
private:
	Transaction() {}
	Transaction & operator=(const Transaction &) = delete;
	Transaction(const Transaction &) = delete;
private:
	static Transaction * m_instance;
};
