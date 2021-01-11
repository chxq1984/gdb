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

//����һ��key
void watchedFlow::watchedForKey(string table, redisClient *c)
{
	int count = watchedObjs.size();
	for (int i = 0; i < count; i++) {
		if (watchedObjs[i].table == table) {
			// push֮ǰ�Ӹ��ж����п��ܸ��û��Ѿ������ˣ�
			// ����ʵҲ�ɲ��ӣ��Ͼ�һֱ�����ţ������ö��λ��
			watchedObjs[i].theClients.push_back(c);
			return;
		}
	}
	watchedObj theWatchedObj;
	theWatchedObj.table = table;
	theWatchedObj.theClients.push_back(c);
	watchedObjs.push_back(theWatchedObj);

}

//��������key
void watchedFlow::watchCommand(redisClient *c, queue<string> testTable)
{
	//cout << "��������ʼ,��ǰ���ӵı����£�" << endl;
	//print(testTable);
	
	int count = testTable.size();
	for (int i = 0; i < count; i++) {
		watchedForKey(testTable.front(), c);
		//cout << "���ּ��ӵı�" << testTable.front() << endl;
		testTable.pop();
	}	

	//cout << "��ʱ�����ֵ�ṹ���£�" << endl;
	//count = watchedObjs.size();
	//for (int i = 0; i < count; i++) {
	//	list<redisClient*>::iterator it;
	//	for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
	//		cout << *it << endl;
	//	}
	//}
}

//������������������������ʲô��֮ǰ�������ֶ��������ݣ�����Ӧ����һ������ִ�еĿ죨д����������������������ִ��ʧ��
void watchedFlow::touchWatchedKey(string table)
{
	int count = watchedObjs.size();
	// ֻ��һ�������ֻҪ�����棬�ͱ��˼����ţ�����Щ���ӵ����ø�һ
	for (int i = 0; i < count; i++) {
		if (watchedObjs[i].table == table) {
			list<redisClient*>::iterator it;
			for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
				(*it)->flags = 10; // һ��ûע��զд�˸� == ��
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
	//cout << "��ʱ�����ֵ�ṹ���£�" << endl;
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
	// �Ȱ�����ͻ��˶��Ƴ�(�ÿͻ���֮ǰ�����ӵ����еļ���
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
	//cout << "��Ҫɾ���ļ��ӱ�" ;
	//print(keys);
	//cout << "ɾ��ǰ�ļ����ֵ�Ϊ��" << endl;
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
		//cout << "������ɾ���ı�Ϊ��" << keys.front() << endl;
		cleanWatchedKey(keys.front(), c);
		keys.pop();
	}
	//cout << "ɾ����ļ����ֵ�Ϊ��" << endl;
	//count = watchedObjs.size();
	//for (int i = 0; i < count; i++) {
	//	list<redisClient*>::iterator it;
	//	for (it = watchedObjs[i].theClients.begin(); it != watchedObjs[i].theClients.end(); it++) {
	//		cout << *it << endl;
	//	}
	//}
}
