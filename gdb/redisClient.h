#pragma once
#include <list>
#include <queue>
#include <string>
#include "redisDb.h"
#include "watchedFlow.h"

using namespace std;

class redisClient
{				 
public:
	int id;							// 客户端唯一标识
	queue<string> commands;	        // 命令队列	(当前用户的一系列操作）
	int flags;						// 0，未开始事务；1，正处于事务判断阶段；10，未执行前遇到问题，异常退出；11，即将运行前未遇到异常，可立即执行
	queue<string> myWatchedQueue;	// 当前客户端正在监视着的表
	watchedFlow* watchedTable1;      // 监视的总表 (整个模块只有一个，即监视字典）   共享锁表、只存读、但是所有的写操作得检查它--select--testdemo1
	watchedFlow* watchedTable2;													//   排它锁表、只存写、但是其他的读写操作都得检查它--update--testdemo2
	redisDb* db;					// 当前作用的数据库

public:
	redisClient();
	~redisClient();
};

