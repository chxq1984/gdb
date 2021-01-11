#pragma once
#include <string>
#include <vector>
#include <queue>
#include "watchedObj.h"

using namespace std;

class watchedFlow
{
public:			   
	vector<watchedObj> watchedObjs;      // ¼àÊÓ×Öµä

public:
	watchedFlow();
	~watchedFlow();
	void watchedForKey(string key, redisClient *c);
	void watchCommand(redisClient *c, queue<string> testTable);
	void touchWatchedKey(string key);
	void TouchWatchedKey(queue<string> keys);
	void cleanWatchedKey(string key, redisClient *c);
	void CleanwatchedKey(redisClient *c, queue<string> keys);

};

