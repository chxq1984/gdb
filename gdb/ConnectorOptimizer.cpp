#include "ConnectorOptimizer.h"

void ConnectorNode::showInfo()
{
	cout << endl;
	cout << tableName << endl;
	cout << "T:" << T << endl;
	map<string, int>::iterator iter;
	for (iter = Vs.begin(); iter != Vs.end(); iter++) {
		cout << iter->first << " " << iter->second << endl;
	}

}

ConnectorOptimizer::ConnectorOptimizer(vector<ConnectorNode*>& cnodes)
{
	this->cnodes = &cnodes;
}

void ConnectorOptimizer::optimizer()
{
	//计算种群大小
	int geqo_effort = 5;
	int geqo_pool_size = getPoolSize(geqo_effort);//种群大小

	vector<vector<int>> rans = getRandomIndividual(geqo_pool_size);
	vector<Individual*> individuals;
	int indiNum = rans.size();//生成的个体数
	//创建个体
	for (int m = 0;m < indiNum;m++) {
		vector<ConnectorNode*>tmpcnodes;
		for (int n = 0;n < cnodes->size();n++) {
			tmpcnodes.push_back(cnodes->at(rans[m][n]));
		}
		Individual* indi = new Individual(tmpcnodes,rans[m]);
		individuals.push_back(indi);
	}
	std::sort(std::begin(individuals), std::end(individuals),
		[](const Individual* p1, const Individual* p2) {return p1->cost < p2->cost;});//按cost进行升序排序
	int time = geqo_pool_size;//演化代数等于种群大小
	for (int m = 0;m < time;m++) {
		/*cout << endl << "迭代数：" << m;
		cout << " 最优代价：" << individuals.front()->cost << endl;*/
		rans.clear();
		for (int m = 0;m < individuals.size();m++) {
			rans.push_back(individuals.at(m)->order);
		}//重新得到排序
		int chooseIndex1 = getChoosenIndex(individuals.size());
		int chooseIndex2 = getChoosenIndex(individuals.size());
		if (chooseIndex2 == chooseIndex1) {
			//若二者重复则取前一个值
			chooseIndex2 = chooseIndex1 == 0 ? 1 : chooseIndex1 - 1;
		}
		/*cout << chooseIndex2 << " " << individuals.size() << endl;*/
		vector<int> tmp = rans.at(chooseIndex2);
		getChild(rans.at(chooseIndex1), tmp);//生成后代，tmp内存放后代
		variation(tmp);//变异
		//利用tmp产生个体
		vector<ConnectorNode*>tmpcnodes;
		for (int n = 0;n < cnodes->size();n++) {
			tmpcnodes.push_back(cnodes->at(tmp[n]));
		}
		Individual* indi = new Individual(tmpcnodes, tmp);
		individuals.push_back(indi);
		std::sort(std::begin(individuals), std::end(individuals),
			[](const Individual* p1, const Individual* p2) {return p1->cost < p2->cost;});//按cost进行升序排序
		individuals.pop_back();//去掉代价最高的个体

	}
	//遗传算法结束迭代，取第一个
	best = &individuals.front()->cnodeNames;
	cout << "遗传算法结束，最优代价：" << individuals.front()->cost << endl;
	
}

vector<vector<int>> ConnectorOptimizer::getRandomIndividual(int n)
{
	srand(unsigned(time(NULL)));
	vector<vector<int>> rans;
	vector<int> old;
	for (int m = 0;m < cnodes->size();m++)
		old.push_back(m);
	for (int m = 0;m < n;m++) {
		vector<int> newArray;
		RandomArray(old, newArray);
		rans.push_back(newArray);
	}
	return rans;
}

void ConnectorOptimizer::RandomArray(vector<int> oldArray, vector<int>& newArray)
{
	// 随机打乱
	int len = oldArray.size();
	for (int i = len; i > 0; i--) {
		
		// 选中的随机下标
		int index = rand() % i;
		// 根据选中的下标将原数组选中的元素push到新数组
		newArray.push_back(oldArray[index]);
		// 将原数组中选中的元素剔除
		oldArray.erase(oldArray.begin() + index);
	}
}

int ConnectorOptimizer::getChoosenIndex(int individualNum)
{
	int max = individualNum;
	double bias = 2.0;
	double geo_rand;
	//srand(time(NULL));
	geo_rand = (rand() % 100) * 0.01;//范围在0~1
	//cout << geo_rand << " ";
	double A = bias * bias - 4 * (bias - 1) * geo_rand;
	if (A < 0) {
		double result = max * (bias - A) / (2 * (bias - 1));
		return result;
	}
	else {
		double result = max * (bias - sqrt(A)) / (2 * (bias - 1));
		return result;
	}
}

void ConnectorOptimizer::getChild(vector<int>& fa1, vector<int>& fa2)
{
	//采取基于位置的杂交
	int geneSize = cnodes->size();//基因大小
	int pre = geneSize / 3;
	int bac = geneSize * 2 / 3;
	int p = round((double)rand() / RAND_MAX * (bac - pre) + pre);//从父体1中选择基因的个数
	vector<int> tmp1 = fa1;
	int* tmp2 = new int[fa2.size()];
	set<int> input;
	for (int m = 0;m < fa2.size();m++)
		tmp2[m] = -1;//初始化为-1
	random_shuffle(tmp1.begin(), tmp1.end());//随机打乱tmp1
	for (int m = 0;m < p;m++) {
		int gene = tmp1.at(m);
		int index;
		//获取具体位置
		for (index = 0;index < fa1.size();index++) {
			if (fa1.at(index) == gene)
				break;
		}
		input.insert(gene);//将值放入
		tmp2[index] = gene;
	}

	int index = 0;
	for (int m = 0;m < tmp1.size();m++) {
		if (!input.count(fa2.at(m))) {
			//说明不存在，则可插入
			for (;index < tmp1.size();index++) {
				if (tmp2[index] == -1)
					break;
			}
			tmp2[index++] = fa2.at(m);
			if (index == tmp1.size())
				break;
		}
	}
	fa2.clear();
	for (int m = 0;m < fa1.size();m++) {
		fa2.push_back(tmp2[m]);
	}
	
}

void ConnectorOptimizer::variation(vector<int>& fa)
{
	int num_gene = fa.size();
	for (int m = 0;m < num_gene;m++) {
		int pre = rand() % num_gene;
		int bac = rand() % num_gene;
		swap(fa[pre], fa[bac]);
	}
}

int ConnectorOptimizer::getPoolSize(int geqo_effort)
{
	int maxsize = 50 * geqo_effort;
	int minsize = 10 * geqo_effort;
	int nr_rel = cnodes->size();//表的数量
	int size = pow(2.0, nr_rel + 1.0);//基准大小
	if (size >= minsize && size <= maxsize) {
		return size;
	}
	else if (size < minsize) {
		return minsize;
	}
	else if (size > maxsize)
		return maxsize;
}

Individual::Individual(vector<ConnectorNode*> names, vector<int>order)
{
	cnodeNames = names;
	cost = SqlGlobal::getInstance()->calConnect(cnodeNames);
	if (cost < 0)
		cost = LLONG_MAX;//cost小于0说明超出最大界限，则将其设置为最大值
	//cout << cost<<" ";
	this->order = order;
}
