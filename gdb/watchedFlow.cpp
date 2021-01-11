#include "watchedFlow.h"
#include "watchedObj.h"
#include "redisClient.h"
#include <algorithm>

watchedFlow::watchedFlow(){}

watchedFlow::~watchedFlow(){}

void print(queue<string> Queue) {
	queue<string> q = Queue;
	int count = q.size();
	for (int i = 0; i < count; i++) {
		cout << q.front() << " ;";
		q.pop();
	}
}

//监视一个key
void watchedFlow::watchedForKey(string table, redisClient *c)
{
	int count = watchedObjs.size();
	for (int i = 0; i < count; i++) {
		if (watchedObjs[i].table == table) {
			// push之前加个判定，有可能该用户已经存在了，
			// 但其实也可不加，毕竟一直更新着，大不了置多遍位呗
			watchedObjs[i].theClients.push_back(c);
			return;
		}
	}
	watchedObj theWatchedObj;
	theWatchedObj.table = table;
	theWatchedObj.theClients.push_back(c);
	watchedObjs.push_back(theWatchedObj);

}

//监视所有key
void watchedFlow::watchCommand(redisClient *c, queue<string> testTable)
{
	//cout << "监视事务开始,当前监视的表如下：" << endl;
	//print(testTable);
	
	int count = testTable.size();
	for (int i = 0; i < count; i++) {
		watchedForKey(testTable.front(), c);
		//cout << "本轮监视的表：" << testTable.front() << endl;
		testTable.pop();
	}	

	//cout << "此时监视字典结构如下：" << endl;
	//count = watchedObjs.size();
	//for (int i = 0; i < count; i++) {
	//	list<redisClient*>::iterator it;
	//	for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
	//		cout << *it << endl;
	//	}
	//}
}

//触碰到主键，触碰的条件是什么，之前是有人手动更改数据，现在应该是一个事务执行的快（写操作），导致了其它事务执行失败
void watchedFlow::touchWatchedKey(string table)
{
	int count = watchedObjs.size();
	// 只有一种情况，只要在里面，就被人监视着，给这些监视的人置负一
	for (int i = 0; i < count; i++) {
		if (watchedObjs[i].table == table) {
			list<redisClient*>::iterator it;
			for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
				(*it)->flags = 10; // 一下没注意咋写了个 == 呢
				// cout << "key:" << key << (*it)->flags << endl;
			}
			return;
		}
	}
}

void watchedFlow::TouchWatchedKey(queue<string> keys)
{
	if (watchedObjs.size() == 0)
		return;
	int count = keys.size();
	for (int i = 0; i < count; i++) {
		touchWatchedKey(keys.front());
		keys.pop();
	}
	//cout << "此时监视字典结构如下：" << endl;
	//count = watchedObjs.size();
	//for (int i = 0; i < count; i++) {
	//	list<redisClient*>::iterator it;
	//	cout << watchedObjs[i].table << "  ";
	//	for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
	//		cout << *it << endl;
	//	}
	//}
}

void watchedFlow::cleanWatchedKey(string table, redisClient * c)
{
	int count = watchedObjs.size();		  
	// 先把这个客户端都移除(该客户端之前所监视的所有的键）
	for (int i = 0; i < count; i++) {
		if (watchedObjs[i].table == table) {
			list<redisClient*>::iterator it;
			for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
				if ((*it)->id == c->id)
					watchedObjs[i].theClients.erase(it);
				break;
			}
			continue;
		}
	}
}

void watchedFlow::CleanwatchedKey(redisClient * c, queue<string> keys)
{
	//cout << "需要删除的监视表：" ;
	//print(keys);
	//cout << "删除前的监视字典为：" << endl;
	//int count1 = watchedObjs.size();
	//for (int i = 0; i < count1; i++) {
	//	list<redisClient*>::iterator it;
		//cout << watchedObjs[i].table << "  ";
		//for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
		//	cout << *it << endl;
		//}
	//}
	
	int count = keys.size();
	for (int i = 0; i < count; i++) {
		//cout << "本轮中删除的表为：" << keys.front() << endl;
		cleanWatchedKey(keys.front(), c);
		keys.pop();
	}
	//cout << "删除后的监视字典为：" << endl;
	//count = watchedObjs.size();
	//for (int i = 0; i < count; i++) {
	//	list<redisClient*>::iterator it;
	//	for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
	//		cout << *it << endl;
	//	}
	//}
}
