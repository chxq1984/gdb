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
	int id;							// �ͻ���Ψһ��ʶ
	queue<string> commands;	        // �������	(��ǰ�û���һϵ�в�����
	int flags;						// 0��δ��ʼ����1�������������жϽ׶Σ�10��δִ��ǰ�������⣬�쳣�˳���11����������ǰδ�����쳣��������ִ��
	queue<string> myWatchedQueue;	// ��ǰ�ͻ������ڼ����ŵı�
	watchedFlow* watchedTable1;      // ���ӵ��ܱ� (����ģ��ֻ��һ�����������ֵ䣩   ��������ֻ������������е�д�����ü����--select--testdemo1
	watchedFlow* watchedTable2;													//   ��������ֻ��д�����������Ķ�д�������ü����--update--testdemo2
	redisDb* db;					// ��ǰ���õ����ݿ�

public:
	redisClient();
	~redisClient();
};

