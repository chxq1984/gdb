#include "SqlGrammer.h"

map<int, string> GrammerParameter::typeMap;

void GrammerNode::addInfo(string st)
{
	infos.push_back(st);
}

void GrammerNode::showInfo()
{
	cout << "type:" << GrammerParameter::getType(type) << endl;
	for (string s : infos) {
		cout << s << endl;
	}
	cout << endl;
}

PhyPlanNode* GrammerNode::transform2PlanNode(GrammerNode* father)
{
	switch (type)
	{
	case GrammerParameter::FROM:
		return transFmFrom(father);
	case GrammerParameter::CONDITION:
		return transFmCondition();
	case GrammerParameter::CONNECTOR:
		return transFmConnector();
	case GrammerParameter::ORDERLIST:
		return transFmOrder();
	case GrammerParameter::PROJECT:
		return transFmProject();
	case GrammerParameter::INSERT:
		return transFmInsert();
	case GrammerParameter::DELETE:
		return transFmDelete();
	case GrammerParameter::UPDATE:
		return transFmUpdate();
	default:
		return NULL;
	}
}

PhyPlanNode* GrammerNode::transFmFrom(GrammerNode* father)
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	bool useIndex = false;//�ж��Ƿ�ʹ����������
	string tableName = infos.at(0);//��ȡ����
	if (father != nullptr) {
		//˵�������Ϊcondition�ڵ�
		for (int m = 0;m < father->infos.size();m+=2) {
			//a.b = 20 a = 20
			string info = father->infos.at(m);//����ָ��
			vector<string> tmsp;
			Translator::getTranslator()->split(info, tmsp, ' ');
			string pre = tmsp.at(0);//��������
			int dotposition = pre.find('.');//�ж��Ƿ����.
			if (dotposition < pre.length()) {
				//˵��Ϊa.b��ʽ
				pre = pre.substr(dotposition+1);
			}
			if (SqlGlobal::getInstance()->hasIndex(tableName, pre)) {
				//��������
				useIndex = true;//��һ��ʹ��������ֱ���˳�
				break;
			}
		}
	}
	if (useIndex)
		ppnode->methodName = "INDEXSCAN";//��������
	else
		ppnode->methodName = "SEQSCAN";//˳�����
	ppnode->addParameter(infos.at(0));

	return ppnode;
}

PhyPlanNode* GrammerNode::transFmCondition()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	ppnode->methodName = "FILTER";//�˴��ݲ�����IndexScan�������ǿ����ӽڵ�
	for (string condition : infos) {
		//ÿһ��conditionΪһ������:a=b��������and���ӷ�
		ppnode->addParameter(condition);
	}
	return ppnode;
}

PhyPlanNode* GrammerNode::transFmOrder()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	ppnode->methodName = "SORT";//�����Խ�����ʽ����
	for (string rule : infos) {
		//rule��a desc
		vector<string> ord;
		Translator::getTranslator()->split(rule, ord, ' ');
		ppnode->addParameter(ord.at(0));
		ppnode->addParameter(ord.at(1));
	}
	return ppnode;
	
}

PhyPlanNode* GrammerNode::transFmProject()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	ppnode->methodName = "SELECT";
	for (string attr : infos) {
		//attrΪÿһ������
		ppnode->addParameter(attr);
	}
	return ppnode;
}

PhyPlanNode* GrammerNode::transFmConnector()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	GrammerNode* lrelation = left;//���ϵ��
	GrammerNode* rrelation = right;//�ҹ�ϵ��
	for (string info : infos) {
		ppnode->addAddition(info);
	}
	ppnode->methodName = "JOIN";//�˴�Ĭ��ѡ��һ��ɢ������
	if(lrelation->type == GrammerParameter::FROM)//��Ϊ���ӷ������������
		ppnode->addParameter(lrelation->infos.at(0));//����1�������
	if (rrelation->type == GrammerParameter::FROM)
		ppnode->addParameter(rrelation->infos.at(0));//����2���ұ���

	//int cacheNum = 50;//Ӧ�����ұ�������軺������С���˴�Ĭ��ѡΪ50
	//ppnode->addParameter(to_string(cacheNum));//����3�����������С
	return ppnode;
}

PhyPlanNode* GrammerNode::transFmDelete()
{
	PhyPlanNode* pnode = new PhyPlanNode();
	pnode->methodName = "DELETE";
	return pnode;
}

PhyPlanNode* GrammerNode::transFmInsert()
{
	PhyPlanNode* pnode = new PhyPlanNode();
	pnode->methodName = "INSERT";
	for (string info : infos) {
		pnode->addParameter(info);
	}
	return pnode;
}

PhyPlanNode* GrammerNode::transFmUpdate()
{
	PhyPlanNode* pnode = new PhyPlanNode();
	pnode->methodName = "UPDATE";
	for (string attr_index : infos) {
		pnode->addParameter(attr_index);
	}
	return pnode;
}

void SqlGrammer::bacLoopTree(GrammerNode* node)
{
	cout << endl;
	if (node->left == NULL && node->right == NULL) {
		node->showInfo();
		return;
	}
	if (node->left != NULL) {
		bacLoopTree(node->left);
	}
	if (node->right != NULL) {
		bacLoopTree(node->right);
	}
	node->showInfo();
}

void SqlGrammer::showInfo()
{
	bacLoopTree(root);
}

PhyPlanNode* SqlGrammer::transform2PhysicPlan()
{
	return copyFromGrammer(root);
}

void SqlGrammer::optimiza()
{
	optimizeConnect();//�Ż�connect
	optimizeSelect();//�Ż�select
	cout << endl << "�Ż����:" << endl;
	showInfo();
}

PhyPlanNode* SqlGrammer::copyFromGrammer(GrammerNode* gnode)
{
	if (gnode == nullptr)
		return nullptr;
	GrammerNode* father = nullptr;
	if (gnode->type == GrammerParameter::FROM) {
		father = findFatherNode(gnode, root);//���˽ڵ�ΪFROM�ڵ����ȡ�丸�ڵ�
		if (father && father->type != GrammerParameter::CONDITION)
			father = nullptr;//���ڵ���ҪΪcondition�ڵ�
	}
	PhyPlanNode* newppnode = gnode->transform2PlanNode(father);//���ʽ�ڵ�ת��Ϊ����ƻ��ڵ�
	newppnode->left = copyFromGrammer(gnode->left);
	newppnode->right = copyFromGrammer(gnode->right);
	return newppnode;
}

void SqlGrammer::optimizeSelect()
{
	cout <<endl<< "��ѯ�Ż�----ѡ�����" << endl;
	queue<GrammerNode*> nodeQueue;
	nodeQueue.push(root);
	while (!nodeQueue.empty()) {
		//��α���
		GrammerNode* target = nodeQueue.front();
		nodeQueue.pop();
		//����target
		if (target->type == GrammerParameter::CONDITION) {
			//Ϊ��ѯ�������
			vector<string>*effectedTables = findTablesByAttr(target);//��ȡcondition�����õı���
			
			if (effectedTables->size() == 1) {
				//˵����һ�ű��������Ż�
				continue;
			}
			int size = target->infos.size();//��ȡ����������С
			bool hasOr = false;
			bool hasAnd = false;
			for (string con : target->infos) {
				if (con == "or" || con == "OR") {
					//������or�򲻽��д���
					hasOr = true;
				}
				else if (con == "and" || con == "AND") {
					hasAnd = true;
				}
			}
			if (hasOr || !hasAnd) {
				//����or�򲻽��д���
				if(hasOr || target->infos.empty())
					continue;
				else {
					//˵��û��and���ڴ˽��н�һ���ж�
					vector<string> cons;
					string condition = target->infos.at(0);//����һ�����
					Translator::getTranslator()->split(condition, cons, ' ');
					//pre opt bac => a = 'c'
					string pre = cons[0];
					string opt = cons[1];
					string bac = cons[2];
					if (bac[0] == '\'' || bac[0] >= '0' && bac[0] <= '9') {
						cons.clear();
						string sourceTable = "";
						if (pre.find('.') < pre.size()) {
							//Ϊa.b��ʽ
							Translator::getTranslator()->split(pre, cons, '.');
							sourceTable = cons[0];//��ȡ����
						}
						else {
							//δ��ʽ˵������Ҫ���Ҷ�Ӧ��
							sourceTable = findAttrSource(pre, *effectedTables);
						}
						if (sourceTable == "")
							continue;//˵��ƥ������1�Ż�Ϊ0��
						else {
							//�����Ż�
							GrammerNode* srcNode = findNodeByInfo(sourceTable, target);//�ҵ�������Ӧ�Ľ��
							GrammerNode* targetFather = findFatherNode(srcNode, target);//�ҵ�sourceTable��Ӧ�ĸ����
							if (targetFather->type == GrammerParameter::CONDITION) {
								//�Ѿ�Ϊcondition����Ҫ�ٴ����ڵ�
								targetFather->addInfo(condition);
							}
							else {
								GrammerNode* newNode = new GrammerNode();
								newNode->addInfo(condition);//�����½��
								newNode->type = GrammerParameter::CONDITION;
								newNode->left = srcNode;
								if (targetFather->left == srcNode)
									targetFather->left = newNode;
								else if (targetFather->right == srcNode)
									targetFather->right = newNode;
							}
							
							//�˽���ȡ��
							targetFather = findFatherNode(target, root);
							if (targetFather->left == target) {
								targetFather->left = target->left;
							}
							else if (targetFather->right == target)
								targetFather->right == target;
							nodeQueue.push(targetFather->left);//Ϊ����������׼��
							delete target;
							target = nullptr;
						}
					}
					else {
						continue;
					}
				}
			}
			else {
				//������or���Ҵ���and����д���
				int conditionLen = (size + 1) / 2;//��ȥand��condition��
				vector<string>::iterator itr = target->infos.begin();
				for (int m = 1;m <= (size-1)/2;m++) {
					target->infos.erase(itr + m);
				}//��ʱ���and
				int eraseNum = 0;//��¼�Ƴ�condition����Ŀ
				for (int m = 0;m < conditionLen;m++) {
					int index = m;
					string condition = target->infos[index-eraseNum];
					vector<string> cons;
					Translator::getTranslator()->split(condition, cons, ' ');
					//pre opt bac => a = 'c'
					string pre = cons[0];
					string opt = cons[1];
					string bac = cons[2];
					if (bac[0] == '\'' || bac[0] >= '0' && bac[0] <= '9') {
						//˵��Ϊ�ַ�����Ϊ����,��ɷ���
						cons.clear();
						string sourceTable = "";
						if (pre.find('.')<pre.size()) {
							//Ϊa.b��ʽ
							Translator::getTranslator()->split(pre, cons, '.');
							sourceTable = cons[0];//��ȡ����
						}
						else {
							//δ��ʽ˵������Ҫ���Ҷ�Ӧ��
							sourceTable = findAttrSource(pre, *effectedTables);
						}
						if (sourceTable == "")
							continue;//˵��ƥ������1�Ż�Ϊ0��
						else {
							//�����Ż�
							GrammerNode* srcNode = findNodeByInfo(sourceTable, target);//�ҵ�������Ӧ�Ľ��
							GrammerNode* targetFather = findFatherNode(srcNode, target);//�ҵ�sourceTable��Ӧ�ĸ����
							if (targetFather->type == GrammerParameter::CONDITION) {
								//��Ϊ����������贴���½ڵ�
								targetFather->addInfo("and");
								targetFather->addInfo(condition);
							}
							else {
								GrammerNode* newNode = new GrammerNode();
								newNode->addInfo(condition);//�����½��
								newNode->type = GrammerParameter::CONDITION;
								newNode->left = srcNode;
								if (targetFather->left == srcNode)
									targetFather->left = newNode;
								else if (targetFather->right == srcNode)
									targetFather->right = newNode;
							}
							target->infos.erase(target->infos.begin() + index-eraseNum);//�Ƴ�condition
							eraseNum++;//�Ƴ�������
						}
					}
				}
				if (target->infos.empty()) {
					//��Ϊ����˽���ȡ��
					GrammerNode* targetFather = findFatherNode(target, root);
					if (targetFather->left == target) {
						targetFather->left = target->left;
					}
					else if (targetFather->right == target)
						targetFather->right == target;
					nodeQueue.push(targetFather->left);//Ϊ����������׼��
					delete target;
					target = nullptr;
				}
				else {
					//���ݴ�С����and
					int remainSize = target->infos.size();
					int insertNum = remainSize - 1;
					for (int m = 1;m <= insertNum;m++) {
						int inum = m * 2 - 1;
						target->infos.insert(target->infos.begin() + inum, "and");
					}
				}
			}
		}
		if (target == nullptr) {
			continue;
		}
		if (target->left)
			nodeQueue.push(target->left);
		if (target->right)
			nodeQueue.push(target->right);
	}
}

void SqlGrammer::optimizeConnect()
{
	GrammerNode* conRoot = findConnect();//��ȡ��һ��connect���
	if (conRoot == nullptr)
		return;
	if (!isAllNatural(conRoot))//����ȫΪ��Ȼ����ʱ�����Ż�
		return;
	vector<ConnectorNode*> cnodes;
	findConnectTable(conRoot, cnodes);//������ӽ������,��cnodes
	ConnectorOptimizer conOpt(cnodes);//�����Ż���
	conOpt.optimizer();//ִ���Ż�
	vector<ConnectorNode*>* best = conOpt.best;
	queue<string>tableName;
	for (ConnectorNode* cnode : *best) {
		tableName.push(cnode->tableName);
		cout << cnode->tableName << " ";
	}
	updateConnectOrder(conRoot, tableName);//��������˳��
}

void SqlGrammer::updateConnectOrder(GrammerNode* croot, queue<string>& order)
{
	//���ú��������˳�����˳��
	if (croot == nullptr)
		return;
	updateConnectOrder(croot->left, order);
	updateConnectOrder(croot->right, order);
	if (croot->type == GrammerParameter::FROM) {
		croot->infos[0] = order.front();
		order.pop();
	}
}

int SqlGrammer::isAllNatural(GrammerNode* croot)
{
	
	stack<GrammerNode*> cstack;
	cstack.push(croot);
	while (croot->left && croot->left->type == GrammerParameter::CONNECTOR) {
		cstack.push(croot->left);
		croot = croot->left;
	}
	int isAllNatural = 1;
	while (!cstack.empty()) {
		if (cstack.top()->infos.empty()) {
			isAllNatural = 0;
			break;
		}else if (cstack.top()->infos[0] != "@natural@") {
			isAllNatural = 0;
			break;
		}
		cstack.pop();
	}
	
	return isAllNatural;
}

vector<string>* SqlGrammer::findTablesByAttr(GrammerNode* condition)
{
	while (condition->left && condition->left->type == GrammerParameter::CONDITION) {
		condition = condition->left;
	}
	vector<string>* tableNames = new vector<string>;
	if (condition->left == nullptr)
		return nullptr;
	if (condition->left->type == GrammerParameter::FROM) {
		tableNames->push_back(condition->left->infos[0]);//˵���ޱ����ӣ���ֱ�ӷ��ر���
		return tableNames;
	}
	else if (condition->left->type == GrammerParameter::CONNECTOR) {
		//˵��Ϊ�����ӣ������������ű�
		queue<GrammerNode*> tmpQueue;
		tmpQueue.push(condition->left);
		//��conditionΪ�������в�α���
		while (!tmpQueue.empty()) {
			GrammerNode* tar = tmpQueue.front();
			if (tar->type == GrammerParameter::FROM) {
				tableNames->push_back(tar->infos[0]);//��Ϊfrom��ȡ������
			}
			tmpQueue.pop();
			if (tar->left) {
				tmpQueue.push(tar->left);
			}
			if (tar->right) {
				tmpQueue.push(tar->right);
			}
		}
		return tableNames;
	}
	return nullptr;

}

//vector<string>* SqlGrammer::findConnectTables(GrammerNode* conRoot)
//{
//	vector<string>* tables = new vector<string>;
//	queue<GrammerNode*> gnodes;
//	gnodes.push(conRoot);
//	while (!gnodes.empty()) {
//		GrammerNode* target = gnodes.front();
//		gnodes.pop();
//		if (target->type == GrammerParameter::FROM)
//			tables->push_back(target->infos[0]);
//
//		if (target->left)
//			gnodes.push(target->left);
//		if (target->right)
//			gnodes.push(target->right);
//	}
//	return tables;
//}

void SqlGrammer::findConnectTable(GrammerNode* conRoot, vector<ConnectorNode*>& cnodes)
{
	GrammerNode* target = conRoot;
	stack<GrammerNode*> gstack;
	gstack.push(target);
	while (target->left && target->left->type == GrammerParameter::CONNECTOR) {
		gstack.push(target->left);
		target = target->left;
	}
	target = gstack.top();//���һ��connector
	gstack.pop();
	GrammerNode* lenode = target->left;//����
	ConnectorNode* lcnode = createConnectNode(lenode);

	GrammerNode* rinode = target->right;//�ҽ�� 
	ConnectorNode* rcnode = createConnectNode(rinode);
	cnodes.push_back(lcnode);
	cnodes.push_back(rcnode);

	//��Ҷ��connecor�������ӽ��
	while (!gstack.empty()) {
		target = gstack.top();
		gstack.pop();
		rinode = target->right;
		cnodes.push_back(createConnectNode(rinode));
	}
}

ConnectorNode* SqlGrammer::createConnectNode(GrammerNode* target)
{
	ConnectorNode* cnode = new ConnectorNode();
	cnode->T = SqlGlobal::getInstance()->getT(target->infos[0]);//��ȡTֵ
	cnode->tableName = target->infos[0];
	vector<string> attrs = SqlGlobal::getInstance()->getAttribute(cnode->tableName);//��ȡ�����������
	for (string attribute : attrs) {
		//����
		int v = SqlGlobal::getInstance()->getV(cnode->tableName, attribute);//��������Զ�Ӧ��vֵ
		cnode->Vs[attribute] = v;
	}
	return cnode;
}



GrammerNode* SqlGrammer::findFatherNode(GrammerNode* child, GrammerNode* head)
{
	queue<GrammerNode*> gnodes;
	gnodes.push(head);
	while (!gnodes.empty()) {
		GrammerNode* target = gnodes.front();
		gnodes.pop();
		if (target->left == child || target->right == child) {
			return target;
		}
		if (target->left)
			gnodes.push(target->left);
		if (target->right)
			gnodes.push(target->right);
	}
	return nullptr;
}

GrammerNode* SqlGrammer::findFatherNode(string childInfo, GrammerNode* head)
{
	queue<GrammerNode*> gnodes;
	gnodes.push(head);
	while (!gnodes.empty()) {
		GrammerNode* target = gnodes.front();
		gnodes.pop();
		if (target->left && target->left->type == GrammerParameter::FROM && target->left->infos[0] == childInfo || \
			target->right && target->right->type == GrammerParameter::FROM && target->right->infos[0] == childInfo) {
			return target;
		}
		if (target->left)
			gnodes.push(target->left);
		if (target->right)
			gnodes.push(target->right);
	}
	return nullptr;
}

GrammerNode* SqlGrammer::findNodeByInfo(string info, GrammerNode* head)
{
	queue<GrammerNode*> gnodes;
	gnodes.push(head);
	while (!gnodes.empty()) {
		GrammerNode* target = gnodes.front();
		gnodes.pop();
		if (target->type == GrammerParameter::FROM && target->infos[0] == info) {
			return target;
		}
		if (target->left)
			gnodes.push(target->left);
		if (target->right)
			gnodes.push(target->right);
	}
	return nullptr;
}

GrammerNode* SqlGrammer::findConnect()
{
	queue<GrammerNode*> gqueue;
	gqueue.push(root);
	while (!gqueue.empty()) {
		GrammerNode* target = gqueue.front();
		gqueue.pop();
		if (target->type == GrammerParameter::CONNECTOR)
			return target;
		if (target->left)
			gqueue.push(target->left);
		if (target->right)
			gqueue.push(target->right);
	}
	return nullptr;
}

string SqlGrammer::findAttrSource(string attrName, vector<string>& tableNames)
{
	int blongNum = 0;//���ڵı���
	string blongTableName;
	for (string tableName : tableNames) {
		//��tableName�����attrName���ԣ���blongNum+1
		vector<string>tableAttr = SqlGlobal::getInstance()->getAttribute(tableName);//��ȡ��ӵ�е�����
		for (string attr : tableAttr) {
			//attrΪ���ھ��е�����
			if (attr == attrName) {
				blongNum += 1;
				blongTableName = tableName;
				break;
			}
		}
	}
	if (blongNum == 1) {
		return blongTableName;
	}
	return "";
}

void GrammerParameter::initMap()
{
	typeMap[1] = "from";
	typeMap[2] = "connector";
	typeMap[3] = "condition";
	typeMap[4] = "project";
	typeMap[5] = "deduplicate";
	typeMap[6] = "orderlist";
	typeMap[7] = "insert";
	typeMap[8] = "update";
	typeMap[9] = "delete";
}

string GrammerParameter::getType(int type)
{
	typeMap.clear();
	initMap();
	return typeMap.find(type)->second;
}
