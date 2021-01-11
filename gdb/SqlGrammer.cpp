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
	bool useIndex = false;//判断是否使用索引遍历
	string tableName = infos.at(0);//获取表名
	if (father != nullptr) {
		//说明父结点为condition节点
		for (int m = 0;m < father->infos.size();m+=2) {
			//a.b = 20 a = 20
			string info = father->infos.at(m);//单条指令
			vector<string> tmsp;
			Translator::getTranslator()->split(info, tmsp, ' ');
			string pre = tmsp.at(0);//即属性名
			int dotposition = pre.find('.');//判断是否存在.
			if (dotposition < pre.length()) {
				//说明为a.b形式
				pre = pre.substr(dotposition+1);
			}
			if (SqlGlobal::getInstance()->hasIndex(tableName, pre)) {
				//存在索引
				useIndex = true;//有一个使用索引则直接退出
				break;
			}
		}
	}
	if (useIndex)
		ppnode->methodName = "INDEXSCAN";//索引遍历
	else
		ppnode->methodName = "SEQSCAN";//顺序遍历
	ppnode->addParameter(infos.at(0));

	return ppnode;
}

PhyPlanNode* GrammerNode::transFmCondition()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	ppnode->methodName = "FILTER";//此处暂不考虑IndexScan，若考虑可增加节点
	for (string condition : infos) {
		//每一个condition为一个类似:a=b的条件或and连接符
		ppnode->addParameter(condition);
	}
	return ppnode;
}

PhyPlanNode* GrammerNode::transFmOrder()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	ppnode->methodName = "SORT";//对属性进行显式排序
	for (string rule : infos) {
		//rule：a desc
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
		//attr为每一个属性
		ppnode->addParameter(attr);
	}
	return ppnode;
}

PhyPlanNode* GrammerNode::transFmConnector()
{
	PhyPlanNode* ppnode = new PhyPlanNode();
	GrammerNode* lrelation = left;//左关系表
	GrammerNode* rrelation = right;//右关系表
	for (string info : infos) {
		ppnode->addAddition(info);
	}
	ppnode->methodName = "JOIN";//此处默认选择一趟散列连接
	if(lrelation->type == GrammerParameter::FROM)//若为连接符则左参数忽略
		ppnode->addParameter(lrelation->infos.at(0));//参数1：左表名
	if (rrelation->type == GrammerParameter::FROM)
		ppnode->addParameter(rrelation->infos.at(0));//参数2：右表名

	//int cacheNum = 50;//应由左右表计算所需缓冲区大小，此处默认选为50
	//ppnode->addParameter(to_string(cacheNum));//参数3：缓冲区块大小
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
	optimizeConnect();//优化connect
	optimizeSelect();//优化select
	cout << endl << "优化完毕:" << endl;
	showInfo();
}

PhyPlanNode* SqlGrammer::copyFromGrammer(GrammerNode* gnode)
{
	if (gnode == nullptr)
		return nullptr;
	GrammerNode* father = nullptr;
	if (gnode->type == GrammerParameter::FROM) {
		father = findFatherNode(gnode, root);//若此节点为FROM节点则获取其父节点
		if (father && father->type != GrammerParameter::CONDITION)
			father = nullptr;//父节点需要为condition节点
	}
	PhyPlanNode* newppnode = gnode->transform2PlanNode(father);//表达式节点转换为物理计划节点
	newppnode->left = copyFromGrammer(gnode->left);
	newppnode->right = copyFromGrammer(gnode->right);
	return newppnode;
}

void SqlGrammer::optimizeSelect()
{
	cout <<endl<< "查询优化----选择后移" << endl;
	queue<GrammerNode*> nodeQueue;
	nodeQueue.push(root);
	while (!nodeQueue.empty()) {
		//层次遍历
		GrammerNode* target = nodeQueue.front();
		nodeQueue.pop();
		//处理target
		if (target->type == GrammerParameter::CONDITION) {
			//为查询条件结点
			vector<string>*effectedTables = findTablesByAttr(target);//获取condition所作用的表名
			
			if (effectedTables->size() == 1) {
				//说明仅一张表，则无需优化
				continue;
			}
			int size = target->infos.size();//获取条件容器大小
			bool hasOr = false;
			bool hasAnd = false;
			for (string con : target->infos) {
				if (con == "or" || con == "OR") {
					//若存在or则不进行处理
					hasOr = true;
				}
				else if (con == "and" || con == "AND") {
					hasAnd = true;
				}
			}
			if (hasOr || !hasAnd) {
				//存在or则不进行处理
				if(hasOr || target->infos.empty())
					continue;
				else {
					//说明没有and则在此进行进一步判断
					vector<string> cons;
					string condition = target->infos.at(0);//仅有一个语句
					Translator::getTranslator()->split(condition, cons, ' ');
					//pre opt bac => a = 'c'
					string pre = cons[0];
					string opt = cons[1];
					string bac = cons[2];
					if (bac[0] == '\'' || bac[0] >= '0' && bac[0] <= '9') {
						cons.clear();
						string sourceTable = "";
						if (pre.find('.') < pre.size()) {
							//为a.b格式
							Translator::getTranslator()->split(pre, cons, '.');
							sourceTable = cons[0];//获取表名
						}
						else {
							//未显式说明则需要查找对应表
							sourceTable = findAttrSource(pre, *effectedTables);
						}
						if (sourceTable == "")
							continue;//说明匹配表多于1张或为0张
						else {
							//进行优化
							GrammerNode* srcNode = findNodeByInfo(sourceTable, target);//找到表名对应的结点
							GrammerNode* targetFather = findFatherNode(srcNode, target);//找到sourceTable对应的父结点
							if (targetFather->type == GrammerParameter::CONDITION) {
								//已经为condition则不需要再创建节点
								targetFather->addInfo(condition);
							}
							else {
								GrammerNode* newNode = new GrammerNode();
								newNode->addInfo(condition);//插入新结点
								newNode->type = GrammerParameter::CONDITION;
								newNode->left = srcNode;
								if (targetFather->left == srcNode)
									targetFather->left = newNode;
								else if (targetFather->right == srcNode)
									targetFather->right = newNode;
							}
							
							//此结点可取消
							targetFather = findFatherNode(target, root);
							if (targetFather->left == target) {
								targetFather->left = target->left;
							}
							else if (targetFather->right == target)
								targetFather->right == target;
							nodeQueue.push(targetFather->left);//为后续遍历做准备
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
				//不存在or并且存在and则进行处理
				int conditionLen = (size + 1) / 2;//除去and的condition数
				vector<string>::iterator itr = target->infos.begin();
				for (int m = 1;m <= (size-1)/2;m++) {
					target->infos.erase(itr + m);
				}//暂时清除and
				int eraseNum = 0;//记录移出condition的数目
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
						//说明为字符串或为数字,则可分离
						cons.clear();
						string sourceTable = "";
						if (pre.find('.')<pre.size()) {
							//为a.b格式
							Translator::getTranslator()->split(pre, cons, '.');
							sourceTable = cons[0];//获取表名
						}
						else {
							//未显式说明则需要查找对应表
							sourceTable = findAttrSource(pre, *effectedTables);
						}
						if (sourceTable == "")
							continue;//说明匹配表多于1张或为0张
						else {
							//进行优化
							GrammerNode* srcNode = findNodeByInfo(sourceTable, target);//找到表名对应的结点
							GrammerNode* targetFather = findFatherNode(srcNode, target);//找到sourceTable对应的父结点
							if (targetFather->type == GrammerParameter::CONDITION) {
								//已为父结点则无需创建新节点
								targetFather->addInfo("and");
								targetFather->addInfo(condition);
							}
							else {
								GrammerNode* newNode = new GrammerNode();
								newNode->addInfo(condition);//插入新结点
								newNode->type = GrammerParameter::CONDITION;
								newNode->left = srcNode;
								if (targetFather->left == srcNode)
									targetFather->left = newNode;
								else if (targetFather->right == srcNode)
									targetFather->right = newNode;
							}
							target->infos.erase(target->infos.begin() + index-eraseNum);//移出condition
							eraseNum++;//移出数增加
						}
					}
				}
				if (target->infos.empty()) {
					//若为空则此结点可取消
					GrammerNode* targetFather = findFatherNode(target, root);
					if (targetFather->left == target) {
						targetFather->left = target->left;
					}
					else if (targetFather->right == target)
						targetFather->right == target;
					nodeQueue.push(targetFather->left);//为后续遍历做准备
					delete target;
					target = nullptr;
				}
				else {
					//根据大小插入and
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
	GrammerNode* conRoot = findConnect();//获取第一个connect结点
	if (conRoot == nullptr)
		return;
	if (!isAllNatural(conRoot))//仅当全为自然连接时进行优化
		return;
	vector<ConnectorNode*> cnodes;
	findConnectTable(conRoot, cnodes);//填充连接结点向量,即cnodes
	ConnectorOptimizer conOpt(cnodes);//连接优化器
	conOpt.optimizer();//执行优化
	vector<ConnectorNode*>* best = conOpt.best;
	queue<string>tableName;
	for (ConnectorNode* cnode : *best) {
		tableName.push(cnode->tableName);
		cout << cnode->tableName << " ";
	}
	updateConnectOrder(conRoot, tableName);//更新连接顺序
}

void SqlGrammer::updateConnectOrder(GrammerNode* croot, queue<string>& order)
{
	//采用后根遍历的顺序更新顺序
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
		tableNames->push_back(condition->left->infos[0]);//说明无表连接，则直接返回表名
		return tableNames;
	}
	else if (condition->left->type == GrammerParameter::CONNECTOR) {
		//说明为表连接，则至少有两张表
		queue<GrammerNode*> tmpQueue;
		tmpQueue.push(condition->left);
		//以condition为根结点进行层次遍历
		while (!tmpQueue.empty()) {
			GrammerNode* tar = tmpQueue.front();
			if (tar->type == GrammerParameter::FROM) {
				tableNames->push_back(tar->infos[0]);//若为from则取得名字
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
	target = gstack.top();//最后一个connector
	gstack.pop();
	GrammerNode* lenode = target->left;//左结点
	ConnectorNode* lcnode = createConnectNode(lenode);

	GrammerNode* rinode = target->right;//右结点 
	ConnectorNode* rcnode = createConnectNode(rinode);
	cnodes.push_back(lcnode);
	cnodes.push_back(rcnode);

	//非叶子connecor仅有右子结点
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
	cnode->T = SqlGlobal::getInstance()->getT(target->infos[0]);//获取T值
	cnode->tableName = target->infos[0];
	vector<string> attrs = SqlGlobal::getInstance()->getAttribute(cnode->tableName);//获取表的所有属性
	for (string attribute : attrs) {
		//遍历
		int v = SqlGlobal::getInstance()->getV(cnode->tableName, attribute);//计算此属性对应的v值
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
	int blongNum = 0;//属于的表数
	string blongTableName;
	for (string tableName : tableNames) {
		//若tableName表存在attrName属性，则blongNum+1
		vector<string>tableAttr = SqlGlobal::getInstance()->getAttribute(tableName);//获取表拥有的属性
		for (string attr : tableAttr) {
			//attr为表内具有的属性
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
