#include "Node.h"

void SelList::addAttribute(Attribute* attr)
{
	selList.push_back(attr);
}

void SelList::showInfo()
{
	cout << "SelList:" << endl;
	for (int m = 0;m < selList.size();m++) {
		selList.at(m)->showInfo();
	}
}

GrammerNode* SelList::transform2Grammer()
{
	GrammerNode* node = new GrammerNode();
	node->type = GrammerParameter::PROJECT;
	for (int m = 0;m < selList.size();m++) {
		string info = selList.at(m)->getAttributes();
		node->addInfo(info);
	}
	return node;
}

void FromList::addNode(Relation* node)
{
	fromList.push_back(node);
}

void FromList::addNode(Query* node)
{
	queryList.push_back(node);
}
void FromList::showInfo()
{
	cout << "fromList:" << endl;
	for (int m = 0;m < fromList.size();m++) {
		fromList.at(m)->showInfo();
	}
}
GrammerNode* FromList::transform2Grammer()
{
	reverse(fromList.begin(), fromList.end()); //由于顺序和natural join有关，因此需要保持原序，即倒序
	int fromNumber = fromList.size();//查询的关系数
	for (Relation* relation : fromList) {
		//减去natural标记剩下的才为关系数
		if (relation->relationName == "@natural@") {
			fromNumber--;
		}
	}
	if (fromNumber == 1) {
		//仅一个关系则无需连接
		GrammerNode* node = new GrammerNode();
		node->type = GrammerParameter::FROM;
		node->addInfo(fromList.at(0)->relationName);
		return node;
	}
	int n = 0;
	int connetNumber = fromNumber - 1;//连接符数目,采取左深树，因此数目为关系数-1
	stack<GrammerNode*> grammerStack;
	
	GrammerNode* root = new GrammerNode();//根节点
	root->type = GrammerParameter::CONNECTOR;
	grammerStack.push(root);

	for (int m = 0;m < connetNumber - 1;m++) {
		GrammerNode* gnode = new GrammerNode();
		gnode->type = GrammerParameter::CONNECTOR;
		grammerStack.top()->left = gnode;//连接左节点
		grammerStack.push(gnode);

	}

	while (!grammerStack.empty()) {
		GrammerNode* connector = grammerStack.top();
		grammerStack.pop();
		if (connector->left == nullptr) {
			//说明为最底部节点
			
			if (fromList.at(n)->relationName == "@natural@") {
				connector->addInfo("@natural@");
				n++;
			}
			GrammerNode* gnode = new GrammerNode();
			gnode->type = GrammerParameter::FROM;
			gnode->addInfo(fromList.at(n++)->relationName);
			connector->left = gnode;
			
		}
		
		if (fromList.at(n)->relationName == "@natural@") {
			connector->addInfo("@natural@");
			n++;
		}
		GrammerNode* gnode = new GrammerNode();
		gnode->type = GrammerParameter::FROM;
		gnode->addInfo(fromList.at(n++)->relationName);
		connector->right = gnode;
	}
	return root;
	
}
//
//void Condition::addNode(Node* node)
//{
//	conditions.push_back(node);
//}

void OrderList::addOrderNode(OrderNode* ornode)
{
	orderList.push_back(ornode);
}

void OrderList::showInfo()
{
	cout << "orderList:" << endl;
	for (int m = 0;m < orderList.size();m++) {
		orderList.at(m)->showInfo();
	}
}

GrammerNode* OrderList::transform2Grammer()
{
	GrammerNode* gnode = new GrammerNode();
	gnode->type = GrammerParameter::ORDERLIST;
	for (int m = 0;m < orderList.size();m++) {
		OrderNode* orNode = orderList.at(m);
		string info = orNode->attr.getAttributes() + " " + orNode->rule;//获取排序规则->a desc
		gnode->addInfo(info);
	}
	return gnode;
}

void GroupList::addAttribute(Attribute* attr)
{
	groupList.push_back(attr);
}

GrammerNode* GroupList::transform2Grammer()
{
	return NULL;
}

void Attribute::setName(string attrName, string tableName)
{
	this->attrName = attrName;
	this->tableName = tableName;
}

void Attribute::setName(string name)
{
	int position = name.find(".");
	if (position == name.npos) {
		//说明为b形式
		attrName = name;
	}
	else {
		//说明为a.b形式
		tableName = name.substr(0, position);
		attrName = name.substr(position + 1);
	}
}

void Attribute::setName(Name* name)
{
	attrName = name->attrName;
	alias = name->alias;
	tableName = name->tableName;
	aggFunc = name->aggFunc;	
}

void Attribute::showInfo()
{
	cout << "attribute:" << attrName << endl;
	if (tableName != "")
		cout << "tableName:" << tableName << endl;
}

string Attribute::getAttributes()
{
	string message = "";
	if (tableName != "") {
		//存在表名,a.b形式
		message += tableName + ".";
	}
	message += attrName;
	if (alias != "") {
		//存在别名
		message += " " + alias;
	}
	return message;
}

void Number::showInfo()
{
	cout << "Number:" << number << endl;
}

void OrderNode::showInfo()
{
	cout << "OrderNode:" << endl << "rule:" << rule << endl;
	attr.showInfo();
}

void Relation::showInfo()
{
	cout << "Relation:" << relationName << endl;
}

void Operator::showInfo()
{
	cout << "Operator:" << opName << endl;
}

void Condition::showInfo()
{
	cout << "Condition:" << endl;
	if (Lattr != nullptr) {
		cout << "Lattr:" << endl;
		Lattr->showInfo();
	}
	if (Rattr != nullptr) {
		cout << "Rattr:" << endl;
		Rattr->showInfo();
	}
	if (lCnode != nullptr) {
		cout << "lCnode:" << endl;
		lCnode->showInfo();
	}
	if (rCnode != nullptr) {
		cout << "rCnode:" << endl;
		rCnode->showInfo();
	}
	if (rNumber != nullptr) {
		cout << "rNumber:" << endl;
		rNumber->showInfo();
	}
	if (query != nullptr) {
		cout << "subQuery:" << endl;
		query->showInfo();
	}
	cout << "soperator:" << endl;
	soperator->showInfo();

}

GrammerNode* Condition::transform2Grammer()
{
	GrammerNode* root = new GrammerNode();
	
	root->type = GrammerParameter::CONDITION;
	
	int leafCount = (getCount() - 1) / 2;
	
	setGrammerVec(root->infos, 1, leafCount);//向infos内写入信息，写入过程忽略带子查询的condition
	reverse(root->infos.begin(),root->infos.end());//倒序
	return root;
}

string Condition::getInfo()
{
	string info = "";
	if (rNumber != nullptr) {
		//说明右操作数为数字
		info += Lattr->getAttributes() + " " + soperator->opName + " " + rNumber->number;//a = 10
	}
	else if (pString != nullptr) {
		//说明右操作数为字符串
		info += Lattr->getAttributes() + " " + soperator->opName + " " + pString->parameter;//a = '10'
	}
	else {
		info += Lattr->getAttributes() + " " + soperator->opName + " " + Rattr->getAttributes();//a = b
	}
	return info;
}

string Condition::getLoopInfo()
{
	if (lCnode == nullptr) {
		//说明为叶节点
		return getInfo();
	}
	//说明有子condition
	string leInfo = lCnode->getLoopInfo();//获取左节点信息
	string reInfo = rCnode->getLoopInfo();//获取右节点信息
	string info = leInfo + " " + soperator->opName + " " + reInfo;//a = b and c = e and g = h
	return info;
}

string Condition::setGrammerVec(vector<string>& infos, int count, int leafCount)
{
	if (leafCount == 0) {
		//说明只有一个节点
		if (query == nullptr) {
			//仅当不存在子查询时进行info转换并返回
			infos.push_back(getInfo());
		}
		return "";
	}
	if (lCnode == nullptr) {
		if(query == nullptr)
			return getInfo();
		return "";
	}
	string leInfo = lCnode->setGrammerVec(infos,count+1,leafCount);
	string reInfo = rCnode->setGrammerVec(infos,-1,leafCount);//右节点count设置为-1
	if (count == leafCount) {
		//说明为叶子节点上一层节点
		if (lCnode->query == nullptr) {
			infos.push_back(leInfo);
		}
		if (lCnode->query == nullptr && rCnode->query == nullptr) {
			infos.push_back(soperator->opName);
		}
		if (rCnode->query == nullptr) {
			infos.push_back(reInfo);
		}
		return "";
	}
	else {
		if (rCnode->query == nullptr) {
			infos.push_back(soperator->opName);
			infos.push_back(reInfo);
		}		
		return "";
	}
}

int Condition::getCount()
{
	if (lCnode == nullptr) {
		return 1;
	}
	else {
		int count = 0;
		count += lCnode->getCount();
		count += rCnode->getCount();
		return count+1;

	}
}

vector<Condition*>* Condition::getSubQueryCondition()
{
	vector<Condition*>* storage = new vector<Condition*>;
	queue<Condition*> tmpstack;
	tmpstack.push(this);
	while (!tmpstack.empty()) {
		Condition* top = tmpstack.front();
		tmpstack.pop();//取出首部
		if (top->query != nullptr) {
			//存在子查询
			storage->push_back(top);
		}
		
		if (top->lCnode != nullptr) {
			tmpstack.push(top->lCnode);
		}
		if (top->rCnode != nullptr) {
			tmpstack.push(top->rCnode);
		}
	}
	return storage;
}

void Query::showInfo()
{
	cout << "query:" << endl;
	selList->showInfo();
	fromList->showInfo();
	if (condition)
		condition->showInfo();
	if (orderList)
		orderList->showInfo();
}

GrammerNode* Query::transform2Grammer()
{
	GrammerNode* gnode;
	if (condition) {
		vector<Condition*>* subQueryCondition = condition->getSubQueryCondition();//具有子查询的结点
		if (!subQueryCondition->empty()) {
			//condition中具有子查询
			gnode = transform2GrammerWithSubQuery(subQueryCondition);//调用具有子查询的转换函数
			return solveConnect(gnode);
		}
	}
	gnode = transform2GrammerWithSimple();//无子查询，调用简单转换函数 
	return solveConnect(gnode);
	
}

GrammerNode* Query::transform2GrammerWithSubQuery(vector<Condition*>* conditionWithSub)
{
	GrammerNode* root, * ptr;
	//处理orderList与selList
	if (orderList != nullptr) {
		root = orderList->transform2Grammer();
		root->left = selList->transform2Grammer();
		ptr = root->left;
	}
	else {
		root = selList->transform2Grammer();
		ptr = root;
	}
	if (condition->lCnode) {
		GrammerNode* simCondition = condition->transform2Grammer();//获取无子查询的查询对象
		ptr->left = simCondition;
		ptr = simCondition;
	}
	
	
	//GrammerNode* simCondition = condition->transform2Grammer();//获取无子查询的查询对象
	//ptr->left = simCondition;
	//ptr = simCondition;

	GrammerNode* froms = fromList->transform2Grammer();//将fromlist转换为结点
	//处理子查询condition
	GrammerNode* connect = nullptr;
	for (Condition* subcondition : *conditionWithSub) {
		//遍历子查询condition
		GrammerNode* subQueryRoot = subcondition->query->transform2Grammer();//将子查询转换为结点
		
		connect = new GrammerNode();
		connect->type = GrammerParameter::CONNECTOR;
		connect->left = froms;
		connect->right = subQueryRoot;
		//ptr->left = connect;
		froms = connect;//下一个froms即为此次得到的connect
	}
	ptr->left = connect;

	return root;
}

GrammerNode* Query::transform2GrammerWithSimple()
{
	GrammerNode* root, * ptr;

	if (orderList != nullptr) {
		root = orderList->transform2Grammer();
		root->left = selList->transform2Grammer();
		ptr = root->left;
	}
	else {
		root = selList->transform2Grammer();
		ptr = root;
	}
	if (condition) {
		ptr->left = condition->transform2Grammer();
		ptr = ptr->left;
	}

	ptr->left = fromList->transform2Grammer();
	return root;
}

GrammerNode* Query::solveConnect(GrammerNode* root)
{	
	cout << endl << "Solve Connect" << endl;
	queue<GrammerNode*> gqueue;
	gqueue.push(root);
	GrammerNode* father = nullptr;
	while (!gqueue.empty()) {
		GrammerNode* target = gqueue.front();
		gqueue.pop();
		
		if (target->type == GrammerParameter::CONDITION) {
			int index = -1;
			int targetInfoSize = target->infos.size() - 1;
			vector<int> deleIndex;
			for (string info : target->infos) {
				index++;
				int findex = info.find('.');
				int lindex = info.rfind('.');//需要判断有两个'.'
				
				if (findex < info.length() && findex < lindex) {
					//说明为a.b = c.e类型,需要进行转换
					turnCondition2Connect(target, info);//向对应connector加入info
					deleIndex.push_back(index);
					if (index + 1 <= targetInfoSize && target->infos.at(index + 1) == "and") {
						deleIndex.push_back(index + 1);
						target->infos.at(index + 1) = "dele";//修改为待删除
					}
					else if (index + 1 > targetInfoSize && index - 1 >= 0 && target->infos.at(index - 1) == "and") {
						deleIndex.push_back(index - 1);
						target->infos.at(index - 1) = "dele";//修改为待删除
					}
				}
			}
			if (!deleIndex.empty()) {
				//说明需要进行删除
				sort(deleIndex.begin(), deleIndex.end());//从小到大进行排序
				int delecount = 0;
				vector<string>tmpInfo;
				for (int m = 0;m < target->infos.size();m++) {
					if (deleIndex.empty() || m != deleIndex.front()) {
						tmpInfo.push_back(target->infos[m]);
					}
					else {
						deleIndex.erase(deleIndex.begin());
					}
				}
				target->infos = tmpInfo;
				//删光了则把结点删除
				if (target->type == GrammerParameter::CONDITION && target->infos.empty()) {
					if (father && father->left == target) {
						father->left = target->left;
					}
					else if (father && father->right == target) {
						father->right = target->left;
					}
					delete target;
					target = father;
				}
			}
		}
		father = target;
		if (target->left)
			gqueue.push(target->left);
		if (target->right)
			gqueue.push(target->right);
	}
	cout << endl << "solve finish" << endl;
	return root;
}

void Query::turnCondition2Connect(GrammerNode* sroot, string condition)
{
	//condition 为 a.b = c.d类型
	vector<string>attr;
	Translator::getTranslator()->split(condition, attr, " ");
	string pre = attr[0];
	string bac = attr[2];

	int position = pre.find(".");
	pre = pre.substr(0,position);//a名
	position = bac.find(".");
	bac = bac.substr(0,position);//c名
	
	queue<GrammerNode*> gqueue;
	vector<GrammerNode*> conqueue;//存储所有的连接符
	gqueue.push(sroot);
	while (!gqueue.empty()) {
		GrammerNode* target = gqueue.front();
		gqueue.pop();
		if (target->left)
			gqueue.push(target->left);
		if (target->right)
			gqueue.push(target->right);

		if (target->type == GrammerParameter::CONNECTOR) {
			conqueue.push_back(target);
		}
	}
	for (GrammerNode* gnode : conqueue) {
		GrammerNode* left, *right;
		left = gnode->left;
		right = gnode->right;
		if (left->type == GrammerParameter::FROM) {
			if (left->infos[0] == pre || left->infos[0] == bac) {
				gnode->addInfo(condition);
				return;
			}
		}
		//condition右侧只能为表名
		if (right->infos[0] == pre || right->infos[0] == bac) {
			gnode->addInfo(condition);
			return;
		}
	}
}

void ParaString::showInfo()
{
	cout << "String_parameter:" <<parameter << endl;
}

void Insert::showInfo()
{
	cout << "Insert:" << endl;
	cout << "tableName:" << tableName << endl;
	cout << "attributes:" << endl;
	for (string attr : attributes) {
		cout << attr << " ";
	}
	cout << endl;
}

GrammerNode* Insert::transform2Grammer()
{
	GrammerNode* gnode = new GrammerNode();
	gnode->type = GrammerParameter::INSERT;
	gnode->addInfo(tableName);
	vector<string>::reverse_iterator riter = attributes.rbegin();//insert顺序不能改变
	for (;riter != attributes.rend();riter++) {
		gnode->addInfo(*riter);
	}
	return gnode;
}

void Delete::showInfo()
{
	cout << "Delete:" << endl;
	cout << "tableName:" << tableName << endl;
	condition->showInfo();
}

GrammerNode* Delete::transform2Grammer()
{
	//创建根结点
	GrammerNode* root = new GrammerNode();
	root->type = GrammerParameter::DELETE;
	
	//创建Condition结点
	GrammerNode* cnode = condition->transform2Grammer();
	root->left = cnode;

	//创建from结点
	GrammerNode* fnode = new GrammerNode();
	fnode->type = GrammerParameter::FROM;
	fnode->addInfo(tableName);
	cnode->left = fnode;

	return root;
}

void Update::showInfo()
{
	cout << "Update" << endl;
	cout << "tableName:" << tableName << endl;
	cout << "attr = index:" << endl;
	map<string, string>::iterator iter = attr_indexs.begin();
	for (;iter != attr_indexs.end();iter++) {
		cout << iter->first << " = " << iter->second << endl;
	}
	condition->showInfo();
	cout << endl;
}

GrammerNode* Update::transform2Grammer()
{
	//结点info格式：属性 值 属性 值...
	GrammerNode* root = new GrammerNode();
	map<string, string>::iterator iter = attr_indexs.begin();
	for (;iter != attr_indexs.end();iter++) {
		root->addInfo(iter->first);
		root->addInfo(iter->second);
	}
	root->type = GrammerParameter::UPDATE;

	GrammerNode* cnode = condition->transform2Grammer();
	root->left = cnode;

	GrammerNode* fnode = new GrammerNode();
	fnode->type = GrammerParameter::FROM;
	fnode->addInfo(tableName);
	cnode->left = fnode;
	return root;
}
