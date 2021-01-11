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
	reverse(fromList.begin(), fromList.end()); //����˳���natural join�йأ������Ҫ����ԭ�򣬼�����
	int fromNumber = fromList.size();//��ѯ�Ĺ�ϵ��
	for (Relation* relation : fromList) {
		//��ȥnatural���ʣ�µĲ�Ϊ��ϵ��
		if (relation->relationName == "@natural@") {
			fromNumber--;
		}
	}
	if (fromNumber == 1) {
		//��һ����ϵ����������
		GrammerNode* node = new GrammerNode();
		node->type = GrammerParameter::FROM;
		node->addInfo(fromList.at(0)->relationName);
		return node;
	}
	int n = 0;
	int connetNumber = fromNumber - 1;//���ӷ���Ŀ,��ȡ�������������ĿΪ��ϵ��-1
	stack<GrammerNode*> grammerStack;
	
	GrammerNode* root = new GrammerNode();//���ڵ�
	root->type = GrammerParameter::CONNECTOR;
	grammerStack.push(root);

	for (int m = 0;m < connetNumber - 1;m++) {
		GrammerNode* gnode = new GrammerNode();
		gnode->type = GrammerParameter::CONNECTOR;
		grammerStack.top()->left = gnode;//������ڵ�
		grammerStack.push(gnode);

	}

	while (!grammerStack.empty()) {
		GrammerNode* connector = grammerStack.top();
		grammerStack.pop();
		if (connector->left == nullptr) {
			//˵��Ϊ��ײ��ڵ�
			
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
		string info = orNode->attr.getAttributes() + " " + orNode->rule;//��ȡ�������->a desc
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
		//˵��Ϊb��ʽ
		attrName = name;
	}
	else {
		//˵��Ϊa.b��ʽ
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
		//���ڱ���,a.b��ʽ
		message += tableName + ".";
	}
	message += attrName;
	if (alias != "") {
		//���ڱ���
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
	
	setGrammerVec(root->infos, 1, leafCount);//��infos��д����Ϣ��д����̺��Դ��Ӳ�ѯ��condition
	reverse(root->infos.begin(),root->infos.end());//����
	return root;
}

string Condition::getInfo()
{
	string info = "";
	if (rNumber != nullptr) {
		//˵���Ҳ�����Ϊ����
		info += Lattr->getAttributes() + " " + soperator->opName + " " + rNumber->number;//a = 10
	}
	else if (pString != nullptr) {
		//˵���Ҳ�����Ϊ�ַ���
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
		//˵��ΪҶ�ڵ�
		return getInfo();
	}
	//˵������condition
	string leInfo = lCnode->getLoopInfo();//��ȡ��ڵ���Ϣ
	string reInfo = rCnode->getLoopInfo();//��ȡ�ҽڵ���Ϣ
	string info = leInfo + " " + soperator->opName + " " + reInfo;//a = b and c = e and g = h
	return info;
}

string Condition::setGrammerVec(vector<string>& infos, int count, int leafCount)
{
	if (leafCount == 0) {
		//˵��ֻ��һ���ڵ�
		if (query == nullptr) {
			//�����������Ӳ�ѯʱ����infoת��������
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
	string reInfo = rCnode->setGrammerVec(infos,-1,leafCount);//�ҽڵ�count����Ϊ-1
	if (count == leafCount) {
		//˵��ΪҶ�ӽڵ���һ��ڵ�
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
		tmpstack.pop();//ȡ���ײ�
		if (top->query != nullptr) {
			//�����Ӳ�ѯ
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
		vector<Condition*>* subQueryCondition = condition->getSubQueryCondition();//�����Ӳ�ѯ�Ľ��
		if (!subQueryCondition->empty()) {
			//condition�о����Ӳ�ѯ
			gnode = transform2GrammerWithSubQuery(subQueryCondition);//���þ����Ӳ�ѯ��ת������
			return solveConnect(gnode);
		}
	}
	gnode = transform2GrammerWithSimple();//���Ӳ�ѯ�����ü�ת������ 
	return solveConnect(gnode);
	
}

GrammerNode* Query::transform2GrammerWithSubQuery(vector<Condition*>* conditionWithSub)
{
	GrammerNode* root, * ptr;
	//����orderList��selList
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
		GrammerNode* simCondition = condition->transform2Grammer();//��ȡ���Ӳ�ѯ�Ĳ�ѯ����
		ptr->left = simCondition;
		ptr = simCondition;
	}
	
	
	//GrammerNode* simCondition = condition->transform2Grammer();//��ȡ���Ӳ�ѯ�Ĳ�ѯ����
	//ptr->left = simCondition;
	//ptr = simCondition;

	GrammerNode* froms = fromList->transform2Grammer();//��fromlistת��Ϊ���
	//�����Ӳ�ѯcondition
	GrammerNode* connect = nullptr;
	for (Condition* subcondition : *conditionWithSub) {
		//�����Ӳ�ѯcondition
		GrammerNode* subQueryRoot = subcondition->query->transform2Grammer();//���Ӳ�ѯת��Ϊ���
		
		connect = new GrammerNode();
		connect->type = GrammerParameter::CONNECTOR;
		connect->left = froms;
		connect->right = subQueryRoot;
		//ptr->left = connect;
		froms = connect;//��һ��froms��Ϊ�˴εõ���connect
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
				int lindex = info.rfind('.');//��Ҫ�ж�������'.'
				
				if (findex < info.length() && findex < lindex) {
					//˵��Ϊa.b = c.e����,��Ҫ����ת��
					turnCondition2Connect(target, info);//���Ӧconnector����info
					deleIndex.push_back(index);
					if (index + 1 <= targetInfoSize && target->infos.at(index + 1) == "and") {
						deleIndex.push_back(index + 1);
						target->infos.at(index + 1) = "dele";//�޸�Ϊ��ɾ��
					}
					else if (index + 1 > targetInfoSize && index - 1 >= 0 && target->infos.at(index - 1) == "and") {
						deleIndex.push_back(index - 1);
						target->infos.at(index - 1) = "dele";//�޸�Ϊ��ɾ��
					}
				}
			}
			if (!deleIndex.empty()) {
				//˵����Ҫ����ɾ��
				sort(deleIndex.begin(), deleIndex.end());//��С�����������
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
				//ɾ������ѽ��ɾ��
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
	//condition Ϊ a.b = c.d����
	vector<string>attr;
	Translator::getTranslator()->split(condition, attr, " ");
	string pre = attr[0];
	string bac = attr[2];

	int position = pre.find(".");
	pre = pre.substr(0,position);//a��
	position = bac.find(".");
	bac = bac.substr(0,position);//c��
	
	queue<GrammerNode*> gqueue;
	vector<GrammerNode*> conqueue;//�洢���е����ӷ�
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
		//condition�Ҳ�ֻ��Ϊ����
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
	vector<string>::reverse_iterator riter = attributes.rbegin();//insert˳���ܸı�
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
	//���������
	GrammerNode* root = new GrammerNode();
	root->type = GrammerParameter::DELETE;
	
	//����Condition���
	GrammerNode* cnode = condition->transform2Grammer();
	root->left = cnode;

	//����from���
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
	//���info��ʽ������ ֵ ���� ֵ...
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
