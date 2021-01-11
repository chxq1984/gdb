#include "PhysicalPlan.h"

void PhyPlanNode::addParameter(string parameter)
{
	parameters.push_back(parameter);
}

void PhyPlanNode::addAddition(string addition)
{
	additions.push_back(addition);
}

void PhyPlanNode::showParameters()
{
	cout << "paramater:" << endl;
	for (string parameter : parameters) {
		cout << parameter << endl;
	}
}

void PhyPlanNode::showAdditions()
{
	if (additions.empty())
		return;
	cout << "addition:" << endl;
	for (string info : additions)
		cout << info << endl;
	cout << endl;
}

vector<string>& PhyPlanNode::getParameters()
{
	return parameters;
}

vector<string>& PhyPlanNode::getAddition()
{
	return additions;
}

void PhysicalPlan::showPlan()
{
	backLoopTree(root);
}

void PhysicalPlan::backLoopTree(PhyPlanNode* ppnode)
{
	if (ppnode == nullptr)
		return;
	backLoopTree(ppnode->left);
	backLoopTree(ppnode->right);

	cout << "method name:" << ppnode->methodName << endl;
	//cout << "parameter:" << endl;
	ppnode->showAdditions();
	ppnode->showParameters();
	cout << endl << endl;
}

bool PhysicalPlan::canFinish(vector<PhyPlanNode*>& phyNodes)
{
	reverse(phyNodes.begin(), phyNodes.end());//颠倒phyNodes顺序
	/*for (PhyPlanNode* p : phyNodes)
		cout << p->getParameters()[0] << endl;
	cout << endl;*/
	queue<string> tableNames;
	vector<string> type;
	for (PhyPlanNode* root : phyNodes) {
		tableNames.push(getTableName(root));
		if (root->methodName == "Update") {
			type.push_back("update");
		}
		else if (root->methodName != "Insert" && root->methodName != "Delete")
			type.push_back("select");
	}
	
	/*while (!tableNames.empty()) {
		cout << tableNames.front() << endl;
		tableNames.pop();
	}*/

	//调用函数
	return Transaction::check(tableNames,type);//调用事务函数确认是否能够执行
}

string PhysicalPlan::getTableName(PhyPlanNode* root)
{
	string tableNames;
	queue<PhyPlanNode*>phyQueue;
	phyQueue.push(root);
	while (!phyQueue.empty()) {
		PhyPlanNode* target = phyQueue.front();
		phyQueue.pop();
		if (target->left)
			phyQueue.push(target->left);
		if (target->right)
			phyQueue.push(target->right);

		if (target->methodName == "TableScan") {
			//说明为表扫描
			if (tableNames.length() > 0) {
				tableNames += " ";
			}
			tableNames += target->getParameters()[0];
		}
	}
	return tableNames;
}
