#include <iostream>
using namespace std;
#include "Node.h"
#include "SqlGlobal.h"
#include "Translator.h"
#include "DML_gram.tab.h"

int parser_dml_sql(string sql);
string getInputSql();
int main() {

	string sql;
	extern SqlGlobal* sg;
	while (!sg->exit) 
	{
		sql = getInputSql();
		parser_dml_sql(sql);
	}
	return 0;
	
}