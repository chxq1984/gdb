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
	cout << "事务初始化成功" << endl;
}

void basicFlow::multiCommand()
{
	if (c->flags == 1) {   
		cout << "事务已经开始了" << endl;
		return;
	}
	cout << "开启事务成功" << endl;
	c->flags = 1;
}

void basicFlow::queueMultiCommand()  // 设为最后一块入队suanle...
{
	int number1 = testDemo1.size();
	int number2 = testDemo2.size();

	//cout << "命令入队" << endl;
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

	// 将监视的表加到自己的监视队列里去
	c->myWatchedQueue = testTable1;
	queue<string> q = testTable2;
	int number = q.size();
	for (int i = 0; i < number; i++) {
		c->myWatchedQueue.push(q.front());
		q.pop();
	}

	// 同时让监视字典监视这些表，并且把自己链到监视字典的相应表上
	c->watchedTable1->watchCommand(c, testTable1);
	c->watchedTable2->watchCommand(c, testTable2);

	// 正常执行到这里，属于正常结束
	c->flags = 11;

}

bool basicFlow::execCommand()
{
	if (c->flags == 0) {
		cout << "没有事务要开始" << endl;
		return false;
	}
	if (c->flags == 10) {
		cout << "事务开始执行之前，监视的表被修改，出现冲突，退出执行" << endl;
		return false;
	}

	// 11 就是正常的标志了，可以直接去处理
//send(execWords1);
	//send(execWords2);

	// 检测是否有触碰的情况发生，将监视着某个相同主键的客户端flags置为10.表示监视期间发生了更改，需取消执行
	// 这里是自己执行，要去修改别人的标志位去，我这执行了，发生相应变化，就抛出异常了
	c->watchedTable1->TouchWatchedKey(execTables1);
	c->watchedTable2->TouchWatchedKey(execTables2);

	// 同时也得把总监视表中当前客户端涉及到的监控对象给清除
	//cout << "执行的事务再完成之后，涉及到的表将会取消监视" << endl;
	c->watchedTable1->CleanwatchedKey(c, c->myWatchedQueue);
	c->watchedTable2->CleanwatchedKey(c, c->myWatchedQueue);

	return true;
}

void basicFlow::discardTransaction()
{
	// initClientMultiState();	// pop的特殊性，把它放后面吧，其实此时自己的监视队列已经清完了

	// 同时也得把总监视表中当前客户端涉及到的监控对象给清除
	cout << "执行完成的事务涉及到的表被取消监视" << endl;
	c->watchedTable1->CleanwatchedKey(c, c->myWatchedQueue);
	c->watchedTable2->CleanwatchedKey(c, c->myWatchedQueue);

	initClientMultiState();
}

void basicFlow::discardCommand()
{
	if (c->flags == 0) {
		cout << "非事务状态，无法取消" << endl;
		return;
	}
	discardTransaction();
	basicFlow:: ~basicFlow();
	cout << "事务取消" << endl;
}