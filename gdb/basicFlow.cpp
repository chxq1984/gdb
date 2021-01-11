#include "basicFlow.h"
#include <iostream>

using namespace std;

basicFlow::basicFlow(){}

basicFlow::~basicFlow(){}

void basicFlow::initClientMultiState()
{
	c->flags = 0;
	while (!c->commands.empty())
		c->commands.pop();
	while (!c->commands.empty())
		c->myWatchedQueue.pop();
	cout << "�����ʼ���ɹ�" << endl;
}

void basicFlow::multiCommand()
{
	if (c->flags == 1) {   
		cout << "�����Ѿ���ʼ��" << endl;
		return;
	}
	cout << "��������ɹ�" << endl;
	c->flags = 1;
}

void basicFlow::queueMultiCommand()  // ��Ϊ���һ�����suanle...
{
	int number1 = testDemo1.size();
	int number2 = testDemo2.size();

	//cout << "�������" << endl;
	for (int i = 0; i < number1; i++) {
		string comd = testDemo1.front();
		c->commands.push(comd);
		testDemo1.pop();
	}

	for (int i = 0; i < number2; i++) {
		string comd = testDemo2.front();
		c->commands.push(comd);
		testDemo2.pop();
	}
	//Sleep(1000);

	// �����ӵı�ӵ��Լ��ļ��Ӷ�����ȥ
	c->myWatchedQueue = testTable1;
	queue<string> q = testTable2;
	int number = q.size();
	for (int i = 0; i < number; i++) {
		c->myWatchedQueue.push(q.front());
		q.pop();
	}

	// ͬʱ�ü����ֵ������Щ�����Ұ��Լ����������ֵ����Ӧ����
	c->watchedTable1->watchCommand(c, testTable1);
	c->watchedTable2->watchCommand(c, testTable2);

	// ����ִ�е����������������
	c->flags = 11;

}

bool basicFlow::execCommand()
{
	if (c->flags == 0) {
		cout << "û������Ҫ��ʼ" << endl;
		return false;
	}
	if (c->flags == 10) {
		cout << "����ʼִ��֮ǰ�����ӵı��޸ģ����ֳ�ͻ���˳�ִ��" << endl;
		return false;
	}

	// 11 ���������ı�־�ˣ�����ֱ��ȥ����
//send(execWords1);
	//send(execWords2);

	// ����Ƿ��д����������������������ĳ����ͬ�����Ŀͻ���flags��Ϊ10.��ʾ�����ڼ䷢���˸��ģ���ȡ��ִ��
	// �������Լ�ִ�У�Ҫȥ�޸ı��˵ı�־λȥ������ִ���ˣ�������Ӧ�仯�����׳��쳣��
	c->watchedTable1->TouchWatchedKey(execTables1);
	c->watchedTable2->TouchWatchedKey(execTables2);

	// ͬʱҲ�ð��ܼ��ӱ��е�ǰ�ͻ����漰���ļ�ض�������
	//cout << "ִ�е����������֮���漰���ı���ȡ������" << endl;
	c->watchedTable1->CleanwatchedKey(c, c->myWatchedQueue);
	c->watchedTable2->CleanwatchedKey(c, c->myWatchedQueue);

	return true;
}

void basicFlow::discardTransaction()
{
	// initClientMultiState();	// pop�������ԣ������ź���ɣ���ʵ��ʱ�Լ��ļ��Ӷ����Ѿ�������

	// ͬʱҲ�ð��ܼ��ӱ��е�ǰ�ͻ����漰���ļ�ض�������
	cout << "ִ����ɵ������漰���ı�ȡ������" << endl;
	c->watchedTable1->CleanwatchedKey(c, c->myWatchedQueue);
	c->watchedTable2->CleanwatchedKey(c, c->myWatchedQueue);

	initClientMultiState();
}

void basicFlow::discardCommand()
{
	if (c->flags == 0) {
		cout << "������״̬���޷�ȡ��" << endl;
		return;
	}
	discardTransaction();
	basicFlow:: ~basicFlow();
	cout << "����ȡ��" << endl;
}