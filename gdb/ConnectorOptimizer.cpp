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
	//������Ⱥ��С
	int geqo_effort = 5;
	int geqo_pool_size = getPoolSize(geqo_effort);//��Ⱥ��С

	vector<vector<int>> rans = getRandomIndividual(geqo_pool_size);
	vector<Individual*> individuals;
	int indiNum = rans.size();//���ɵĸ�����
	//��������
	for (int m = 0;m < indiNum;m++) {
		vector<ConnectorNode*>tmpcnodes;
		for (int n = 0;n < cnodes->size();n++) {
			tmpcnodes.push_back(cnodes->at(rans[m][n]));
		}
		Individual* indi = new Individual(tmpcnodes,rans[m]);
		individuals.push_back(indi);
	}
	std::sort(std::begin(individuals), std::end(individuals),
		[](const Individual* p1, const Individual* p2) {return p1->cost < p2->cost;});//��cost������������
	int time = geqo_pool_size;//�ݻ�����������Ⱥ��С
	for (int m = 0;m < time;m++) {
		/*cout << endl << "��������" << m;
		cout << " ���Ŵ��ۣ�" << individuals.front()->cost << endl;*/
		rans.clear();
		for (int m = 0;m < individuals.size();m++) {
			rans.push_back(individuals.at(m)->order);
		}//���µõ�����
		int chooseIndex1 = getChoosenIndex(individuals.size());
		int chooseIndex2 = getChoosenIndex(individuals.size());
		if (chooseIndex2 == chooseIndex1) {
			//�������ظ���ȡǰһ��ֵ
			chooseIndex2 = chooseIndex1 == 0 ? 1 : chooseIndex1 - 1;
		}
		/*cout << chooseIndex2 << " " << individuals.size() << endl;*/
		vector<int> tmp = rans.at(chooseIndex2);
		getChild(rans.at(chooseIndex1), tmp);//���ɺ����tmp�ڴ�ź��
		variation(tmp);//����
		//����tmp��������
		vector<ConnectorNode*>tmpcnodes;
		for (int n = 0;n < cnodes->size();n++) {
			tmpcnodes.push_back(cnodes->at(tmp[n]));
		}
		Individual* indi = new Individual(tmpcnodes, tmp);
		individuals.push_back(indi);
		std::sort(std::begin(individuals), std::end(individuals),
			[](const Individual* p1, const Individual* p2) {return p1->cost < p2->cost;});//��cost������������
		individuals.pop_back();//ȥ��������ߵĸ���

	}
	//�Ŵ��㷨����������ȡ��һ��
	best = &individuals.front()->cnodeNames;
	cout << "�Ŵ��㷨���������Ŵ��ۣ�" << individuals.front()->cost << endl;
	
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
	// �������
	int len = oldArray.size();
	for (int i = len; i > 0; i--) {
		
		// ѡ�е�����±�
		int index = rand() % i;
		// ����ѡ�е��±꽫ԭ����ѡ�е�Ԫ��push��������
		newArray.push_back(oldArray[index]);
		// ��ԭ������ѡ�е�Ԫ���޳�
		oldArray.erase(oldArray.begin() + index);
	}
}

int ConnectorOptimizer::getChoosenIndex(int individualNum)
{
	int max = individualNum;
	double bias = 2.0;
	double geo_rand;
	//srand(time(NULL));
	geo_rand = (rand() % 100) * 0.01;//��Χ��0~1
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
	//��ȡ����λ�õ��ӽ�
	int geneSize = cnodes->size();//�����С
	int pre = geneSize / 3;
	int bac = geneSize * 2 / 3;
	int p = round((double)rand() / RAND_MAX * (bac - pre) + pre);//�Ӹ���1��ѡ�����ĸ���
	vector<int> tmp1 = fa1;
	int* tmp2 = new int[fa2.size()];
	set<int> input;
	for (int m = 0;m < fa2.size();m++)
		tmp2[m] = -1;//��ʼ��Ϊ-1
	random_shuffle(tmp1.begin(), tmp1.end());//�������tmp1
	for (int m = 0;m < p;m++) {
		int gene = tmp1.at(m);
		int index;
		//��ȡ����λ��
		for (index = 0;index < fa1.size();index++) {
			if (fa1.at(index) == gene)
				break;
		}
		input.insert(gene);//��ֵ����
		tmp2[index] = gene;
	}

	int index = 0;
	for (int m = 0;m < tmp1.size();m++) {
		if (!input.count(fa2.at(m))) {
			//˵�������ڣ���ɲ���
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
	int nr_rel = cnodes->size();//�������
	int size = pow(2.0, nr_rel + 1.0);//��׼��С
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
		cost = LLONG_MAX;//costС��0˵�����������ޣ���������Ϊ���ֵ
	//cout << cost<<" ";
	this->order = order;
}
