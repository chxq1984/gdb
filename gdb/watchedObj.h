#pragma once

#include <string>
#include <list>

using namespace std;

class redisClient;
class watchedObj
{
public:
	string table;
	list<redisClient *> theClients;
public:
	watchedObj();
	~watchedObj();
};
